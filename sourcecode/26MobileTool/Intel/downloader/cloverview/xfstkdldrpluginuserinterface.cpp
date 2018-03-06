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

extern QString GlobalCloverviewMessageString;
extern QString GlobalCloverviewStatusValue;
extern int GlobalCloverviewProgressValue;
extern QStringList GlobalCloverviewStatusLog;

void attachFunction(void* clientData)
{
    XfstkDldrPluginUserInterface* plugin = reinterpret_cast<XfstkDldrPluginUserInterface*>(clientData);
    int numtargets = plugin->socDevs.number_devices;
    plugin->CurrentState.NumberOfAvailableTargets = numtargets;
    plugin->ui->DeviceStatus->setText(QString("CLOVERVIEW TARGETS DETECTED: %1").arg(numtargets));
    if(plugin->devDetectWait)
        plugin->emitDownloadbegin();
}
void detachFunction(void* clientData)
{
    XfstkDldrPluginUserInterface* plugin = reinterpret_cast<XfstkDldrPluginUserInterface*>(clientData);
    int numtargets = plugin->socDevs.number_devices;
    plugin->CurrentState.NumberOfAvailableTargets = numtargets;
    plugin->ui->DeviceStatus->setText(QString("CLOVERVIEW TARGETS DETECTED: %1").arg(numtargets));

}
void XfstkDldrPluginUserInterface::on_BeginDownload_clicked()
{
    bool conversionStatus = false;
    //If device detected or USBTimeout empty start download
    if(this->CurrentState.NumberOfAvailableTargets || this->CurrentState.USBTimeout.isEmpty())
        this->BeginDownload();
    //if Device timer still active cancel download
    else if(this->DetectDevicesTimeRemain)
    {
        this->cancelDetection();
    }
    else
    {
        this->DetectDevicesTimeRemain = this->CurrentState.USBTimeout.toUInt(&conversionStatus);
        if(!conversionStatus)
        {
            //If invalid number report warning
            this->LastError.clear();
            this->LastError = "Invalid USB Timeout set";
            this->LineEditWA = false;
            this->ReportErrors();
        }else if(this->DetectDevicesTimeRemain != 0)
        {
            this->ui->StatusLog->clear();
            QString tmpstr = QString("Waiting to detect device, time remaining %1 sec").arg(this->DetectDevicesTimeRemain);
            this->ui->DownloadDetails->setText(tmpstr);
            this->UsbCallBackTimer->start(1000);
            this->ui->BeginDownload->setText("Cancel Device Detection Timer");
            this->devDetectWait = true;
            this->DetectDevicesTimeRemain--;
        }else
        {
            this->BeginDownload();
        }
    }
}

void XfstkDldrPluginUserInterface::cancelDetection()
{
    this->ui->BeginDownload->setText("Begin Download");
    this->ui->DownloadDetails->setText("No provisioning activities in progress...");
    this->UsbCallBackTimer->stop();
    this->devDetectWait = false;
    this->DetectDevicesTimeRemain = 0;
}

void XfstkDldrPluginUserInterface::UpdatedeviceDetectStatus()
{
    //Every second report how much time is left. If 0 seconds then cancel
    if(this->DetectDevicesTimeRemain)
    {
        QString tmpstr = QString("Waiting to detect device, time remaining %1 sec").arg(this->DetectDevicesTimeRemain);
        this->ui->DownloadDetails->setText(tmpstr);
        this->UsbCallBackTimer->start(1000);
        this->DetectDevicesTimeRemain--;
    }else
    {
        this->cancelDetection();
    }
#ifndef XFSTK_OS_WIN
    if(this->CurrentState.NumberOfAvailableTargets)
    {
        emit this->readyForDownload();
    }
#endif

}

