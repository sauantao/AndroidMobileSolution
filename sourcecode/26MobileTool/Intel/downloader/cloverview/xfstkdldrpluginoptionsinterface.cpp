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
#include "xfstkdldrpluginoptionsinterface.h"
#include "ui_xfstkdldrpluginoptionsinterface.h"
#include "xfstkdldrplugincloverview.h"
XfstkDldrPluginOptionsInterface::XfstkDldrPluginOptionsInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XfstkDldrPluginOptionsInterface)
{
    ui->setupUi(this);
}

XfstkDldrPluginOptionsInterface::~XfstkDldrPluginOptionsInterface()
{
    delete ui;
}

QTabWidget *XfstkDldrPluginOptionsInterface::GetTabInterface()
{
    return this->ui->OptionsInterface;
}

void XfstkDldrPluginOptionsInterface::changeEvent(QEvent *e)
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
void XfstkDldrPluginOptionsInterface::UserInterfaceChanged(UserInterfaceState *State)
{
    this->CurrentState.FWDnXPath = State->FWDnXBin;
    this->CurrentState.IFWIPath = State->IFWIBin;
    this->CurrentState.OSDnXPath = State->OSDnXBin;
    this->CurrentState.OSIPath = State->OSImageBin;
    this->CurrentState.EnableGpFlagOverride = State->EnableGpFlagOverride;
    this->CurrentState.GPFlagOverrideValue = State->GPFlagOverrideValue;
    this->CurrentState.LoggingPath = State->LoggingPath;
    this->CurrentState.EnableProvisionCount = State->EnableProvisionCount;
    this->CurrentState.EnableLogging = State->EnableLogging;
    this->CurrentState.ProvisionCount = State->ProvisionCount;
    this->CurrentState.DesktopDir = State->DesktopDir;
    this->CurrentState.USBTimeout = State->USBTimeout;

    this->ui->FWDnXPath->setText(this->CurrentState.FWDnXPath);
    this->ui->IFWIPath->setText(this->CurrentState.IFWIPath);
    this->ui->OSDnXPath->setText(this->CurrentState.OSDnXPath);
    this->ui->OSImagePath->setText(this->CurrentState.OSIPath);
    this->ui->GPFlagOverrideValue->setText(this->CurrentState.GPFlagOverrideValue);
    this->ui->UsbTimeoutOption->setText(this->CurrentState.USBTimeout);
    if(this->CurrentState.EnableGpFlagOverride) {
        this->ui->GPFlagOverrideEnable->setCheckState(Qt::Checked);
    }
    else {
        this->ui->GPFlagOverrideEnable->setCheckState(Qt::Unchecked);
    }
    if(this->CurrentState.EnableProvisionCount) {
        this->ui->ProvisionCountEnabled->setCheckState(Qt::Checked);
    }
    else {
        this->ui->ProvisionCountEnabled->setCheckState(Qt::Unchecked);
    }
    if(this->CurrentState.EnableLogging) {
        this->ui->EnableLogging->setCheckState(Qt::Checked);
    }
    else {
        this->ui->EnableLogging->setCheckState(Qt::Unchecked);
    }
    this->ui->LoggingPath->setText(this->CurrentState.LoggingPath);
    XfstkDldrPluginCloverview* tmpPlugin =  new XfstkDldrPluginCloverview();
    if(tmpPlugin != NULL)
    {
        tmpPlugin->UserTabInterface.CurrentState = *State;
        tmpPlugin->SaveTabInterfaceSettings();
        delete tmpPlugin;
    }

    return;
}

void XfstkDldrPluginOptionsInterface::on_ClearFWDnXPath_clicked()
{
    this->CurrentState.FWDnXPath = "N/A";
    this->ui->FWDnXPath->setText("N/A");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ClearIFWIPath_clicked()
{
    this->CurrentState.IFWIPath = "N/A";
    this->ui->IFWIPath->setText("N/A");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ClearOSDnXPath_clicked()
{
    this->CurrentState.OSDnXPath = "N/A";
    this->ui->OSDnXPath->setText("N/A");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ClearOSImagePath_clicked()
{
    this->CurrentState.OSIPath = "N/A";
    this->ui->OSImagePath->setText("N/A");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ClearAllStoredPaths_clicked()
{
    this->CurrentState.FWDnXPath = "N/A";
    this->CurrentState.IFWIPath = "N/A";
    this->CurrentState.OSDnXPath = "N/A";
    this->CurrentState.OSIPath = "N/A";
    this->ui->FWDnXPath->setText("N/A");
    this->ui->IFWIPath->setText("N/A");
    this->ui->OSDnXPath->setText("N/A");
    this->ui->OSImagePath->setText("N/A");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_GPFlagOverrideEnable_toggled(bool checked)
{
    if(checked) {
        this->CurrentState.EnableGpFlagOverride = true;
    }
    else {
        this->CurrentState.EnableGpFlagOverride = false;
    }
    this->CurrentState.GPFlagOverrideValue = this->ui->GPFlagOverrideValue->text();
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_GPFlagOverrideValue_editingFinished()
{
    this->CurrentState.GPFlagOverrideValue = this->ui->GPFlagOverrideValue->text();
    this->OptionsInterfaceChanged(&(this->CurrentState));
}
void XfstkDldrPluginOptionsInterface::on_UsbTimeoutOption_editingFinished()
{
    this->CurrentState.USBTimeout = this->ui->UsbTimeoutOption->text();
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ProvisionCountEnabled_toggled(bool checked)
{
    if(checked) {
        this->CurrentState.EnableProvisionCount = true;
    }
    else {
        this->CurrentState.EnableProvisionCount = false;
    }
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_EnableLogging_toggled(bool checked)
{
    if(checked) {
        this->CurrentState.EnableLogging = true;
    }
    else {
        this->CurrentState.EnableLogging = false;
    }
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_LoggingPath_editingFinished()
{
    QString dir = this->ui->LoggingPath->text();
    QDir valid_Dir = QDir(dir);
    if(!valid_Dir.exists())
    {
        this->ui->LoggingPath->setFocus();
        this->ui->LoggingPath->setText(this->CurrentState.LoggingPath);
        this->ui->LoggingPath->clearFocus();
        QMessageBox msgBox;
        msgBox.setText("Invalid Log Directory");
        msgBox.exec();

    }else
    {
        this->CurrentState.LoggingPath = dir;
        this->OptionsInterfaceChanged(&(this->CurrentState));
    }
}

void XfstkDldrPluginOptionsInterface::on_BrowseLoggingPath_clicked()
{
    QString Path = this->ui->LoggingPath->text();
    this->ui->LoggingPath->setFocus();
    this->ui->LoggingPath->setText(this->OpenFile.getExistingDirectory(NULL, "Log File Path", Path));
    this->ui->LoggingPath->clearFocus();
    this->on_LoggingPath_editingFinished();
}

void XfstkDldrPluginOptionsInterface::on_RestoreDefaultLogPath_clicked()
{
    this->ui->LoggingPath->setText(this->CurrentState.DesktopDir);
    this->CurrentState.LoggingPath = this->CurrentState.DesktopDir;
    this->OptionsInterfaceChanged(&(this->CurrentState));
}

void XfstkDldrPluginOptionsInterface::on_ResetProvisionCount_clicked()
{
    this->CurrentState.ProvisionCount = QString("0");
    this->OptionsInterfaceChanged(&(this->CurrentState));
}


