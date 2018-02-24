#include "QualComMobileWidget.h"
#include "ui_QualComMobileWidget.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <Windows.h>
#include <tchar.h>
#include "serialport.h"
#include "sahara.h"
#include <QFileDialog>

//Only List COM port information for desktop version
#ifndef ARM
#include "setupapi.h"
#define INITGUID 1    // This is needed to properly define the GUID's in devpkey.h
#include "devpkey.h"
#endif //ARM

QualComMobileWidget::QualComMobileWidget(QTabWidget *parent, MainWindow *window) :
    TabWidgetBase(3, tr("&Qualcom Widget"), parent),
    ui(new Ui::QualComMobileWidget),
    main_window(window)
{
  ui->setupUi(this);
  ui->checkBox_QcOnly->setChecked(true);
  ui->checkBox_AutoBoot->setChecked(true);
  ui->comboBox_ListCom->addItem("- Select a Port -");
  ui->comboBox_BootSelect->addItem("- Select a Boot -");
  ui->comboBox_BootSelect->addItem("- Select a Boot MSM8937 -");
  ui->comboBox_BootSelect->addItem("- Select a Boot MSM8936 -");
  ui->comboBox_BootSelect->addItem("- Select a Boot MSM8916 -");
  ui->comboBox_BootSelect->addItem("- Select a Boot MSM8974 -");
  ui->groupBox_BootSelect->setHidden(true);
  ui->comboBox_BootSelect->setHidden(true);
  ui->pushButton_BootSelect->setHidden(true);
  ui->groupBox_RomSelect->setHidden(true);
  ui->radioButton_ReadInfo->setChecked(true);


     //foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
     // ui->comboBox_ListCom->addItem(info.portName());

  connect(ui->checkBox_QcOnly, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_Com_Reload_clicked()));
  connect(ui->checkBox_AutoBoot, SIGNAL(clicked(bool)), this, SLOT(AutoBootUpdateUI()));
  connect(ui->radioButton_Flash, SIGNAL(clicked(bool)), this, SLOT(FlashUpdateUI()));
  connect(ui->radioButton_ReadInfo, SIGNAL(clicked(bool)), this, SLOT(ReadInfoUpdateUI()));
}
QualComMobileWidget::~QualComMobileWidget()
{
    delete ui;
}
void QualComMobileWidget::LockOnUI()
{
    //enableControl(false);
}

void QualComMobileWidget::DoFinished()
{
    //enableControl(true);
}

void QualComMobileWidget::UpdateUI()
{
    ui->retranslateUi(this);
}


void QualComMobileWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
    QString label = "ADB";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

    tab_widget->setTabText(index, label);
}