XfstkDldrPluginUserInterface::XfstkDldrPluginUserInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XfstkDldrPluginUserInterface)
{
    ui->setupUi(this);
    this->IgnoreIncrementalUIChanges = true;
    this->LineEditWA = false;
    this->CurrentState.FWDnXBin = "N/A";
    this->CurrentState.IFWIBin = "N/A";
    this->CurrentState.OSDnXBin = "N/A";
    this->CurrentState.OSImageBin = "N/A";
    this->CurrentState.CurrentSearchDir = "N/A";
    this->CurrentState.SuppressErrors = false;
    this->CurrentState.IsDownloadThreadDone = true;
    this->CurrentState.NumberOfAvailableTargets = 0;
    this->UpdateStatusTimer = new QTimer(this);
    connect(this->UpdateStatusTimer, SIGNAL(timeout()), this, SLOT(UpdateUiStatus()));
    this->UpdateStatusTimer->start(500);
    this->ui->DownloadProgress->setValue(0);
    this->ui->DownloadProgress->setRange(0,100);
    this->bFWOnly = false;
    this->bOsOnly = false;
    this->bFwOs = false;
    this->CurrentState.StatusListLocation = 0;
    this->CurrentState.StatusListPrevLength = 0;
    this->CurrentState.ShowDownloadDetails = false;
    this->CurrentState.DesktopDir = QDir::homePath() + "/Desktop";
    this->UsbCallBackTimer = new QTimer(this);
    connect(this->UsbCallBackTimer,SIGNAL(timeout()),this,SLOT(UpdatedeviceDetectStatus()));
    this->DetectDevicesTimeRemain = 0;
    connect(this,SIGNAL(readyForDownload()),this,SLOT(on_BeginDownload_clicked()));
    memset(&socDevs,0,sizeof(socDevs));
    QFileInfo Dir = QFileInfo(this->CurrentState.DesktopDir);
    if(!Dir.isDir()) {
    this->CurrentState.DesktopDir = qApp->applicationDirPath();
    }

    QString temp = QTime::currentTime().toString();
    temp.append(QString(" - "));
    temp.append("XFSTK-LOG--No provisioning activities in progress...");
    this->ui->StatusLog->addItem(temp);

#ifdef XFSTK_OS_WIN
    this->devDetectWait = false;
    this->CallbackStruct.attach = attachFunction;
    this->CallbackStruct.detach = detachFunction;
    this->CallbackStruct.clientdata = this;
    this->CallbackStruct.device = &(this->socDevs);
    this->dldrapi = new xfstkdldrapi();
    this->dldrapi->registerdevicecallback(&this->CallbackStruct,CLOVERVIEW);
#else
    this->UsbDetectionTimer = new QTimer(this);
    connect(this->UsbDetectionTimer, SIGNAL(timeout()), this, SLOT(UpdateUsbStatus()));
    this->UsbDetectionTimer->start(1000);
    this->dldrapi = NULL;
#endif
    this->ui->DeviceStatus->setText(QString("CLOVERVIEW TARGETS DETECTED: 0"));
}

