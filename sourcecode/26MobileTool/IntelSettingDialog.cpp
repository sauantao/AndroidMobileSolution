#include "IntelSettingDialog.h"
#include "ui_IntelSettingDialog.h"



IntelSettingDialog::IntelSettingDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::IntelSettingDialog)
{
	ui->setupUi(this);
}

IntelSettingDialog::~IntelSettingDialog()
{
	delete ui;
}
//QTabWidget *IntelSettingDialog::GetTabInterface()
//{
//	return  this->ui->OptionsInterface;
//	
//}

void IntelSettingDialog::changeEvent(QEvent *e)
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
void IntelSettingDialog::UserInterfaceChanged(UserInterfaceState *State)
{
	//this->CurrentState.FWDnXPath = State->FWDnXBin;
	//this->CurrentState.IFWIPath = State->IFWIBin;
	//this->CurrentState.OSDnXPath = State->OSDnXBin;
	//this->CurrentState.OSIPath = State->OSImageBin;
	//this->CurrentState.EnableGpFlagOverride = State->EnableGpFlagOverride;
	//this->CurrentState.GPFlagOverrideValue = State->GPFlagOverrideValue;
	//this->CurrentState.LoggingPath = State->LoggingPath;
	//this->CurrentState.EnableProvisionCount = State->EnableProvisionCount;
	//this->CurrentState.EnableLogging = State->EnableLogging;
	//this->CurrentState.ProvisionCount = State->ProvisionCount;
	//this->CurrentState.DesktopDir = State->DesktopDir;
	//this->CurrentState.USBTimeout = State->USBTimeout;
	//this->CurrentState.SoftfuseInclude = State->SoftfuseInclude;
	//this->CurrentState.SoftfusesPath = State->SoftfusesPath;

	this->ui->FWDnXPath->setText(this->CurrentState.FWDnXPath);
	this->ui->IFWIPath->setText(this->CurrentState.IFWIPath);
	this->ui->OSDnXPath->setText(this->CurrentState.OSDnXPath);
	this->ui->OSImagePath->setText(this->CurrentState.OSIPath);
	this->ui->SoftfusesPath->setText(this->CurrentState.SoftfusesPath);
	this->ui->GPFlagOverrideValue->setText(this->CurrentState.GPFlagOverrideValue);
	this->ui->UsbTimeoutOption->setText(this->CurrentState.USBTimeout);
	if (this->CurrentState.EnableGpFlagOverride) {
		this->ui->GPFlagOverrideEnable->setCheckState(Qt::Checked);
	}
	else {
		this->ui->GPFlagOverrideEnable->setCheckState(Qt::Unchecked);
	}
	if (this->CurrentState.EnableProvisionCount) {
		this->ui->ProvisionCountEnabled->setCheckState(Qt::Checked);
	}
	else {
		this->ui->ProvisionCountEnabled->setCheckState(Qt::Unchecked);
	}
	if (this->CurrentState.EnableLogging) {
		this->ui->EnableLogging->setCheckState(Qt::Checked);
	}
	else {
		this->ui->EnableLogging->setCheckState(Qt::Unchecked);
	}
	this->ui->LoggingPath->setText(this->CurrentState.LoggingPath);

	if (this->CurrentState.SoftfuseInclude) {
		this->ui->SoftfuseInclude->setCheckState(Qt::Checked);
	}
	else {
		this->ui->SoftfuseInclude->setCheckState(Qt::Unchecked);
	}

	//XfstkDldrPluginCloverviewPlus* tmpPlugin = new XfstkDldrPluginCloverviewPlus();
	/*if(tmpPlugin != NULL)
	{
	tmpPlugin->UserTabInterface.CurrentState = *State;
	tmpPlugin->SaveTabInterfaceSettings();
	delete tmpPlugin;
	}*/
	return;
}

