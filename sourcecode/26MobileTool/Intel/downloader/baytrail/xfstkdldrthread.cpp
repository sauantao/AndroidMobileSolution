/*
    Copyright (C) 2015  Intel Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "xfstkdldrthread.h"
QString GlobalBaytrailMessageString;
QString GlobalBaytrailStatusValue;
int GlobalBaytrailProgressValue;
int GlobalBaytrailProgressTotalRemainingTargets;
QString GlobalBaytrailLog;
QStringList GlobalBaytrailStatusLog;
QMutex GlobalStatusMutex;

void status(char *message, void *)
{
    QMutexLocker locker(&GlobalStatusMutex);

    QString temp = QTime::currentTime().toString();
    temp.append(QString(" - "));
    temp.append(QString::fromAscii(message));
    temp.remove(QRegExp("[\\n\\r]"));
    GlobalBaytrailMessageString = temp;
    bool isprogress = false;
    if(GlobalBaytrailMessageString.contains("XFSTK-PROGRESS")) {
        isprogress = true;
        QStringList splitter;
        splitter = GlobalBaytrailMessageString.split("--");
        QString Value;
        if(splitter.length() >0 ) {
            Value = splitter.last();
            if(Value.toInt() < 5) {
                Value = "5";
            }
            GlobalBaytrailProgressValue = Value.toInt()/GlobalBaytrailProgressTotalRemainingTargets;
        }
    }
    if(GlobalBaytrailMessageString.contains("XFSTK-STATUS")) {
        QStringList splitter;
        splitter = GlobalBaytrailMessageString.split("--");
        QString Value;
        if(splitter.length() >0 ) {
            Value = splitter.last();
            GlobalBaytrailStatusValue = Value;
        }
    }
    if(!isprogress) {
        GlobalBaytrailLog.append(QString("%1\n").arg(GlobalBaytrailMessageString));
        GlobalBaytrailStatusLog.append(QString("%1").arg(GlobalBaytrailMessageString));
    }
}

xfstkdldrthreadobj::xfstkdldrthreadobj(QObject *parent) :
    QObject(parent)
{
    this->tid = 0;
    this->numtargets = 0;
    this->provisioningok = false;
    this->bLog = false;
    GlobalBaytrailLog.clear();
    GlobalBaytrailStatusLog.clear();
}
void xfstkdldrthreadobj::configuredownloader(char *fwimage, int tid, int numtargets, int retrycount)
{
    this->fwimage = fwimage;
    this->tid = tid;
    this->numtargets = numtargets;
    this->retrycount = retrycount;
    this->bFwOnly = false;
    GlobalBaytrailProgressValue = 5;
    GlobalBaytrailProgressTotalRemainingTargets = numtargets;
    GlobalBaytrailMessageString = "XFSTK-LOG--Initiating Download...";
    GlobalBaytrailLog.clear();
}

bool xfstkdldrthreadobj::downloadfwthread(char *fwimage)
{
    int targetcounter = 0;
    int provpass = 0;
    int provfail = 0;
    int sanity = 0;
    xfstkdldrapi test;
    test.registerstatuscallback(status, 0);


    if(retrycount > 0) {
            test.settargetretrycount(retrycount);
    }
    while(targetcounter < numtargets)
    {
        if(this->bFwOnly)
        {
            provisioningok = test.downloadfw(fwimage);
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
        GlobalBaytrailProgressTotalRemainingTargets--;

    }
    if(provfail > 0) {
        return false;
    }
    return true;
}

void xfstkdldrthreadobj::go()
{
    bool result = this->downloadfwthread(this->fwimage);
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

        QString InitResult = GlobalBaytrailLog;

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
    exit();
}