void QualComMobileWidget::SetShortCut(int , const QString &)
{

}
int QualComMobileWidget::updatePortList()
{
#ifndef ARM
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	DEVPROPTYPE ulPropertyType = DEVPROP_TYPE_STRING;
	DWORD dwSize;
#endif //ARM
	ui->plainTextEdit->clear();
	log(kLogTypeInfo, QString::fromUtf8("  Đang tìm kiếm thiết bị QualCom  ...\n"));
#ifndef ARM
	if (hDevInfo != INVALID_HANDLE_VALUE) {
		// Successfully got a list of ports
		for (int i = 0; ; i++) {
			WCHAR szBuffer[512];
			SP_DEVINFO_DATA DeviceInfoData;
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

			wchar_t *Htcom;
			if (ui->checkBox_QcOnly->isChecked()){
				Htcom = L"QDLoader 9008";
			}
			else{
				Htcom = L"";
			}

			if (!SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData) && (GetLastError() == ERROR_NO_MORE_ITEMS)) {
				// No more ports

				break;
			}
			// successfully found entry print out the info
			if (SetupDiGetDeviceProperty(hDevInfo, &DeviceInfoData, &DEVPKEY_Device_FriendlyName, &ulPropertyType, (BYTE*)szBuffer, sizeof(szBuffer), &dwSize, 0)) {

				if ((GetLastError() == ERROR_SUCCESS) && wcsstr(szBuffer, Htcom) != NULL) {
					log(kLogTypeInfo, QString::fromUtf8("  Đã tìm thấy thiết bị ...\n"));
					//convert from wide char to narrow char array
					char ch[512];
					char DefChar = ' ';
					WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, ch, 512, &DefChar, NULL);
					//A std:string  using the char* constructor.
					std::string ss(ch);
					QString qstr = QString::fromStdString(ss);
					log(kLogTypeError, "  " + qstr);
					ui->comboBox_ListCom->addItem(qstr);
					WCHAR *port = wcsstr(szBuffer, L"COM");
					if (port != NULL) {
						SerialPort spTemp;
						pbl_info_t pbl_info;
						spTemp.Open(_wtoi((port + 3)));
						Sahara sh(&spTemp);
						int status = sh.DumpDeviceInfo(&pbl_info);
						if (status == ERROR_SUCCESS) {
							// wprintf(L": SERIAL=0x%x : HW_ID=0x%x", pbl_info.serial, pbl_info.msm_id);
							char ch[512];
							char DefChar = ' ';
							WideCharToMultiByte(CP_ACP, 0, port, -1, ch, 512, &DefChar, NULL);
							//A std:string  using the char* constructor.
							std::string ss(ch);
							QString qstr = QString::fromStdString(ss);
							log(kLogTypeError, QString::fromUtf8("  Đã kết nối với cổng :   ") + qstr);
							QString msg;
							log(kLogTypeInfo, msg.sprintf("  SERIAL=0x%x  :  HW_ID=0x%x   ", pbl_info.serial, pbl_info.msm_id));

							if (pbl_info.msm_id == 0x560e1){
								log(kLogTypeError, QString::fromUtf8("  Tên Chíp : MSM8937 "));
							}
							else{
								log(kLogTypeError, QString::fromUtf8("  Tên Chíp : chua xac nhan "));
							}
						}
					}
					log(kLogTypeInfo, "\n\n");
				}
			}
		}
	}
#endif //ARM
	return ERROR_SUCCESS;
}

void QualComMobileWidget::log(int type, const char* message) {
    QString tmp = "gray";

    switch (type) {
    case kLogTypeDebug:		tmp = "gray";	break;
    case kLogTypeError:		tmp = "red";	break;
    case kLogTypeWarning:	tmp = "orange";	break;
    case kLogTypeInfo:		tmp = "green";	break;
    }

    ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message));
}

void QualComMobileWidget::log(int type, std::string message)
{
    QString tmp = "gray";

    switch (type) {
    case kLogTypeDebug:		tmp = "gray";	break;
    case kLogTypeError:		tmp = "red";	break;
    case kLogTypeWarning:	tmp = "orange";	break;
    case kLogTypeInfo:		tmp = "green";	break;
    }

    ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.c_str()));
}

void QualComMobileWidget::log(int type, QString message)
{

    QString tmp = "gray";

    switch (type) {
        case kLogTypeDebug:		tmp = "gray";	break;
        case kLogTypeError:		tmp = "red";	break;
        case kLogTypeWarning:	tmp = "orange";	break;
        case kLogTypeInfo:		tmp = "green";	break;
    }

    ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.toStdString().c_str()));
}

void QualComMobileWidget::on_pushButton_Com_Connec_clicked()
{
	ui->comboBox_ListCom->clear();
	updatePortList();

}
void QualComMobileWidget::on_pushButton_Com_Reload_clicked()
{
	ui->comboBox_ListCom->clear();
	updatePortList();
}
void QualComMobileWidget::on_pushButton_BootSelect_clicked()
{
	QString quacomboot = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file boot"), "d:\\", "*.mbn");
	ui->comboBox_BootSelect->clear();
	ui->comboBox_BootSelect->addItem(quacomboot);
}
void QualComMobileWidget::AutoBootUpdateUI()
{
	if (ui->checkBox_AutoBoot->isChecked()){

		ui->groupBox_BootSelect->setHidden(true);
		ui->comboBox_BootSelect->setHidden(true);
		ui->pushButton_BootSelect->setHidden(true);
	}
	else{

		ui->groupBox_BootSelect->setHidden(false);
		ui->comboBox_BootSelect->setHidden(false);
		ui->pushButton_BootSelect->setHidden(false);
	}

}
void QualComMobileWidget::ReadInfoUpdateUI()
{
	ui->groupBox_RomSelect->setHidden(true);
}
void QualComMobileWidget::FlashUpdateUI()
{

	ui->groupBox_RomSelect->setHidden(false);
}

