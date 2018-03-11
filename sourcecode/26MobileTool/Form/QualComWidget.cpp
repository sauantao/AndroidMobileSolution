#include "QualComWidget.h"
#include "ui_QualComWidget.h"
#include <iostream>
#include <string>
#include <QFileDialog>
#include <QString>
#include <Qchar>

//Only List COM port information for desktop version
#ifndef ARM
#include "setupapi.h"
#define INITGUID 1    // This is needed to properly define the GUID's in devpkey.h
#include "devpkey.h"
#endif //ARM

using namespace std;
#define CLASS_DLOAD  0
#define CLASS_SAHARA 1
static SerialPort m_port;
static int m_chipset = 8974;
static int m_protocol = FIREHOSE_PROTOCOL;
static int m_class = CLASS_SAHARA;
static int m_sector_size = 512;
static bool m_emergency = false;
static bool m_verbose = false;
static fh_configure_t m_cfg = { 4, "emmc", false, false, true, -1,1024 * 1024 };
int dnum = -1;
QString folder = NULL;

QualComWidget::QualComWidget(QTabWidget *parent, MainWindow *window) :
    TabWidgetBase(3, tr("&Qualcom Widget"), parent),
    ui(new Ui::QualComWidget),
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
QualComWidget::~QualComWidget()
{
    delete ui;
}
void QualComWidget::LockOnUI()
{
    //enableControl(false);
}

void QualComWidget::DoFinished()
{
    //enableControl(true);
}

void QualComWidget::UpdateUI()
{
    ui->retranslateUi(this);
}


void QualComWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
    QString label = "ADB";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

    tab_widget->setTabText(index, label);
}

void QualComWidget::SetShortCut(int , const QString &)
{

}
int QualComWidget::updatePortList()
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
					//log(kLogTypeInfo, QString::fromUtf8("  Đã tìm thấy thiết bị ...\n"));
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
							//log(kLogTypeError, QString::fromUtf8("  Đã kết nối với cổng :   ") + qstr);
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
int QualComWidget::QcupdatePortList()
{
#ifndef ARM
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	DEVPROPTYPE ulPropertyType = DEVPROP_TYPE_STRING;
	DWORD dwSize;
#endif //ARM
	ui->plainTextEdit->clear();
	log(kLogTypeInfo, QString::fromUtf8("Đang tìm kiếm thiết bị QualCom  ...\n"));
#ifndef ARM
	if (hDevInfo != INVALID_HANDLE_VALUE) {
		// Successfully got a list of ports
		for (int i = 0; ; i++) {
			WCHAR szBuffer[512];
			SP_DEVINFO_DATA DeviceInfoData;
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

			wchar_t *Htcom;
			if (ui->checkBox_QcOnly->isChecked()) {
				Htcom = L"QDLoader 9008";
			}
			else {
				Htcom = L"";
			}

			if (!SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData) && (GetLastError() == ERROR_NO_MORE_ITEMS)) {
				// No more ports

				break;
			}
			// successfully found entry print out the info
			if (SetupDiGetDeviceProperty(hDevInfo, &DeviceInfoData, &DEVPKEY_Device_FriendlyName, &ulPropertyType, (BYTE*)szBuffer, sizeof(szBuffer), &dwSize, 0)) {

				if ((GetLastError() == ERROR_SUCCESS) && wcsstr(szBuffer, Htcom) != NULL) {
					//log(kLogTypeInfo, QString::fromUtf8("  Đã tìm thấy thiết bị ...\n"));
					//convert from wide char to narrow char array
					char ch[512];
					char DefChar = ' ';
					WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, ch, 512, &DefChar, NULL);
					//A std:string  using the char* constructor.
					std::string ss(ch);
					QString qstr = QString::fromStdString(ss);
					log(kLogTypeError, "  " + qstr);
					ui->comboBox_ListCom->addItem(qstr);
					log(kLogTypeInfo, "\n\n");
				}
			}
		}
	}
#endif //ARM
	return ERROR_SUCCESS;
}

void QualComWidget::log(int type, const char* message) {
    QString tmp = "gray";

    switch (type) {
    case kLogTypeDebug:		tmp = "gray";	break;
    case kLogTypeError:		tmp = "red";	break;
    case kLogTypeWarning:	tmp = "orange";	break;
    case kLogTypeInfo:		tmp = "green";	break;
    }

    ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message));
}

void QualComWidget::log(int type, std::string message)
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

void QualComWidget::log(int type, QString message)
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

