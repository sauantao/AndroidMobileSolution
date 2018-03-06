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
#include "xfstkdldrpluginuserinterface.h"
#include "ui_xfstkdldrpluginuserinterface.h"

extern QString GlobalBaytrailMessageString;
extern QString GlobalBaytrailStatusValue;
extern int GlobalBaytrailProgressValue;
extern QStringList GlobalBaytrailStatusLog;

XfstkDldrPluginUserInterface::XfstkDldrPluginUserInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XfstkDldrPluginUserInterface)
{
    ui->setupUi(this);
    this->IgnoreIncrementalUIChanges = true;
    this->LineEditWA = false;
    this->CurrentState.IFWIBin = "N/A";
    this->CurrentState.CurrentSearchDir = "N/A";
    this->CurrentState.SuppressErrors = false;
    this->CurrentState.IsDownloadThreadDone = true;
    this->CurrentState.NumberOfAvailableTargets = 0;
    this->UpdateStatusTimer = new QTimer(this);
    connect(this->UpdateStatusTimer, SIGNAL(timeout()), this, SLOT(UpdateUiStatus()));
    this->UpdateStatusTimer->start(500);
    this->ui->DownloadProgress->setValue(0);
    this->ui->DownloadProgress->setRange(0,100);
    this->CurrentState.StatusListLocation = 0;
    this->CurrentState.StatusListPrevLength = 0;
    this->CurrentState.StartDownload = 0;
    this->CurrentState.ShowDownloadDetails = false;
    this->CurrentState.DesktopDir = QDir::homePath() + "/Desktop";
    QFileInfo Dir = QFileInfo(this->CurrentState.DesktopDir);
    if(!Dir.isDir()) {
    this->CurrentState.DesktopDir = qApp->applicationDirPath();
    }

    QString temp = QTime::currentTime().toString();
    temp.append(QString(" - "));
    temp.append("XFSTK-LOG--No provisioning activities in progress...");
    this->ui->StatusLog->addItem(temp);
}

XfstkDldrPluginUserInterface::~XfstkDldrPluginUserInterface()
{
    delete ui;
    if(this->UpdateStatusTimer)
        delete this->UpdateStatusTimer;
}
QTabWidget *XfstkDldrPluginUserInterface::GetTabInterface()
{
    return this->ui->UserInterface;
}

void XfstkDldrPluginUserInterface::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void XfstkDldrPluginUserInterface::ReportErrors()
{
    if(!this->CurrentState.SuppressErrors) {
        this->LineEditWA = !(this->LineEditWA);
        if(this->LineEditWA ) {
            if(this->LastError.length() != 0) {
                QMessageBox msgBox;
                msgBox.setText(this->LastError);
                msgBox.exec();
            }
        }
    }
}

void XfstkDldrPluginUserInterface::on_BrowseIFWIBin_clicked()
{
    QString Path = this->DetermineCurrentFileSearchPath(this->ui->IFWIBin->text());
    this->ui->IFWIBin->setFocus();
    this->ui->IFWIBin->setText(this->OpenFile.getOpenFileName(NULL, "IFWI Bin File", Path));
    this->ui->IFWIBin->clearFocus();
    this->on_IFWIBin_editingFinished();

}

