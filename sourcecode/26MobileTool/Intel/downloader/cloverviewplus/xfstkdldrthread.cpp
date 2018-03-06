
#include "xfstkdldrthread.h"
QString GlobalCloverviewPlusMessageString;
QString GlobalCloverviewPlusStatusValue;
int GlobalCloverviewPlusProgressValue;
int GlobalCloverviewPlusProgressTotalRemainingTargets;
QString GlobalCloverviewPlusLog;
QStringList GlobalCloverviewPlusStatusLog;
QMutex GlobalStatusMutex;

void status(char *message, void *)
{
    QMutexLocker locker(&GlobalStatusMutex);

    QString temp = QTime::currentTime().toString();
    temp.append(QString(" - "));
    temp.append(QString::fromUtf8(message));
    temp.remove(QRegExp("[\\n\\r]"));
    GlobalCloverviewPlusMessageString = temp;
    bool isprogress = false;
    if(GlobalCloverviewPlusMessageString.contains("XFSTK-PROGRESS")) {
        isprogress = true;
        QStringList splitter;
        splitter = GlobalCloverviewPlusMessageString.split("--");
        QString Value;
        if(splitter.length() >0 ) {
            Value = splitter.last();
            if(Value.toInt() < 5) {
                Value = "5";
            }
            GlobalCloverviewPlusProgressValue = Value.toInt()/GlobalCloverviewPlusProgressTotalRemainingTargets;
        }
    }
    if(GlobalCloverviewPlusMessageString.contains("XFSTK-STATUS")) {
        QStringList splitter;
        splitter = GlobalCloverviewPlusMessageString.split("--");
        QString Value;
        if(splitter.length() >0 ) {
            Value = splitter.last();
            GlobalCloverviewPlusStatusValue = Value;
        }
    }
    if(!isprogress) {
        GlobalCloverviewPlusLog.append(QString("%1\n").arg(GlobalCloverviewPlusMessageString));
        GlobalCloverviewPlusStatusLog.append(QString("%1").arg(GlobalCloverviewPlusMessageString));
    }
}

xfstkdldrthreadobj::xfstkdldrthreadobj(QObject *parent) :
    QObject(parent)
{
    this->tid = 0;
    this->numtargets = 0;
    this->provisioningok = false;
    this->bLog = false;
    GlobalCloverviewPlusLog.clear();
    GlobalCloverviewPlusStatusLog.clear();
}
void xfstkdldrthreadobj::configuredownloader(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags, int tid, int numtargets, int retrycount)
{
    this->fwdnx = fwdnx;
    this->fwimage = fwimage;
    this->osdnx = osdnx;
    this->osimage = osimage;
    this->gpflags = gpflags;
    this->tid = tid;
    this->numtargets = numtargets;
    this->retrycount = retrycount;
    this->bFwOnly = false;
    this->bFwOs = false;
    this->bOsOnly = false;
    GlobalCloverviewPlusProgressValue = 5;
    GlobalCloverviewPlusProgressTotalRemainingTargets = numtargets;
    GlobalCloverviewPlusMessageString = "XFSTK-LOG--Initiating Download...";
    GlobalCloverviewPlusLog.clear();
}

bool xfstkdldrthreadobj::downloadmtfwosthread(char *fwdnx, char *fwimage, char *osdnx, char* osimage, char* gpflags)
{
    int targetcounter = 0;
    int provpass = 0;
    int provfail = 0;
    int sanity = 0;
    xfstkdldrapi test;
    //xfstkstatuspfn mystatusfn = status;
    test.registerstatuscallback(status, 0);
    bool SForNOT = false;

    if(this->bSoftfuseInclude)
    {
        test.setsoftfusepath(true, (char*)this->SoftfusesPath.toLatin1().data());
        SForNOT = true;
    }
    else
        test.setsoftfusepath(false, const_cast<char*>("N/A"));

    if(retrycount > 0) {
            test.settargetretrycount(retrycount);
    }
    while(targetcounter < numtargets) {
        if(this->bFwOnly) {
            provisioningok = test.downloadfw(fwdnx, fwimage, gpflags);
        }
        else if (this->bOsOnly) {
            provisioningok = test.downloados(osdnx, osimage, gpflags);
        }
        else if (this->bFwOs) {
            if (!SForNOT)
                provisioningok = test.downloadfwos(fwdnx, fwimage, osdnx, osimage, gpflags);
            else
                provisioningok = test.downloadfwos(fwdnx, fwimage, osdnx, osimage, gpflags, (char*)this->SoftfusesPath.toLatin1().data());
        }

        if(provisioningok) {
                printf("TARGET: %d -  ################# SUCCESS!!! ###############\n",targetcounter);
                provpass++;
        }
        else {
                printf("TARGET: %d -  !!!!!!!!!!!!!!!!! FAILURE... !!!!!!!!!!!!!!!\n",targetcounter);
                printf("\nXFSTK: SUMMARY - TOTAL PASS = 0 - TOTAL FAIL = %d\n", numtargets);
                printf("\nXFSTK: Programming NOT completed for all %d targets - FAIL\n",numtargets);
                provfail++;
        }
        sanity++;
        provisioningok = false;
        targetcounter++;
        if(sanity > 2*numtargets) {
                printf("\nXFSTK: SUMMARY - TOTAL PASS = 0 - TOTAL FAIL = %d\n", numtargets);
                printf("\nXFSTK: Programming NOT completed for all %d targets - FAIL\n",numtargets);
        }
        TargetsCompletedForThread(provpass);
        GlobalCloverviewPlusProgressTotalRemainingTargets--;

    }
    if(provfail > 0) {
        return false;
    }
    return true;
}

void xfstkdldrthreadobj::go()
{
    bool result = this->downloadmtfwosthread(this->fwdnx, this->fwimage, this->osdnx, this->osimage, this->gpflags);
    if(result) {
        printf("####### Provisioning Completed Successfully for tid - %x\n", this->tid);
    }
    else {
        printf("####### Provisioning Encountered Errors for tid - %x\n", this->tid);
    }
    if(this->bLog) {
        QString origdir = QDir::currentPath();
        if(this->LogPath == "N/A") {
            this->LogPath = origdir;
        }
        QDir::setCurrent(this->LogPath);

        QString InitResult = GlobalCloverviewPlusLog;

        QString logfilename = QString("xfstklog_%1.txt").arg(QDateTime::currentDateTime().toString().replace(" ","_"));
        logfilename = logfilename.replace(":","-");
        QFile file(logfilename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        out << logfilename << "\n" << InitResult;
        file.close();
        QDir::setCurrent(origdir);
    }
    ThreadComplete(result);
}

xfstkdldrthread::xfstkdldrthread(QObject *parent) :
    QThread(parent)
{
}
xfstkdldrthread::~xfstkdldrthread()
{
    wait();
}

void xfstkdldrthread::setobj(xfstkdldrthreadobj *obj)
{
    this->obj = obj;
}
void xfstkdldrthread::run()
{
    this->obj->go();
    this->done();
    exit();
}