void QualComWidget::on_pushButton_Com_Connec_clicked()
{

	QString intdnum = ui->comboBox_ListCom->currentText();

	if (!(intdnum.contains("QDLoader 9008")))
	{
		log(kLogTypeInfo, QString::fromUtf8("Không có thiết bị nào được kết nối .\nHãy kiểm tra lại kết nối cáp thiết bị , driver ...\nSau đó bấm nút làm mới cổng com & thử lại "));
	}
	else
	{
		QString intdnum = ui->comboBox_ListCom->currentText();
		QChar com1 = intdnum.at(34); QChar com2 = intdnum.at(35);
		QString comtemp1 = "";
		comtemp1.append(com1);
		comtemp1.append(com2);
		int comtemp = comtemp1.toInt();
		QString str = (QString::fromUtf8("  Kết nối với cổng : ") + QString::number(comtemp));
		dnum = comtemp;
		ui->pushButton_Com_Connec->setEnabled(false);
	}
}
void QualComWidget::on_pushButton_Com_Reload_clicked()
{
	ui->comboBox_ListCom->clear();
	QcupdatePortList();
	ui->pushButton_Com_Connec->setEnabled(true);
	dnum = -1;
}
void QualComWidget::on_pushButton_BootSelect_clicked()
{
	QString quacomboot = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file boot"), "d:\\", "*.mbn");
	if (quacomboot.isEmpty()){
		log(kLogTypeInfo, QString::fromUtf8("Chưa chọn file boot"));

	}
	else{
		ui->comboBox_BootSelect->clear();
		ui->comboBox_BootSelect->addItem(quacomboot);
	}

}
void QualComWidget::on_pushButton_RomBootFolder_clicked()
{
	QString RomBootFolder = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file boot"), "d:\\", "*.mbn");
	if (RomBootFolder.isNull()){
		log(kLogTypeInfo, QString::fromUtf8("Chưa chọn file boot"));

	}
	else
	{
		ui->comboBox_BootSelect->clear();
		ui->comboBox_BootSelect->addItem(RomBootFolder);
		 folder = RomBootFolder;
		 folder.chop(28);
         ui->lineEdit_FolderRom->setText(folder);
	}
}
void QualComWidget::on_pushButton_RawXmlPatchXml_clicked()
{
	QString rawprogram0 = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file Raw Program"), folder, "*.xml");
	
	if (rawprogram0.isNull()) {
		log(kLogTypeInfo, QString::fromUtf8("Chưa chọn file Raw Program xml"));

	}
	else{

		ui->lineEdit_RawProgramXml->setText(rawprogram0);
	}

	QString patch = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file Patch "), folder, "*.xml");
	if (patch.isNull()) {
		log(kLogTypeInfo, QString::fromUtf8("Chưa chọn file Raw Patch xml"));

	}
	else{

		ui->lineEdit_PatchXml->setText(patch);
	}
}
void QualComWidget::AutoBootUpdateUI()
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
void QualComWidget::ReadInfoUpdateUI()
{
	ui->groupBox_RomSelect->setHidden(true);
}
void QualComWidget::FlashUpdateUI()
{

	ui->groupBox_RomSelect->setHidden(false);
}
void QualComWidget::StringToByte(TCHAR **szSerialData, BYTE *data, int len)
{
	for (int i = 0; i < len; i++) {
		TCHAR *hex = szSerialData[i];
		if (wcsncmp(hex, L"0x", 2) == 0) {
			BYTE val1 = (BYTE)(hex[2] - '0');
			BYTE val2 = (BYTE)(hex[3] - '0');
			if (val1 > 9) val1 = val1 - 7;
			if (val2 > 9) val2 = val2 - 7;
			data[i] = (val1 << 4) + val2;
		}
		else {
			data[i] = (BYTE)_wtoi(szSerialData[i]);
		}
	}
}
int QualComWidget::RawSerialSend(int dnum, TCHAR **szSerialData, int len)
{
	int status = ERROR_SUCCESS;
	BYTE data[256];

	// Make sure the number of bytes of data we are trying to send is valid
	if (len < 1 || len > sizeof(data)) {
		return ERROR_INVALID_PARAMETER;
	}

	m_port.Open(dnum);
    StringToByte(szSerialData, data, len);
	status = m_port.Write(data, len);
	return status;
}
int QualComWidget::EraseDisk(uint64 start, uint64 num, int dnum, TCHAR *szPartName)
{
	int status = ERROR_SUCCESS;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Connected to flash programmer, starting download\n");
		fh.WipeDiskContents(start, num, szPartName);
	}
	else {
		DiskWriter dw;
		// Initialize and print disk list
		dw.InitDiskList(false);

		status = dw.OpenDevice(dnum);
		if (status == ERROR_SUCCESS) {
			wprintf(L"Successfully opened volume\n");
			wprintf(L"Erase at start_sector %I64d: num_sectors: %I64d\n", start, num);
			status = dw.WipeDiskContents(start, num, szPartName);
		}
		dw.CloseDevice();
	}
	return status;
}
int QualComWidget::WipeDisk(int dnum)
{
	DiskWriter dw;
	int status;

	// Initialize and print disk list
	dw.InitDiskList();

	status = dw.OpenDevice(dnum);
	if (status == ERROR_SUCCESS) {
		wprintf(L"Successfully opened volume\n");
		wprintf(L"Wipping GPT and MBR\n");
		status = dw.WipeLayout();
	}
	dw.CloseDevice();
	return status;
}
int QualComWidget::ReadGPT(int dnum)
{
	int status;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Connected to flash programmer, starting download\n");
		fh.ReadGPT(true);
	}
	else {
		DiskWriter dw;
		dw.InitDiskList();
		status = dw.OpenDevice(dnum);

		if (status == ERROR_SUCCESS) {
			status = dw.ReadGPT(true);
		}

		dw.CloseDevice();
	}
	return status;
}
int QualComWidget::WriteGPT(int dnum, TCHAR *szPartName, TCHAR *szBinFile)
{
	int status;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Connected to flash programmer, starting download\n");
		status = fh.WriteGPT(szPartName, szBinFile);
	}
	else {
		DiskWriter dw;
		dw.InitDiskList();
		status = dw.OpenDevice(dnum);
		if (status == ERROR_SUCCESS) {
			status = dw.WriteGPT(szPartName, szBinFile);
		}
		dw.CloseDevice();
	}
	return status;
}
int QualComWidget::ResetDevice()
{
	Dload dl(&m_port);
	int status = ERROR_SUCCESS;
	if (status != ERROR_SUCCESS) return status;
	status = dl.DeviceReset();
	return status;
}
int QualComWidget::RawDiskProgram(TCHAR **pFile, TCHAR *oFile, uint64 dnum)
{
	DiskWriter dw;
	int status = ERROR_SUCCESS;

	// Depending if we want to write to disk or file get appropriate handle
	if (oFile != NULL) {
		status = dw.OpenDiskFile(oFile, dnum);
	}
	else {
		int disk = dnum & 0xFFFFFFFF;
		// Initialize and print disk list
		dw.InitDiskList();
		status = dw.OpenDevice(disk);
	}
	if (status == ERROR_SUCCESS) {
		wprintf(L"Successfully opened disk\n");
		for (int i = 0; pFile[i] != NULL; i++) {
			Partition p(dw.GetNumDiskSectors());
			status = p.PreLoadImage(pFile[i]);
			if (status != ERROR_SUCCESS) return status;
			status = p.ProgramImage(&dw);
		}
	}

	dw.CloseDevice();
	return status;
}
int QualComWidget::RawDiskDump(uint64 start, uint64 num, TCHAR *oFile, int dnum, TCHAR *szPartName)
{
	DiskWriter dw;
	int status = ERROR_SUCCESS;

	// Get extra info from the user via command line
	wprintf(L"Dumping at start sector: %I64d for sectors: %I64d to file: %s\n", start, num, oFile);
	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		if (status != ERROR_SUCCESS) return status;
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Connected to flash programmer, starting dump\n");
		status = fh.DumpDiskContents(start, num, oFile, 0, szPartName);
	}
	else {
		// Initialize and print disk list
		dw.InitDiskList();
		status = dw.OpenDevice(dnum);
		if (status == ERROR_SUCCESS) {
			wprintf(L"Successfully opened volume\n");
			status = dw.DumpDiskContents(start, num, oFile, 0, szPartName);
		}
		dw.CloseDevice();
	}
	return status;
}
int QualComWidget::DumpDeviceInfo(void)
{
	int status = ERROR_SUCCESS;
	Sahara sh(&m_port);
	if (m_protocol == FIREHOSE_PROTOCOL) {
		pbl_info_t pbl_info;
		status = sh.DumpDeviceInfo(&pbl_info);
		if (status == ERROR_SUCCESS) {
			QString msg;
			log(kLogTypeInfo, msg.sprintf("SerialNumber: 0x%08x\n", pbl_info.serial));
			log(kLogTypeInfo, msg.sprintf("MSM_HW_ID: 0x%08x\n", pbl_info.msm_id));
			log(kLogTypeInfo, msg.sprintf("OEM_PK_HASH: 0x"));
			//wprintf(L"SerialNumber: 0x%08x\n", pbl_info.serial);
			//wprintf(L"MSM_HW_ID: 0x%08x\n", pbl_info.msm_id);
			//wprintf(L"OEM_PK_HASH: 0x");
			for (int i = 0; i < sizeof(pbl_info.pk_hash); i++) {
				log(kLogTypeInfo, msg.sprintf("%02x", pbl_info.pk_hash[i]));
				//wprintf(L"%02x", pbl_info.pk_hash[i]);
			}
			log(kLogTypeInfo, msg.sprintf("\nSBL SW Version: 0x%08x\n", pbl_info.pbl_sw));
			//wprintf(L"\nSBL SW Version: 0x%08x\n", pbl_info.pbl_sw);
		}
	}
	else {
		QString msg;
		log(kLogTypeInfo, msg.sprintf("Only devices with Sahara support this information\n"));
		//wprintf(L"Only devices with Sahara support this information\n");
		status = ERROR_INVALID_PARAMETER;
	}

	return status;
}
int QualComWidget::LoadFlashProg(TCHAR *mprgFile)
{
	QString msg;
	int status = ERROR_SUCCESS;
	// This is PBL so depends on the chip type

	if (m_chipset == 8974) {
		Sahara sh(&m_port);
		if (status != ERROR_SUCCESS) return status;
		status = sh.ConnectToDevice(true, 0);
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, msg.sprintf("Downloading flash programmer: %s\n", mprgFile));
		//wprintf(L"Downloading flash programmer: %s\n", mprgFile);
		status = sh.LoadFlashProg(mprgFile);
		if (status != ERROR_SUCCESS) return status;
	}
	else {
		Dload dl(&m_port);
		if (status != ERROR_SUCCESS) return status;
		status = dl.IsDeviceInDload();
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, msg.sprintf("Downloading flash programmer: %s\n", mprgFile));
		//wprintf(L"Downloading flash programmer: %s\n", mprgFile);
		status = dl.LoadFlashProg(mprgFile);
		if (status != ERROR_SUCCESS) return status;
	}
	return status;
}
void QualComWidget::on_toolButton_Start_clicked()
{

	//int dnum = 20;
	int status = 0;
	bool bEmergdl = FALSE;
	TCHAR *szOutputFile = NULL;
	TCHAR *szXMLFile[8] = { NULL };
	TCHAR **szSerialData = { NULL };
	DWORD dwXMLCount = 0;
	TCHAR *szFFUImage = NULL;
	TCHAR *szFlashProg = NULL;
	TCHAR *szSingleImage = NULL;
	TCHAR *szPartName = NULL;
	//emmc_cmd_e cmd = EMMC_CMD_NONE;
	uint64 uiStartSector = 0;
	uint64 uiNumSectors = 0;
	uint64 uiOffset = 0x40000000;
	DWORD dwGPP1 = 0, dwGPP2 = 0, dwGPP3 = 0, dwGPP4 = 0;
	bool bGppQuiet = FALSE;

     // m_port.Open(dnum);
	 //status = DumpDeviceInfo();
	//QString qccomname = "QDLoader 9008";
	if (ui->radioButton_ReadInfo->isChecked())
	{
		QString intdnum = ui->comboBox_ListCom->currentText();
		QString temp = QTime::currentTime().toString();
		temp.append(QString(" - "));
		temp.append(QString::fromUtf8("Không có thiết bị nào được kết nối .\nHãy kiểm tra lại kết nối cáp thiết bị , driver ...\nSau đó bấm nút làm mới cổng com & thử lại\n "));

		if (!(intdnum.contains("QDLoader 9008"))) {
			log(kLogTypeInfo, temp);
		}
		else {
			if (dnum == -1) {
				log(kLogTypeInfo, QString::fromUtf8("Hãy bấm kết nối để thiết lập kết nối cổng COM. "));
			}
			if (!(dnum == -1)) {
				QString dnumtemp = QString::number(dnum);
				//log(kLogTypeWarning, str);
				log(kLogTypeWarning, QString::fromUtf8("Kết nối với cổng COM : ") + dnumtemp);
			}
		}
		m_port.Open(dnum);
		//status = 
		DumpDeviceInfo();
	}
	if (ui->radioButton_Flash->isChecked()){
		log(kLogTypeInfo, QString::fromUtf8("Flash"));
	}
}