void XfstkDldrPluginUserInterface::OptionsInterfaceChanged(OptionsInterfaceState *State)
{
    if(!this->CurrentState.IsDownloadThreadDone) {
        QMessageBox Message;
        Message.setText("Downloader settings cannot be changed while provisioning activities are in progress.\nChanges to all Baytrail settings have been discarded.\nPlease try again after provisioning has completed.");
        Message.exec();
    }
    else
    {
        if(State->IFWIPath == "N/A")
        {
            this->ui->IFWIBin->setText(State->IFWIPath);
            this->CurrentState.IFWIBin = "N/A";
        }
        this->CurrentState.LoggingPath = State->LoggingPath;
        this->CurrentState.EnableLogging = State->EnableLogging;
        if(State->ProvisionCount == QString("0")) {
            this->CurrentState.ProvisionCount = State->ProvisionCount;
            this->CurrentState.NumProvisionCount = 0;
            this->ui->ProvisionCount->setText(QString("Baytrail Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
        }
        this->CurrentState.EnableProvisionCount = State->EnableProvisionCount;

        if(!this->CurrentState.EnableProvisionCount) {
            this->ui->ProvisionCount->hide();
        }
        else {
            this->ui->ProvisionCount->show();
        }
    }

    return;
}

void XfstkDldrPluginUserInterface::on_IFWIBin_editingFinished()
{
    if(this->VerifyBinaryFilePath(this->ui->IFWIBin->text())) {
        this->CurrentState.IFWIBin = this->ui->IFWIBin->text();
        this->UserInterfaceChanged(&(this->CurrentState));
    }
    else {
        this->CurrentState.IFWIBin = "N/A";
        this->ui->IFWIBin->setText(this->CurrentState.IFWIBin);
    }
}

bool XfstkDldrPluginUserInterface::ValidateUserInterfaceState()
{
    return true;
}
bool XfstkDldrPluginUserInterface::VerifyBinaryFilePath(QString BinPath)
{
    this->LastError.clear();

    if(BinPath == "N/A") {
        return true;
    }

    if(BinPath.endsWith(".bin" , Qt::CaseInsensitive)){
        if(QFile::exists(BinPath)) {
            QStringList splitter;
            QString Bin;
            QString Path;
            splitter = BinPath.split("/");
            if(splitter.length() != 0) {
                Bin = splitter.last();
            }
            splitter = BinPath.split(Bin);
            if(splitter.length() != 0) {
                Path = splitter.first();
            }
            this->CurrentState.CurrentSearchDir = Path;
            return true;
        }
        else {
            this->LastError = "File does not exist.";
        }
    }
    else {
        if(BinPath == "") {
            return false;
        }
        else {
            this->LastError = "File type must be .bin.";
        }
    }
    this->ReportErrors();
    return false;
}

QString XfstkDldrPluginUserInterface::DetermineCurrentFileSearchPath(QString BinPath)
{
    QStringList splitter;
    QString Bin;
    QString Path;
    QFileInfo Dir = QFileInfo(this->CurrentState.CurrentSearchDir);
    this->CurrentState.SuppressErrors = true;
    if(this->CurrentState.CurrentSearchDir == "N/A" || !Dir.isDir()) {
        if(BinPath != "N/A" && this->VerifyBinaryFilePath(BinPath)) {
            splitter = BinPath.split("/");
            if(splitter.length() != 0) {
                Bin = splitter.last();
            }
            splitter = BinPath.split(Bin);
            if(splitter.length() != 0) {
                Path = splitter.first();
            }
            this->CurrentState.CurrentSearchDir = Path;
        }
        else {
            this->CurrentState.CurrentSearchDir = QDesktopServices::displayName(QDesktopServices::DesktopLocation);
        }
    }
    this->CurrentState.SuppressErrors = false;
    return this->CurrentState.CurrentSearchDir;
}

void XfstkDldrPluginUserInterface::SaveUserInterfaceStateToDisk(QString Vendor, QString ProductPlugin)
{
#if defined XFSTK_OS_WIN
    QString PluginPath = QString("%1/%2/").arg(qApp->applicationDirPath(),QString("xfstkdldrplugins"));
#else
    QString PluginPath = QString("/usr/lib/xfstk/xfstkdldrplugins/");
#endif
    QSettings settings(PluginPath + Vendor + ".ini", QSettings::IniFormat);
    settings.beginGroup(ProductPlugin);
        settings.beginGroup("Image Paths");
            settings.setValue("fwImagePath", this->CurrentState.IFWIBin);
        settings.endGroup();
            settings.beginGroup("Download Options");
        settings.endGroup();
        settings.beginGroup("Provision Count");
            settings.setValue("provisionAttempts", this->CurrentState.NumProvisionCount);
            settings.setValue("provisionAttemptsVisible", this->CurrentState.EnableProvisionCount);
        settings.endGroup();
        settings.beginGroup("Logging");
            settings.setValue("loggingEnabled", this->CurrentState.EnableLogging);
            settings.setValue("loggingPath", this->CurrentState.LoggingPath);
            settings.setValue("showStatusLog", this->CurrentState.ShowDownloadDetails);
        settings.endGroup();
    settings.endGroup();
    settings.sync();
}

void XfstkDldrPluginUserInterface::LoadUserInterfaceStateFromDisk(QString Vendor, QString ProductPlugin)
{

#if defined XFSTK_OS_WIN
    QString PluginPath = QString("%1/%2/").arg(qApp->applicationDirPath(),QString("xfstkdldrplugins"));
#else
    QString PluginPath = QString("/usr/lib/xfstk/xfstkdldrplugins/");
#endif
    QSettings settings(PluginPath + Vendor + ".ini", QSettings::IniFormat);
    if(settings.status() == QSettings::NoError) {
        settings.beginGroup(ProductPlugin);
            settings.beginGroup("Image Paths");
                this->CurrentState.IFWIBin = settings.value("fwImagePath", "N/A").toString();
            settings.endGroup();
            settings.beginGroup("Download Options");
            settings.endGroup();
            settings.beginGroup("Provision Count");
                this->CurrentState.NumProvisionCount = settings.value("provisionAttempts", 0).toUInt();
                this->CurrentState.ProvisionCount = QString("%1").arg(this->CurrentState.NumProvisionCount);
                this->CurrentState.EnableProvisionCount = settings.value("provisionAttemptsVisible", true).toBool();
            settings.endGroup();
            settings.beginGroup("Logging");
                this->CurrentState.EnableLogging = settings.value("loggingEnabled", false).toBool();
                this->CurrentState.LoggingPath = settings.value("loggingPath", this->CurrentState.DesktopDir).toString();
                this->CurrentState.ShowDownloadDetails = settings.value("showStatusLog",true).toBool();
            settings.endGroup();
        settings.endGroup();
    }
    else {
        this->SaveUserInterfaceStateToDisk(Vendor,ProductPlugin);
    }
    this->UserInterfaceChanged(&(this->CurrentState));
}
void XfstkDldrPluginUserInterface::RestoreUserInterfaceFromCurrentState()
{
    this->ui->IFWIBin->setText(this->CurrentState.IFWIBin);
    if(this->CurrentState.ShowDownloadDetails) {
        this->ui->StatusLog->show();
    }
    else {
        this->ui->StatusLog->hide();
    }
    if(!this->CurrentState.EnableProvisionCount) {
        this->ui->ProvisionCount->hide();
    }
    else {
        this->ui->ProvisionCount->show();
    }
    this->CurrentState.ProvisionCount = QString("%1").arg(this->CurrentState.NumProvisionCount);
    this->ui->ProvisionCount->setText(QString("Baytrail Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
}
void XfstkDldrPluginUserInterface::TargetsCompletedForThread(int numdone)
{
    this->CurrentState.TotalPassingProvisionsForCurrentThread = numdone;
}

void XfstkDldrPluginUserInterface::ThreadComplete(bool result)
{
    if(this->bFWOnly)
    {
        if(result)
        {
            this->ui->DownloadDetails->setText("Success: FW only download completed!");
        }
        else
        {
            this->ui->DownloadDetails->setText("Failure: FW only download did not complete.");
        }
    }

    this->ui->DownloadProgress->setValue(100);
    this->CurrentState.TotalFailingProvisionsForCurrentThread = this->CurrentState.TotalTargetsForCurrentThread - this->CurrentState.TotalPassingProvisionsForCurrentThread;
    this->CurrentState.IsDownloadThreadDone = true;
    if(this->CurrentState.StatusListPrevLength < GlobalBaytrailStatusLog.length()) {
        this->CurrentState.StatusListLocation = this->CurrentState.StatusListPrevLength;
        this->CurrentState.StatusListPrevLength = GlobalBaytrailStatusLog.length();
        if(this->CurrentState.ShowDownloadDetails) {
            int i = 0;
            for(int i = this->CurrentState.StatusListLocation; i < this->CurrentState.StatusListPrevLength;i++) {
                this->ui->StatusLog->addItem(QString("%1").arg(GlobalBaytrailStatusLog.at(i)));
            }
            this->CurrentState.StatusListLocation = i;
            this->ui->StatusLog->scrollToBottom();
        }
    }
    this->CurrentState.StatusListLocation = 0;
    this->CurrentState.StatusListPrevLength = 0;
    this->ui->BeginDownload->setEnabled(true);
}

void XfstkDldrPluginUserInterface::UpdateUsbStatus()
{
    xfstkdldrapi status;

    // this code creates user input performance issues in GUI.
    // Since BayTrail has no detection window, disable feature
    //if((this->CurrentState.StartDownload == 0))// && (this->CurrentState.NumberOfAvailableTargets == 0))
    //{
    //    int numtargets = status.getavailabletargets(BAYTRAIL);
    //    this->ui->DeviceStatus->setText(QString("BAYTRAIL TARGETS DETECTED: %1").arg(numtargets));
    //    this->CurrentState.NumberOfAvailableTargets = numtargets;
    //}
}

void XfstkDldrPluginUserInterface::UpdateUiStatus()
{
    if(this->CurrentState.IsDownloadThreadDone) {
        GlobalBaytrailStatusLog.clear();
        this->CurrentState.StatusListLocation = 0;
        this->CurrentState.StatusListPrevLength = 0;
    }
    else
    {
        this->ui->DownloadDetails->setText(QString("%1").arg(GlobalBaytrailStatusValue));
        this->ui->DownloadProgress->setValue(GlobalBaytrailProgressValue);
        if(this->CurrentState.StatusListPrevLength < GlobalBaytrailStatusLog.length())
        {
            this->CurrentState.StatusListLocation = this->CurrentState.StatusListPrevLength;
            this->CurrentState.StatusListPrevLength = GlobalBaytrailStatusLog.length();
            if(this->CurrentState.ShowDownloadDetails)
            {
                int i = 0;
                for(int i = this->CurrentState.StatusListLocation; i < this->CurrentState.StatusListPrevLength;i++)
                {
                    this->ui->StatusLog->addItem(QString("%1").arg(GlobalBaytrailStatusLog.at(i)));
                }
                this->CurrentState.StatusListLocation = i;
                this->ui->StatusLog->scrollToBottom();
            }
        }
    }
}

void XfstkDldrPluginUserInterface::DownloaderDone()
  {
    this->CurrentState.StartDownload = 0;
  }

void XfstkDldrPluginUserInterface::on_BeginDownload_clicked()
{
    this->bFWOnly = false;
    this->FWImage.clear();
    this->FWImage = this->ui->IFWIBin->text();
    this->baFWImage = FWImage.toLatin1();
    this->c_str_FWImage = baFWImage.data();
    this->CurrentState.SuppressErrors = true;
    this->ui->StatusLog->clear();
    GlobalBaytrailStatusLog.clear();
    this->CurrentState.StatusListLocation = 0;
    this->CurrentState.StatusListPrevLength = 0;
    this->CurrentState.StartDownload = 1;

    if(FWImage != "N/A")
    {
        //fw only
        bFWOnly = true;

        this->ui->DownloadDetails->setText("Preparing for FW only download...");
        if(!this->VerifyBinaryFilePath(FWImage))
        {
            QMessageBox Message;
            Message.setText("Please select valid FW image.");
            Message.exec();
            this->CurrentState.StartDownload = 0;
            return;
        }
    }

    this->CurrentState.SuppressErrors = false;
    GlobalBaytrailStatusValue = this->ui->DownloadDetails->text();

    if(this->CurrentState.IsDownloadThreadDone)
    {
        this->CurrentState.StatusListLocation = 0;
        this->CurrentState.StatusListPrevLength = 0;
        if(this->CurrentState.EnableProvisionCount)
        {
            this->CurrentState.NumProvisionCount++;
            this->CurrentState.ProvisionCount = QString("%1").arg(this->CurrentState.NumProvisionCount);
            this->ui->ProvisionCount->setText(QString("Baytrail Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
            this->UserInterfaceChanged(&(this->CurrentState));
        }
        this->ui->BeginDownload->setEnabled(false);
        this->ui->DownloadProgress->setRange(0,100);
        this->ui->DownloadProgress->setValue(5);
        GlobalBaytrailProgressValue = 5;
        this->CurrentState.TotalPassingProvisionsForCurrentThread = 0;
        this->CurrentState.IsDownloadThreadDone = false;
        int tid = 0;
        int numtargets = 1;
        if(this->CurrentState.NumberOfAvailableTargets != 0)
        {
            numtargets = this->CurrentState.NumberOfAvailableTargets;
        }
        this->CurrentState.TotalTargetsForCurrentThread = numtargets;
        int numretries = 20;
        xfstknewthreadobj.configuredownloader( c_str_FWImage, tid, numtargets,numretries);

        if(bFWOnly)
        {
            this->ui->DownloadProgress->setValue(0);
            xfstknewthreadobj.bFwOnly = true;
        }

        if(this->CurrentState.EnableLogging == true)
        {
            xfstknewthreadobj.bLog = true;
            xfstknewthreadobj.LogPath = this->CurrentState.LoggingPath;
        }

        xfstknewthread.setobj(&xfstknewthreadobj);
        QObject::connect(&xfstknewthreadobj,SIGNAL(ThreadComplete(bool)),this,SLOT(ThreadComplete(bool)), Qt::UniqueConnection);
        QObject::connect(&xfstknewthreadobj,SIGNAL(TargetsCompletedForThread(int)),this,SLOT(TargetsCompletedForThread(int)));
        QObject::connect(&xfstknewthread,SIGNAL(finished()),this,SLOT(DownloaderDone()));
        xfstknewthread.start();
    }
}

