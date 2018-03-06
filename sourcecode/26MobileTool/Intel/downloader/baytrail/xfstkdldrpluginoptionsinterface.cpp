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
#include "xfstkdldrpluginbaytrail.h"

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
    this->CurrentState.IFWIPath = State->IFWIBin;
    this->CurrentState.LoggingPath = State->LoggingPath;
    this->CurrentState.EnableProvisionCount = State->EnableProvisionCount;
    this->CurrentState.EnableLogging = State->EnableLogging;
    this->CurrentState.ProvisionCount = State->ProvisionCount;
    this->CurrentState.DesktopDir = State->DesktopDir;

    this->ui->IFWIPath->setText(this->CurrentState.IFWIPath);
    this->ui->LoggingPath->setText(this->CurrentState.LoggingPath);
    ////
    if(this->CurrentState.EnableProvisionCount)
    {
        this->ui->ProvisionCountEnabled->setCheckState(Qt::Checked);
    }
    else
    {
        this->ui->ProvisionCountEnabled->setCheckState(Qt::Unchecked);
    }
    ////
    if(this->CurrentState.EnableLogging)
    {
        this->ui->EnableLogging->setCheckState(Qt::Checked);
    }
    else
    {
        this->ui->EnableLogging->setCheckState(Qt::Unchecked);
    }

    XfstkDldrPluginBaytrail* tmpPlugin = new XfstkDldrPluginBaytrail();
    if(tmpPlugin != NULL)
    {
        tmpPlugin->UserTabInterface.CurrentState = *State;
        tmpPlugin->SaveTabInterfaceSettings();
        delete tmpPlugin;
    }

    return;
}

bool XfstkDldrPluginOptionsInterface::VerifyBinaryFilePath(QString BinPath)
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

QString XfstkDldrPluginOptionsInterface::DetermineCurrentFileSearchPath(QString BinPath)
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

void XfstkDldrPluginOptionsInterface::ReportErrors()
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

void XfstkDldrPluginOptionsInterface::on_ClearAllStoredPaths_clicked()
{
    this->CurrentState.IFWIPath = "N/A";
    this->ui->IFWIPath->setText("N/A");
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