XfstkDldrPluginUserInterface::~XfstkDldrPluginUserInterface()
{
    delete ui;
    if( this->dldrapi )
        delete this->dldrapi;
    if(this->UpdateStatusTimer)
        delete this->UpdateStatusTimer;
    if(this->UsbCallBackTimer)
        delete this->UsbCallBackTimer;
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

void XfstkDldrPluginUserInterface::on_BrowseFWDnXBin_clicked()
{
    QString Path = this->DetermineCurrentFileSearchPath(this->ui->FWDnXBin->text());
    this->ui->FWDnXBin->setFocus();
    this->ui->FWDnXBin->setText(this->OpenFile.getOpenFileName(NULL, "FW DnX Bin File", Path));
    this->ui->FWDnXBin->clearFocus();
    this->on_FWDnXBin_editingFinished();
}

void XfstkDldrPluginUserInterface::on_BrowseIFWIBin_clicked()
{
    QString Path = this->DetermineCurrentFileSearchPath(this->ui->IFWIBin->text());
    this->ui->IFWIBin->setFocus();
    this->ui->IFWIBin->setText(this->OpenFile.getOpenFileName(NULL, "IFWI Bin File", Path));
    this->ui->IFWIBin->clearFocus();
    this->on_IFWIBin_editingFinished();
}

void XfstkDldrPluginUserInterface::on_BrowseOSDnXBin_clicked()
{
    QString Path = this->DetermineCurrentFileSearchPath(this->ui->OSDnXBin->text());
    this->ui->OSDnXBin->setFocus();
    this->ui->OSDnXBin->setText(this->OpenFile.getOpenFileName(NULL, "OS DnX Bin File", Path));
    this->ui->OSDnXBin->clearFocus();
    this->on_OSDnXBin_editingFinished();
}

void XfstkDldrPluginUserInterface::on_BrowseOSImageBin_clicked()
{
    QString Path = this->DetermineCurrentFileSearchPath(this->ui->OSImageBin->text());
    this->ui->OSImageBin->setFocus();
    this->ui->OSImageBin->setText(this->OpenFile.getOpenFileName(NULL, "OS Image Bin File", Path));
    this->ui->OSImageBin->clearFocus();
    this->on_OSImageBin_editingFinished();
}
void XfstkDldrPluginUserInterface::OptionsInterfaceChanged(OptionsInterfaceState *State)
{
    if(!this->CurrentState.IsDownloadThreadDone) {
        QMessageBox Message;
        Message.setText("Downloader settings cannot be changed while provisioning activities are in progress.\nChanges to all Cloverview settings have been discarded.\nPlease try again after provisioning has completed.");
        Message.exec();
    }
    else {
        if(State->FWDnXPath == "N/A") {
            this->ui->FWDnXBin->setText(State->FWDnXPath);
            this->CurrentState.FWDnXBin = "N/A";
        }
        if(State->IFWIPath == "N/A") {
            this->ui->IFWIBin->setText(State->IFWIPath);
            this->CurrentState.IFWIBin = "N/A";
        }
        if(State->OSDnXPath == "N/A") {
            this->ui->OSDnXBin->setText(State->OSDnXPath);
            this->CurrentState.OSDnXBin = "N/A";
        }
        if(State->OSIPath == "N/A") {
            this->ui->OSImageBin->setText(State->OSIPath);
            this->CurrentState.OSImageBin = "N/A";
        }
        if(this->CurrentState.EnableGpFlagOverride != State->EnableGpFlagOverride) {
            this->CurrentState.EnableGpFlagOverride = State->EnableGpFlagOverride;
        }
        if(this->CurrentState.GPFlagOverrideValue != State->GPFlagOverrideValue) {
            this->CurrentState.GPFlagOverrideValue = State->GPFlagOverrideValue;
        }
        this->CurrentState.LoggingPath = State->LoggingPath;
        this->CurrentState.EnableLogging = State->EnableLogging;
        if(State->ProvisionCount == QString("0")) {
            this->CurrentState.ProvisionCount = State->ProvisionCount;
            this->CurrentState.NumProvisionCount = 0;
            this->ui->ProvisionCount->setText(QString("Cloverview Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
        }
        this->CurrentState.EnableProvisionCount = State->EnableProvisionCount;

        if(!this->CurrentState.EnableProvisionCount) {
            this->ui->ProvisionCount->hide();
        }
        else {
            this->ui->ProvisionCount->show();
        }
        this->CurrentState.USBTimeout = State->USBTimeout;
    }
    this->SaveUserInterfaceStateToDisk(QString("Intel"),QString("Cloverview"));

    return;
}

void XfstkDldrPluginUserInterface::on_FWDnXBin_editingFinished()
{
    if(this->VerifyBinaryFilePath(this->ui->FWDnXBin->text())) {
        this->CurrentState.FWDnXBin = this->ui->FWDnXBin->text();
        this->UserInterfaceChanged(&(this->CurrentState));
    }
    else {
        this->CurrentState.FWDnXBin = "N/A";
        this->ui->FWDnXBin->setText(this->CurrentState.FWDnXBin);
    }
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

void XfstkDldrPluginUserInterface::on_OSDnXBin_editingFinished()
{
    if(this->VerifyBinaryFilePath(this->ui->OSDnXBin->text())) {
        this->CurrentState.OSDnXBin = this->ui->OSDnXBin->text();
        this->UserInterfaceChanged(&(this->CurrentState));
    }
    else {
        this->CurrentState.OSDnXBin = "N/A";
        this->ui->OSDnXBin->setText(this->CurrentState.OSDnXBin);
    }
}

void XfstkDldrPluginUserInterface::on_OSImageBin_editingFinished()
{
    if(this->VerifyBinaryFilePath(this->ui->OSImageBin->text())) {
        this->CurrentState.OSImageBin = this->ui->OSImageBin->text();
        this->UserInterfaceChanged(&(this->CurrentState));
    }
    else {
        this->CurrentState.OSImageBin = "N/A";
        this->ui->OSImageBin->setText(this->CurrentState.OSImageBin);
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
            settings.setValue("fwDnxPath", this->CurrentState.FWDnXBin);
            settings.setValue("fwImagePath", this->CurrentState.IFWIBin);
            settings.setValue("osDnxPath", this->CurrentState.OSDnXBin);
            settings.setValue("osImagePath", this->CurrentState.OSImageBin);
        settings.endGroup();
        settings.beginGroup("Download Options");
            settings.setValue("gpFlagOverrideEnabled", this->CurrentState.EnableGpFlagOverride);
            settings.setValue("gpFlagOverrideValue", this->CurrentState.GPFlagOverrideValue);
            settings.setValue("USBTimeout", this->CurrentState.USBTimeout);
        settings.endGroup();
        settings.beginGroup("Provision Count");
            settings.setValue("provisionAttempts", this->CurrentState.NumProvisionCount);
            settings.setValue("provisionAttemptsVisible", this->CurrentState.EnableProvisionCount);
        settings.endGroup();
        //settings.beginGroup("Tool Tips");
        //settings.setValue("toolTipsVisible", this-);
        //settings.endGroup();
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
                this->CurrentState.FWDnXBin = settings.value("fwDnxPath", "N/A").toString();
                this->CurrentState.IFWIBin = settings.value("fwImagePath", "N/A").toString();
                this->CurrentState.OSDnXBin = settings.value("osDnxPath", "N/A").toString();
                this->CurrentState.OSImageBin = settings.value("osImagePath", "N/A").toString();
            settings.endGroup();
            settings.beginGroup("Download Options");
                this->CurrentState.EnableGpFlagOverride = settings.value("gpFlagOverrideEnabled", false).toBool();
                this->CurrentState.GPFlagOverrideValue = settings.value("gpFlagOverrideValue", "0x80000001").toString();
                this->CurrentState.USBTimeout = settings.value("USBTimeout", "60").toString();
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
    this->ui->FWDnXBin->setText(this->CurrentState.FWDnXBin);
    this->ui->IFWIBin->setText(this->CurrentState.IFWIBin);
    this->ui->OSDnXBin->setText(this->CurrentState.OSDnXBin);
    this->ui->OSImageBin->setText(this->CurrentState.OSImageBin);
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
    this->ui->ProvisionCount->setText(QString("Cloverview Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
}
void XfstkDldrPluginUserInterface::TargetsCompletedForThread(int numdone)
{
    this->CurrentState.TotalPassingProvisionsForCurrentThread = numdone;
}

void XfstkDldrPluginUserInterface::ThreadComplete(bool result)
{
    if(this->bFWOnly) {
        if(result) {
            this->ui->DownloadDetails->setText("Success: FW only download completed!");
        }
        else {
            this->ui->DownloadDetails->setText("Failure: FW only download did not complete.");
        }
    }
    else if(this->bOsOnly) {
        if(result) {if(((this->CurrentState.GPFlagOverrideValue != "0x80000000") && (this->CurrentState.EnableGpFlagOverride == true)) || (this->CurrentState.EnableGpFlagOverride == false))
            this->ui->DownloadDetails->setText("Success: OS only download completed!");
            else
                this->ui->DownloadDetails->setText("OS download skipped");
        }
        else {
            this->ui->DownloadDetails->setText("Failure: OS only download did not complete.");
        }
    }
    else if(this->bFwOs) {
        if(result) {
            if(!this->CurrentState.EnableGpFlagOverride || (QString(this->CurrentState.GPFlagOverrideValue).toULong(0,16)&1) )
                this->ui->DownloadDetails->setText("Success: FW+OS download completed!");
            else
                this->ui->DownloadDetails->setText("Success: FW download completed! OS download skipped");
        }
        else {
            this->ui->DownloadDetails->setText("Failure: FW+OS download did not complete.");
        }
    }

    this->ui->DownloadProgress->setValue(100);
    this->CurrentState.TotalFailingProvisionsForCurrentThread = this->CurrentState.TotalTargetsForCurrentThread - this->CurrentState.TotalPassingProvisionsForCurrentThread;
    this->CurrentState.IsDownloadThreadDone = true;
    if(this->CurrentState.StatusListPrevLength < GlobalCloverviewStatusLog.length()) {
        this->CurrentState.StatusListLocation = this->CurrentState.StatusListPrevLength;
        this->CurrentState.StatusListPrevLength = GlobalCloverviewStatusLog.length();
        if(this->CurrentState.ShowDownloadDetails) {
            int i = 0;
            for(int i = this->CurrentState.StatusListLocation; i < this->CurrentState.StatusListPrevLength;i++) {
                this->ui->StatusLog->addItem(QString("%1").arg(GlobalCloverviewStatusLog.at(i)));
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
#ifndef XFSTK_OS_WIN
    xfstkdldrapi status;
    int numtargets = status.getavailabletargets(CLOVERVIEW);
#else
    int numtargets = this->socDevs.number_devices;

#endif
    this->ui->DeviceStatus->setText(QString("CLOVERVIEW TARGETS DETECTED: %1").arg(numtargets));
    this->CurrentState.NumberOfAvailableTargets = numtargets;
}

void XfstkDldrPluginUserInterface::UpdateUiStatus()
{
    if(this->CurrentState.IsDownloadThreadDone) {
        GlobalCloverviewStatusLog.clear();
        this->CurrentState.StatusListLocation = 0;
        this->CurrentState.StatusListPrevLength = 0;
    }
    else {
        this->ui->DownloadDetails->setText(QString("%1").arg(GlobalCloverviewStatusValue));
        this->ui->DownloadProgress->setValue(GlobalCloverviewProgressValue);
        if(this->CurrentState.StatusListPrevLength < GlobalCloverviewStatusLog.length()) {
            this->CurrentState.StatusListLocation = this->CurrentState.StatusListPrevLength;
            this->CurrentState.StatusListPrevLength = GlobalCloverviewStatusLog.length();
            if(this->CurrentState.ShowDownloadDetails) {
                int i = 0;
                for(int i = this->CurrentState.StatusListLocation; i < this->CurrentState.StatusListPrevLength;i++) {
                    this->ui->StatusLog->addItem(QString("%1").arg(GlobalCloverviewStatusLog.at(i)));
                }
                this->CurrentState.StatusListLocation = i;
                this->ui->StatusLog->scrollToBottom();
            }
        }
    }
}

void XfstkDldrPluginUserInterface::BeginDownload()
{
    this->bFWOnly = false;
    this->bOsOnly = false;
    this->bFwOs = false;

    this->cancelDetection();

    this->FWDnX.clear();
    this->FWImage.clear();
    this->OSImage.clear();
    this->OSDnX.clear();
    this->GPFlagsOverride.clear();

    this->FWDnX = this->ui->FWDnXBin->text();
    this->FWImage = this->ui->IFWIBin->text();
    this->OSDnX = this->ui->OSDnXBin->text();
    this->OSImage = this->ui->OSImageBin->text();
    if(this->CurrentState.EnableGpFlagOverride) {
        GPFlagsOverride = this->CurrentState.GPFlagOverrideValue;
    }
    else {
        GPFlagsOverride = "0x80000001";
    }

    if(FWDnX != "N/A" && FWImage != "N/A" && (OSDnX == "N/A" || OSImage == "N/A")) {

        //If FW only clear bit 1 even if user set it.
        QString tmpGPFlagsOverride = GPFlagsOverride;

        QMessageBox Message;
        bool ok;
        unsigned long tmpgpflags = tmpGPFlagsOverride.toULong(&ok, 16);
        if(tmpgpflags & 1) {
            if(this->CurrentState.EnableGpFlagOverride){
                Message.setText("OS dnx or OS image path is invalid but gpflags is set to download OS.");
                Message.exec();
            }
            tmpgpflags &= 0xFFFFFFFE;
            GPFlagsOverride = tmpGPFlagsOverride.number(tmpgpflags, 16).toUpper();
        }
    }

    this->baFWDnx = FWDnX.toLatin1();
    this->baFWImage = FWImage.toLatin1();
    this->baOSDnx = OSDnX.toLatin1();
    this->baOSImage = OSImage.toLatin1();
    this->baGPFlagsOverride = GPFlagsOverride.toLatin1();

    this->c_str_FWDnX = baFWDnx.data();
    this->c_str_FWImage = baFWImage.data();
    this->c_str_OSDnx = baOSDnx.data();
    this->c_str_OSImage = baOSImage.data();
    this->c_str_GPFlagsOverride = baGPFlagsOverride.data();

    this->CurrentState.SuppressErrors = true;
    this->ui->StatusLog->clear();
    GlobalCloverviewStatusLog.clear();
    this->CurrentState.StatusListLocation = 0;
    this->CurrentState.StatusListPrevLength = 0;

    if(FWDnX != "N/A" && FWImage != "N/A" && OSDnX != "N/A" && OSImage != "N/A") {
        //fw & os one shot
        this->ui->DownloadDetails->setText("Preparing for FW+OS download...");

        bFwOs = true;
        if(!this->VerifyBinaryFilePath(FWDnX) || !this->VerifyBinaryFilePath(FWImage) ||
           !this->VerifyBinaryFilePath(OSDnX) || !this->VerifyBinaryFilePath(OSImage)) {
            QMessageBox Message;
            Message.setText("Please select valid Fw DnX, Fw, Os Dnx, and OS images.");
            Message.exec();
            return;
        }
    }
    else if(FWDnX != "N/A" && FWImage != "N/A") {
        //fw only
        bFWOnly = true;

        this->ui->DownloadDetails->setText("Preparing for FW only download...");
        if(!this->VerifyBinaryFilePath(FWDnX) || !this->VerifyBinaryFilePath(FWImage)) {
            QMessageBox Message;
            Message.setText("Please select valid Fw DnX, Fw, Os Dnx, and OS images.");
            Message.exec();
            return;
        }
    }
    else if(OSDnX != "N/A" && OSImage != "N/A") {
        //os only
        bOsOnly = true;
        this->ui->DownloadDetails->setText("Preparing for OS only download...");
        if(!this->VerifyBinaryFilePath(OSDnX) || !this->VerifyBinaryFilePath(OSImage)) {
            QMessageBox Message;
            Message.setText("Please select valid Fw DnX, Fw, Os Dnx, and OS images.");
            Message.exec();
            return;
        }
    }
    else {
        //error fill fields correctly...
        QMessageBox Message;
        Message.setText("Please select valid Fw DnX, Fw, Os Dnx, and OS images.");
        Message.exec();
        return;
    }
    this->CurrentState.SuppressErrors = false;
    GlobalCloverviewStatusValue = this->ui->DownloadDetails->text();

    if(this->CurrentState.IsDownloadThreadDone) {
        this->CurrentState.StatusListLocation = 0;
        this->CurrentState.StatusListPrevLength = 0;
        if(this->CurrentState.EnableProvisionCount) {
            this->CurrentState.NumProvisionCount++;
            this->CurrentState.ProvisionCount = QString("%1").arg(this->CurrentState.NumProvisionCount);
            this->ui->ProvisionCount->setText(QString("Cloverview Provisions Attempted: %1").arg(this->CurrentState.ProvisionCount));
            this->UserInterfaceChanged(&(this->CurrentState));
        }
        this->ui->BeginDownload->setEnabled(false);
        this->ui->DownloadProgress->setRange(0,100);
        this->ui->DownloadProgress->setValue(5);
        GlobalCloverviewProgressValue = 5;
        this->CurrentState.TotalPassingProvisionsForCurrentThread = 0;
        this->CurrentState.IsDownloadThreadDone = false;
        int tid = 0;
        int numtargets = 1;
        if(this->CurrentState.NumberOfAvailableTargets != 0) {
            numtargets = this->CurrentState.NumberOfAvailableTargets;
        }
        this->CurrentState.TotalTargetsForCurrentThread = numtargets;
        int numretries = 20;

        xfstknewthreadobj.configuredownloader(c_str_FWDnX, c_str_FWImage,c_str_OSDnx,c_str_OSImage,c_str_GPFlagsOverride, tid, numtargets,numretries);

        if(bFWOnly) {
            this->ui->DownloadProgress->setValue(0);
            xfstknewthreadobj.bFwOnly = true;
        }
        else if(bOsOnly) {
            xfstknewthreadobj.bOsOnly = true;
        }
        else if(bFwOs) {
            xfstknewthreadobj.bFwOs = true;
        }
        else {
            return;
        }
        if(this->CurrentState.EnableLogging == true) {
            xfstknewthreadobj.bLog = true;
            xfstknewthreadobj.LogPath = this->CurrentState.LoggingPath;
        }
        xfstknewthread.setobj(&xfstknewthreadobj);
        QObject::connect(&xfstknewthreadobj,SIGNAL(ThreadComplete(bool)),this,SLOT(ThreadComplete(bool)));
        QObject::connect(&xfstknewthreadobj,SIGNAL(TargetsCompletedForThread(int)),this,SLOT(TargetsCompletedForThread(int)));
        xfstknewthread.start();
    }
}