bool IntelSettingDialog::VerifyBinaryFilePath(QString BinPath)
{
	this->LastError.clear();

	if (BinPath == "N/A") {
		return true;
	}

	if (BinPath.endsWith(".bin", Qt::CaseInsensitive)) {
		if (QFile::exists(BinPath)) {
			QStringList splitter;
			QString Bin;
			QString Path;
			splitter = BinPath.split("/");
			if (splitter.length() != 0) {
				Bin = splitter.last();
			}
			splitter = BinPath.split(Bin);
			if (splitter.length() != 0) {
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
		if (BinPath == "") {
			return false;
		}
		else {
			this->LastError = "File type must be .bin.";
		}
	}
	this->ReportErrors();
	return false;
}

void IntelSettingDialog::ReportErrors()
{
	if (!this->CurrentState.SuppressErrors) {
		this->LineEditWA = !(this->LineEditWA);
		if (this->LineEditWA) {
			if (this->LastError.length() != 0) {
				QMessageBox msgBox;
				msgBox.setText(this->LastError);
				msgBox.exec();
			}
		}
	}
}

QString IntelSettingDialog::DetermineCurrentFileSearchPath(QString BinPath)
{
	QStringList splitter;
	QString Bin;
	QString Path;
	QFileInfo Dir = QFileInfo(this->CurrentState.CurrentSearchDir);
	this->CurrentState.SuppressErrors = true;
	if (this->CurrentState.CurrentSearchDir == "N/A" || !Dir.isDir()) {
		if (BinPath != "N/A" && this->VerifyBinaryFilePath(BinPath)) {
			splitter = BinPath.split("/");
			if (splitter.length() != 0) {
				Bin = splitter.last();
			}
			splitter = BinPath.split(Bin);
			if (splitter.length() != 0) {
				Path = splitter.first();
			}
			this->CurrentState.CurrentSearchDir = Path;
		}
		else {
			//this->CurrentState.CurrentSearchDir = QDesktopServices::displayName(QDesktopServices::DesktopLocation);
		}
	}
	this->CurrentState.SuppressErrors = false;
	return this->CurrentState.CurrentSearchDir;
}

void IntelSettingDialog::on_ClearFWDnXPath_clicked()
{
	this->CurrentState.FWDnXPath = "N/A";
	this->ui->FWDnXPath->setText("N/A");
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_ClearIFWIPath_clicked()
{
	this->CurrentState.IFWIPath = "N/A";
	this->ui->IFWIPath->setText("N/A");
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_ClearOSDnXPath_clicked()
{
	this->CurrentState.OSDnXPath = "N/A";
	this->ui->OSDnXPath->setText("N/A");
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_ClearOSImagePath_clicked()
{
	this->CurrentState.OSIPath = "N/A";
	this->ui->OSImagePath->setText("N/A");
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_ClearAllStoredPaths_clicked()
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

void IntelSettingDialog::on_GPFlagOverrideEnable_toggled(bool checked)
{
	if (checked) {
		this->CurrentState.EnableGpFlagOverride = true;
	}
	else {
		this->CurrentState.EnableGpFlagOverride = false;
	}
	this->CurrentState.GPFlagOverrideValue = this->ui->GPFlagOverrideValue->text();
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_GPFlagOverrideValue_editingFinished()
{
	this->CurrentState.GPFlagOverrideValue = this->ui->GPFlagOverrideValue->text();
	this->OptionsInterfaceChanged(&(this->CurrentState));
}
void IntelSettingDialog::on_UsbTimeoutOption_editingFinished()
{
	this->CurrentState.USBTimeout = this->ui->UsbTimeoutOption->text();
	this->OptionsInterfaceChanged(&(this->CurrentState));
}


void IntelSettingDialog::on_ProvisionCountEnabled_toggled(bool checked)
{
	if (checked) {
		this->CurrentState.EnableProvisionCount = true;
	}
	else {
		this->CurrentState.EnableProvisionCount = false;
	}
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_EnableLogging_toggled(bool checked)
{
	if (checked) {
		this->CurrentState.EnableLogging = true;
	}
	else {
		this->CurrentState.EnableLogging = false;
	}
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_LoggingPath_editingFinished()
{
	QString dir = this->ui->LoggingPath->text();
	QDir valid_Dir = QDir(dir);
	if (!valid_Dir.exists())
	{
		this->ui->LoggingPath->setFocus();
		this->ui->LoggingPath->setText(this->CurrentState.LoggingPath);
		this->ui->LoggingPath->clearFocus();
		QMessageBox msgBox;
		msgBox.setText("Invalid Log Directory");
		msgBox.exec();
	}
	else
	{
		this->CurrentState.LoggingPath = dir;
		this->OptionsInterfaceChanged(&(this->CurrentState));
	}
}

void IntelSettingDialog::on_BrowseLoggingPath_clicked()
{
	QString Path = this->ui->LoggingPath->text();
	this->ui->LoggingPath->setFocus();
	this->ui->LoggingPath->setText(this->OpenFile.getExistingDirectory(NULL, "Log File Path", Path));
	this->ui->LoggingPath->clearFocus();
	this->on_LoggingPath_editingFinished();
}

void IntelSettingDialog::on_RestoreDefaultLogPath_clicked()
{
	this->ui->LoggingPath->setText(this->CurrentState.DesktopDir);
	this->CurrentState.LoggingPath = this->CurrentState.DesktopDir;
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_ResetProvisionCount_clicked()
{
	this->CurrentState.ProvisionCount = QString("0");
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_SoftfusePath_editingFinished()
{
	this->CurrentState.SoftfusesPath = this->ui->SoftfusesPath->text();
	this->OptionsInterfaceChanged(&(this->CurrentState));
}

void IntelSettingDialog::on_BrowseSoftfusePath_clicked()
{
	QString Path = this->DetermineCurrentFileSearchPath(this->ui->SoftfusesPath->text());
	this->ui->SoftfusesPath->setFocus();
	this->ui->SoftfusesPath->setText(this->OpenFile.getOpenFileName(NULL, "Softfuse Bin File", Path));
	this->ui->SoftfusesPath->clearFocus();
	this->on_SoftfusePath_editingFinished();
}

void IntelSettingDialog::on_SoftfuseInclude_toggled(bool checked)
{
	if (checked) {
		this->CurrentState.SoftfuseInclude = true;
	}
	else {
		this->CurrentState.SoftfuseInclude = false;
	}
	this->OptionsInterfaceChanged(&(this->CurrentState));
}
