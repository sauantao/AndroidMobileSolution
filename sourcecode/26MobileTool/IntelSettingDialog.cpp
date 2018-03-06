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

