#include "MainWindow.h"
#include <QSerialPortInfo>
#include <QString>
#include "tchar.h"
#include <winerror.h>
#include <windows.h>
#include <iostream>
#include <QFileDialog>
#include "protocol.h"
//#include "CheckHeader.h"
#include <QtDebug>
#include <QtGui>
#include <QTextCodec>
#include "cmdwidget.h"
#include "adbwidget.h"
#include "emmcrawwidget.h"
#include "QualComMobileWidget.h"
#include "AsusWidget.h"

using namespace std;

//Only List COM port information for desktop version
#ifndef ARM
#include "setupapi.h"
#define INITGUID 1    // This is needed to properly define the GUID's in devpkey.h
#include "devpkey.h"
#endif //ARM

static const QString PColorRed(" QProgressBar::chunk{background-color: red} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorGreen(" QProgressBar::chunk{background-color: green} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorBlue(" QProgressBar::chunk{background-color: blue} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorYellow(" QProgressBar::chunk{background-color: yellow} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorDarkRed(" QProgressBar::chunk{background-color: darkRed} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorDarkMagenta(" QProgressBar::chunk{background-color: darkMagenta} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorDarkCyan(" QProgressBar::chunk{background-color: darkCyan} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorDarkBlue(" QProgressBar::chunk{background-color: darkBlue} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorMagenta(" QProgressBar::chunk{background-color: magenta} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorDarkGray(" QProgressBar::chunk{background-color: darkGray} QProgressBar {text-align: center; border-radius: 0px}");
static const QString PColorOrange("QProgressBar::chunk{background-color:rgba(255,170,127,255} QProgressBar {text-align:center; border-radius:0px}");
static const QString PColorBrown("QProgressBar::chunk{background-color:rgba(85,0,0,255} QProgressBar {text-align:center; border-radius:0px}");



static int m_protocol = FIREHOSE_PROTOCOL;
static int m_class = CLASS_SAHARA;
static int m_chipset = 8974;
static int m_sector_size = 512;
static bool m_emergency = false;
static bool m_verbose = false;
static SerialPort m_port;
static fh_configure_t m_cfg = { 4, "emmc", false, false, true, -1,1024 * 1024 };

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) 
{
	ui->setupUi(this);

	//ui->statusBar->setStyleSheet("color: blue;" "background - color: yellow;""selection-color: yellow;""selection-background-color: blue;");
	//statusBar->setStyleSheet("statusBar { background-color: yellow }");
	//ui->progressBar->setStyleSheet("{border: 2px solid grey;border - radius: 5px;}");
	//ui->progressBar->setStyleSheet(PColorMagenta);
	//storagePathLabel = new QLabel;
	//QString storagePath = QString::fromUtf8("Kiểm tra bản cập nhập");
	//storagePathLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);
	//storagePathLabel->setText(storagePath);
	//storagePathLabel->setTextFormat(Qt::RichText);
	//storagePathLabel->setOpenExternalLinks(true);
	//ui->statusBar->addPermanentWidget(storagePathLabel);

	CreateWidget();
	//ui->tableWidget->setHorizontalHeader(header_);
	//ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
	//ui->tableWidget->setColumnHidden(columnRegion, true);
	/*foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
	ui->comboBox->addItem(info.portName());*/
	//ui->checkBox_firehose->setChecked(true);

	//ui->textEdit->setHidden(true);

	mThread = new MyThread(this);
	// connect signal/slot
	connect(mThread, SIGNAL(valueChanged(int)),
		this, SLOT(onValueChanged(int)));
	connect(mThread, SIGNAL(process_changed(int)), ui->progressBar, SLOT(setValue(int)));

	//connect(ui->checkBox_firehose, SIGNAL(clicked(bool)), this, SLOT(ComReload()));
	//InitDiskListQc();
	DISK_SECTOR_SIZE = 512;
}
MainWindow::~MainWindow()
{
	while (!tab_widgets.empty())
	{
		TabWidgetBase* tab = tab_widgets.front();
		tab_widgets.pop_front();
		delete tab;
	}
}
void MainWindow::CreateWidget()
{
	cmd_widget = new CmdWidget(ui->tabWidget, this);
	adb_widget = new AdbWidget(ui->tabWidget, this);
	asus_widget = new AsusWidget(ui->tabWidget, this);

	//emmcraw_widget = new EmmcRawWidget(ui->tabWidget, this);
	qualcommobile_widget = new QualComMobileWidget(ui->tabWidget, this);

	tab_widgets.push_back(adb_widget);
	tab_widgets.push_back(cmd_widget);
	//tab_widgets.push_back(emmcraw_widget);
	tab_widgets.push_back(qualcommobile_widget);
	tab_widgets.push_back(asus_widget);

	for (std::list<TabWidgetBase*>::const_iterator it = tab_widgets.begin();
		it != tab_widgets.end(); ++it)
	{
		(*it)->Attach();
	}

	ui->tabWidget->setCurrentWidget(cmd_widget);
}
void MainWindow::onValueChanged(int count)
{
	//ui->label->setText(QString::number(count));
	//log(kLogTypeError,QString::fromUtf8("Dang tien hanh :")+QString::number(count));
}
void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
	if (column == ColumnLocation)
	{
		//choose_rom_file(row, ColumnLocation);
	}
}
// Start button
void MainWindow::on_pushButton_Start_clicked()
{
	mThread->start();
}

// Stop button
void MainWindow::on_pushButton_Stop_clicked()
{
	mThread->Stop = true;
}

void MainWindow::on_pushButton_QcBootSlect_clicked()
{
	QString qcboot = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chọn file Boot"), "d:\\", "*.mbn");
	//ui->lineEdit_FireHose->setText(qcboot);

}

void MainWindow::on_pushButton_RawProgramSlect_clicked()
{
	QString rawprogram0 = QFileDialog::getOpenFileName(this, "Chon file Rawprogram ", "d:\\", "*.xml");
	//ui->lineEdit_RawProgram->setText(rawprogram0);
}

void MainWindow::on_pushButton_PatchSelect_clicked()
{
	QString patch = QFileDialog::getOpenFileName(this, "Chon file Patch", "d:\\", "*.xml");
	//ui->lineEdit_PatchSelect->setText(patch);
}

int MainWindow::PrintHelp()
{
	QString str = QString::fromUtf8("Xin chào tất cả mọi người");

	appendLog(str, Qt::blue);
	return -1;
}
void MainWindow::StringToByte(TCHAR **szSerialData, BYTE *data, int len)
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
int MainWindow::RawSerialSend(int dnum, TCHAR **szSerialData, int len)
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
int MainWindow::LoadFlashProg(TCHAR *mprgFile)
{
	int status = ERROR_SUCCESS;
	// This is PBL so depends on the chip type

	if (m_chipset == 8974) {
		Sahara sh(&m_port);
		if (status != ERROR_SUCCESS) return status;
		status = sh.ConnectToDevice(true, 0);
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Downloading flash programmer: %s\n", mprgFile);
		status = sh.LoadFlashProg(mprgFile);
		if (status != ERROR_SUCCESS) return status;
	}
	else {
		Dload dl(&m_port);
		if (status != ERROR_SUCCESS) return status;
		status = dl.IsDeviceInDload();
		if (status != ERROR_SUCCESS) return status;
		wprintf(L"Downloading flash programmer: %s\n", mprgFile);
		status = dl.LoadFlashProg(mprgFile);
		if (status != ERROR_SUCCESS) return status;
	}
	return status;
}
int MainWindow::EraseDisk(uint64 start, uint64 num, int dnum, TCHAR *szPartName)
{
	int status = ERROR_SUCCESS;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		//wprintf(L"Connected to flash programmer, starting download\n");
		QString msg;
		msg = QString("Connected to flash programmer, starting download\n");
		//ui->textEdit->append(msg);
		fh.WipeDiskContents(start, num, szPartName);
	}
	else {
		DiskWriter dw;
		// Initialize and print disk list
		dw.InitDiskList(false);

		status = dw.OpenDevice(dnum);
		if (status == ERROR_SUCCESS) {
			//wprintf(L"Successfully opened volume\n");
			//ui->textEdit->append("Successfully opened volume\n");

			//wprintf(L"Erase at start_sector %I64d: num_sectors: %I64d\n",start, num);
			QString msg;
			msg = QString("Erase at start_sector %I64d: num_sectors: %I64d\n").arg(start).arg(num);
			status = dw.WipeDiskContents(start, num, szPartName);
		}
		dw.CloseDevice();
	}
	return status;
}
int MainWindow::DumpDeviceInfo(void)
{
	int status = ERROR_SUCCESS;
	Sahara sh(&m_port);
	if (m_protocol == FIREHOSE_PROTOCOL) {
		pbl_info_t pbl_info;
		status = sh.DumpDeviceInfo(&pbl_info);
		if (status == ERROR_SUCCESS) {
			//wprintf(L"SerialNumber: 0x%08x\n", pbl_info.serial);
			//wprintf(L"MSM_HW_ID: 0x%08x\n", pbl_info.msm_id);
			//wprintf(L"OEM_PK_HASH: 0x");
			QString msg;
			log(kLogTypeInfo, msg.sprintf("SerialNumber: 0x%08X", pbl_info.serial));
			log(kLogTypeInfo, msg.sprintf("MSM_HW_ID: 0x%08X", pbl_info.msm_id));
			if (pbl_info.msm_id == 0x000560E1)
			{
				log(kLogTypeError, "Ten chip : MSM8937");
				//ui->lineEdit_FireHose->setText("firehose_MSM8937.mbn");
			}
			log(kLogTypeInfo, msg.sprintf("OEM_PK_HASH: 0x"));
			for (int i = 0; i < sizeof(pbl_info.pk_hash); i++) {
				/* wprintf(L"%02x", pbl_info.pk_hash[i]);*/
				QString msg;
				//log(kLogTypeInfo, msg.sprintf("%02x",pbl_info.pk_hash[i]));

			}

			/*wprintf(L"\nSBL SW Version: 0x%08x\n", pbl_info.pbl_sw);*/
			log(kLogTypeInfo, msg.sprintf("SBL SW Version:: 0x%08x", pbl_info.pbl_sw));

		}
	}
	else {
		/*wprintf(L"Only devices with Sahara support this information\n");*/
		log(kLogTypeInfo, "Only devices with Sahara support this information");
		status = ERROR_INVALID_PARAMETER;
	}

	return status;
}
// Wipe out existing MBR, Primary GPT and secondary GPT
int MainWindow::WipeDisk(int dnum)
{
	DiskWriter dw;
	int status;

	// Initialize and print disk list
	dw.InitDiskList();

	status = dw.OpenDevice(dnum);
	if (status == ERROR_SUCCESS) {
		//wprintf(L"Successfully opened volume\n");
		// wprintf(L"Wipping GPT and MBR\n");
		log(kLogTypeInfo, "Successfully opened volume");
		log(kLogTypeInfo, "Wipping GPT and MBR");
		status = dw.WipeLayout();
	}
	dw.CloseDevice();
	return status;
}
int MainWindow::DetectDeviceClass()
{
	int status = -1;
	// This is PBL so depends on the chip type
	Sahara sh(&m_port);
	if (!sh.CheckDevice()) {
		status = 0;
		m_class = CLASS_SAHARA;
		m_protocol = FIREHOSE_PROTOCOL;
	}
	else {
		Dload dl(&m_port);
		status = dl.IsDeviceInDload();
		if (status != 0) return status;
		m_class = CLASS_DLOAD;
		m_protocol = STREAMING_PROTOCOL;
	}
	return status;
}


int MainWindow::CreateGPP(DWORD dwGPP1, DWORD dwGPP2, DWORD dwGPP3, DWORD dwGPP4)
{
	int status = ERROR_SUCCESS;

	if (m_protocol == STREAMING_PROTOCOL) {
		Dload dl(&m_port);

		// Wait for device to re-enumerate with flashprg
		status = dl.ConnectToFlashProg(4);
		if (status != ERROR_SUCCESS) return status;
		status = dl.OpenPartition(PRTN_EMMCUSER);
		if (status != ERROR_SUCCESS) return status;
		//wprintf(L"Connected to flash programmer, creating GPP\n");
		log(kLogTypeInfo, "Connected to flash programmer, creating GPP\n");
		status = dl.CreateGPP(dwGPP1, dwGPP2, dwGPP3, dwGPP4);

	}
	else if (m_protocol == FIREHOSE_PROTOCOL) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		// wprintf(L"Connected to flash programmer, creating GPP\n");
		log(kLogTypeInfo, "Connected to flash programmer, creating GPP\n");
		status = fh.CreateGPP(dwGPP1 / 2, dwGPP2 / 2, dwGPP3 / 2, dwGPP4 / 2);
		status = fh.SetActivePartition(1);
	}

	return status;
}

int MainWindow::ReadGPT(int dnum)
{
	int status;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, "Connected to flash programmer, starting download\n");
		// fh.ReadGPT(true);
		status = GuiReadGPT(true);
	}
	else {
		DiskWriter dw;
		dw.InitDiskList();
		status = dw.OpenDevice(dnum);

		if (status == ERROR_SUCCESS) {
			//status = dw.ReadGPT(true);
			status = GuiReadGPT(true);
		}

		dw.CloseDevice();
	}
	return status;
}

int MainWindow::WriteGPT(int dnum, TCHAR *szPartName, TCHAR *szBinFile)
{
	int status;

	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, "Connected to flash programmer, starting download\n");
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

int MainWindow::ResetDevice()
{
	/*Dload dl(&m_port);
	int status = ERROR_SUCCESS;
	if( status != ERROR_SUCCESS ) return status;
	status = dl.DeviceReset();
	return status;*/

	int status = 0;
	if (m_emergency) {
		Firehose fh(&m_port);// , m_cfg.MaxPayloadSizeToTargetInBytes);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != 0) return status;
		//printf("Connected to flash programmer, starting reset\n");
		log(kLogTypeInfo, "Connected to flash programmer, starting reset");
		status = fh.DeviceReset();
	}
	else {
		Dload dl(&m_port);
		Sahara sa(&m_port);
		if (m_class == CLASS_DLOAD) {
			status = dl.DeviceReset();
			log(kLogTypeInfo, "dl.DeviceReset()");
		}
		else {
			status = sa.DeviceReset();
			log(kLogTypeInfo, "sa.DeviceReset()");
		}
	}
	return status;

}

int MainWindow::FFUProgram(TCHAR *szFFUFile)
{
	FFUImage ffu;
	int status = ERROR_SUCCESS;
	Firehose fh(&m_port);
	fh.SetDiskSectorSize(m_sector_size);
	status = fh.ConnectToFlashProg(&m_cfg);
	if (status != ERROR_SUCCESS) return status;
	log(kLogTypeInfo, "Trying to open FFU\n");
	status = ffu.PreLoadImage(szFFUFile);
	if (status != ERROR_SUCCESS) return status;
	log(kLogTypeInfo, "Valid FFU found trying to program image\n");
	status = ffu.ProgramImage(&fh, 0);
	ffu.CloseFFUFile();
	return status;
}

int MainWindow::FFULoad(TCHAR *szFFUFile, TCHAR *szPartName, TCHAR *szOutputFile)
{
	int status = ERROR_SUCCESS;
	log(kLogTypeInfo, "Loading FFU\n");
	if ((szFFUFile != NULL) && (szOutputFile != NULL)) {
		FFUImage ffu;
		ffu.SetDiskSectorSize(m_sector_size);
		status = ffu.PreLoadImage(szFFUFile);
		if (status == ERROR_SUCCESS)
			status = ffu.SplitFFUBin(szPartName, szOutputFile);
		status = ffu.CloseFFUFile();
	}
	else {
		return PrintHelp();
	}
	return status;
}

int MainWindow::FFURawProgram(TCHAR *szFFUFile, TCHAR *szOutputFile)
{
	int status = ERROR_SUCCESS;
	log(kLogTypeInfo, "Creating rawprogram and files\n");
	if ((szFFUFile != NULL) && (szOutputFile != NULL)) {
		FFUImage ffu;
		ffu.SetDiskSectorSize(m_sector_size);
		status = ffu.FFUToRawProgram(szFFUFile, szOutputFile);
		ffu.CloseFFUFile();
	}
	else {
		return PrintHelp();
	}
	return status;
}


int MainWindow::EDownloadProgram(TCHAR *szSingleImage, TCHAR **szXMLFile)
{
	int status = ERROR_SUCCESS;
	Dload dl(&m_port);
	Firehose fh(&m_port);
	BYTE prtn = 0;
	QString msg;
	if (szSingleImage != NULL) {
		// Wait for device to re-enumerate with flashprg
		status = dl.ConnectToFlashProg(2);
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, "DLOAD Connected to flash programmer, starting download\n");
		dl.OpenPartition(PRTN_EMMCUSER);
		status = dl.LoadImage(szSingleImage);
		dl.ClosePartition();
	}
	else if (szXMLFile[0] != NULL) {
		// Wait for device to re-enumerate with flashprg
		if (m_protocol == STREAMING_PROTOCOL) {
			status = dl.ConnectToFlashProg(4);
			if (status != ERROR_SUCCESS) return status;
			log(kLogTypeInfo, "STREAMING_PROTOCOL Connected to flash programmer, starting download\n");

			// Download all XML files to device 
			for (int i = 0; szXMLFile[i] != NULL; i++) {
				// Use new method to download XML to serial port
				TCHAR szPatchFile[MAX_STRING_LEN];
				wcsncpy_s(szPatchFile, szXMLFile[i], sizeof(szPatchFile));
				StringReplace(szPatchFile, L"rawprogram", L"patch");
				TCHAR *sptr = wcsstr(szXMLFile[i], L".xml");
				if (sptr == NULL) return ERROR_INVALID_PARAMETER;
				prtn = (BYTE)((*--sptr) - '0' + PRTN_EMMCUSER);
				//wprintf(L"Opening partition %i\n",prtn);
				log(kLogTypeInfo, msg.sprintf("Opening partition %i\n", prtn));
				dl.OpenPartition(prtn);
				//Sleep(1);
				status = dl.WriteRawProgramFile(szPatchFile);
				if (status != ERROR_SUCCESS) return status;
				status = dl.WriteRawProgramFile(szXMLFile[i]);
			}
			//wprintf(L"Setting Active partition to %i\n",(prtn - PRTN_EMMCUSER)); 
			log(kLogTypeInfo, msg.sprintf("Setting Active partition to %i\n", (prtn - PRTN_EMMCUSER)));
			dl.SetActivePartition();
			dl.DeviceReset();
			dl.ClosePartition();
		}
		else if (m_protocol == FIREHOSE_PROTOCOL) {
			fh.SetDiskSectorSize(m_sector_size);
			if (m_verbose) fh.EnableVerbose();
			status = fh.ConnectToFlashProg(&m_cfg);
			if (status != ERROR_SUCCESS) return status;
			log(kLogTypeInfo, "FIREHOSE_PROTOCOL Connected to flash programmer, starting download\n");

			// Download all XML files to device
			for (int i = 0; szXMLFile[i] != NULL; i++) {
				Partition rawprg(0);
				status = rawprg.PreLoadImage(szXMLFile[i]);
				if (status != ERROR_SUCCESS) return status;
				status = rawprg.ProgramImage(&fh);

				if (status != ERROR_SUCCESS) break;
				// Only try to do patch if filename has rawprogram in it
				TCHAR *sptr = wcsstr(szXMLFile[i], L"rawprogram");
				if (sptr != NULL) {
					Partition patch(0);
					int pstatus = ERROR_SUCCESS;
					// Check if patch file exist
					TCHAR szPatchFile[MAX_STRING_LEN];
					wcsncpy_s(szPatchFile, szXMLFile[i], sizeof(szPatchFile));
					StringReplace(szPatchFile, L"rawprogram", L"patch");
					pstatus = patch.PreLoadImage(szPatchFile);
					if (pstatus == ERROR_SUCCESS) patch.ProgramImage(&fh);
				}
			}

			// If we want to set active partition then do that here
			if (m_cfg.ActivePartition >= 0 && status == ERROR_SUCCESS) {
				status = fh.SetActivePartition(m_cfg.ActivePartition);
			}
		}
	}

	return status;
}


int MainWindow::RawDiskProgram(TCHAR **pFile, TCHAR *oFile, uint64 dnum)
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
		log(kLogTypeInfo, "Successfully opened disk");
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

int MainWindow::RawDiskTest(int dnum, uint64 offset)
{
	DiskWriter dw;
	int status = ERROR_SUCCESS;
	offset = 0x2000000;

	// Initialize and print disk list
	dw.InitDiskList();
	status = dw.OpenDevice(dnum);
	if (status == ERROR_SUCCESS) {
		log(kLogTypeInfo, "Successfully opened volume\n");
		//status = dw.CorruptionTest(offset);
		status = dw.DiskTest(offset);
	}
	else {
		log(kLogTypeInfo, "Failed to open volume\n");
	}

	dw.CloseDevice();
	return status;
}

int MainWindow::RawDiskDump(uint64 start, uint64 num, TCHAR *oFile, int dnum, TCHAR *szPartName)
{
	DiskWriter dw;
	int status = ERROR_SUCCESS;
	QString msg;
	// Get extra info from the user via command line
	//wprintf(L"Dumping at start sector: %I64d for sectors: %I64d to file: %s\n",start, num, oFile);
	log(kLogTypeInfo, msg.sprintf("Dumping at start sector: %I64d for sectors: %I64d to file: %s\n", start, num, oFile));
	if (m_emergency) {
		Firehose fh(&m_port);
		fh.SetDiskSectorSize(m_sector_size);
		if (m_verbose) fh.EnableVerbose();
		if (status != ERROR_SUCCESS) return status;
		status = fh.ConnectToFlashProg(&m_cfg);
		if (status != ERROR_SUCCESS) return status;
		log(kLogTypeInfo, "Connected to flash programmer, starting dump");
		status = fh.DumpDiskContents(start, num, oFile, 0, szPartName);
	}
	else {
		// Initialize and print disk list
		dw.InitDiskList();
		status = dw.OpenDevice(dnum);
		if (status == ERROR_SUCCESS) {
			log(kLogTypeInfo, "Successfully opened volume\n");
			status = dw.DumpDiskContents(start, num, oFile, 0, szPartName);
		}
		dw.CloseDevice();
	}
	return status;
}

int MainWindow::DiskList()
{
	//InitDiskList();
	return ERROR_SUCCESS;
}


void MainWindow::appendLog(const QString &str, QColor color)
{
	//ui->textEdit->setUpdatesEnabled(FALSE);
	//ui->textEdit->setTextColor(color);
	//ui->textEdit->append(str);
	//ui->textEdit->setUpdatesEnabled(TRUE);
}
void MainWindow::log(int type, const char* message) {
	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	//ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message));
}

void MainWindow::log(int type, std::string message)
{
	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	//ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.c_str()));
}

void MainWindow::log(int type, QString message)
{

	QString tmp = "gray";

	switch (type) {
	case kLogTypeDebug:		tmp = "gray";	break;
	case kLogTypeError:		tmp = "red";	break;
	case kLogTypeWarning:	tmp = "orange";	break;
	case kLogTypeInfo:		tmp = "green";	break;
	}

	//ui->plainTextEdit->appendHtml(tmp.sprintf("<font color=%s><pre>%s</pre></font>", tmp.toStdString().c_str(), message.toStdString().c_str()));
}

int MainWindow::InitDiskListQc()
{
	///////////////////////////////////////////////////////////////////////
	//HANDLE vHandle;
	//TCHAR VolumeName[MAX_PATH + 1];
	//BOOL bValid = true;
	//int i = 0;
#ifndef ARM
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	DEVPROPTYPE ulPropertyType = DEVPROP_TYPE_STRING;
	DWORD dwSize;
#endif //ARM

	/*if (disks == NULL || volumes == NULL) {
	return ERROR_INVALID_PARAMETER;
	}*/

	// wprintf(L"\tFinding all devices in emergency download mode...\n");
	//ui->plainTextEdit->clear();
	log(kLogTypeInfo, QString::fromUtf8("  Đang tìm kiếm thiết bị QualCom  ...\n"));

	// wprintf(L"\tTim kiem tat ca cac thiet bi o che do 9008 ...\n\n");
#ifndef ARM
	if (hDevInfo != INVALID_HANDLE_VALUE) {
		// Successfully got a list of ports
		for (int i = 0; ; i++) {
			WCHAR szBuffer[512];
			SP_DEVINFO_DATA DeviceInfoData;
			DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

			/*wchar_t *Htcom;
			if (ui->checkBox_firehose->isChecked())
			{
				Htcom = L"QDLoader 9008";
			}
			else
			{
				Htcom = L"";
			}*/
			wchar_t *Htcom;
			Htcom = L"QDLoader 9008";
			if (!SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData) && (GetLastError() == ERROR_NO_MORE_ITEMS)) {
				// No more ports

				break;
			}
			// successfully found entry print out the info
			if (SetupDiGetDeviceProperty(hDevInfo, &DeviceInfoData, &DEVPKEY_Device_FriendlyName, &ulPropertyType, (BYTE*)szBuffer, sizeof(szBuffer), &dwSize, 0)) {

				if ((GetLastError() == ERROR_SUCCESS) && wcsstr(szBuffer, Htcom) != NULL) {
					// wprintf(_T("\t>>"));
					// log(kLogTypeInfo, "Tim kiem tat ca cac thiet bi o che do 9008 ...\n");



					//log(kLogTypeInfo, QString::toLocal8Bit(szBuffer));
					//wide char array
					log(kLogTypeInfo,QString::fromUtf8("  Đã tìm thấy thiết bị ...\n"));

					//convert from wide char to narrow char array
					char ch[512];
					char DefChar = ' ';
					WideCharToMultiByte(CP_ACP, 0, szBuffer, -1, ch, 512, &DefChar, NULL);

					//A std:string  using the char* constructor.
					std::string ss(ch);
					QString qstr = QString::fromStdString(ss);

					log(kLogTypeError, "  " + qstr);


				//	ui->comboBox->addItem(qstr);

					// wprintf(szBuffer);
					// Get the serial number and display it if verbose is enabled
					/*if (verbose)
					{*/
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

							log(kLogTypeError,QString::fromUtf8("  Đã kết nối với cổng :   ") + qstr);

							QString msg;
							log(kLogTypeInfo, msg.sprintf("  SERIAL=0x%x  :  HW_ID=0x%x   ", pbl_info.serial, pbl_info.msm_id));
							if (pbl_info.msm_id == 0x560e1)
							{
								log(kLogTypeError, QString::fromUtf8("  Tên Chíp : MSM8937 "));
								// ui->lineEdit_FireHose->setText("firehose_MSM8937.mbn");
								//ui->comboBox_QcBootSelect->addItem("D:\\26-MOBILE\\CPP\\emmcdl\\Release\\prog_emmc_firehose_8937.mbn");
							}
							else
							{
								log(kLogTypeError, QString::fromUtf8("  Tên Chíp : chua xac nhan "));
								//ui->lineEdit_FireHose->setText("firehose_chuaxacnhan.mbn");
								//ui->comboBox_QcBootSelect->addItem("firehose_chuaxacnhan.mbn");
							}
						}
					}


					// }*/
					// wprintf(_T("\n\n"));
					log(kLogTypeInfo, "\n\n");
				}

			}
		}
		//SetupDiDestroyDeviceInfoList(hDevInfo);
		//ui->comboBox->addItem("- Select a Port -");
		//ui->comboBox_QcBootSelect->addItem("D:\\26-MOBILE\\CPP\\emmcdl\\Release\\prog_emmc_firehose_8937_ddr_vo_y66.mbn");
		//ui->comboBox_QcBootSelect->addItem("D:\\26-MOBILE\\CPP\\emmcdl\\Release\\prog_emmc_firehose_8937_ddr_vo_y66.mbn");
		//ui->comboBox_QcBootSelect->addItem("D:\\26-MOBILE\\CPP\\emmcdl\\Release\\prog_emmc_firehose_8937_ddr_vo_y66.mbn");
		//ui->comboBox_QcBootSelect->addItem("- Select Boot -");
	}
#endif //ARM
	return ERROR_SUCCESS;
}
void MainWindow::on_pushButton_2_clicked()
{
	ComReload();

}

void MainWindow::ComReload()
{
	//ui->comboBox->clear();
	InitDiskListQc();


}
void MainWindow::on_pushButton_clicked()
{
	QString qcboot = QFileDialog::getExistingDirectory(this, "chon thu muc", "");
}
int MainWindow::Tesmain()
{
	InitDiskListQc();

	//int dnum = 29;
	//QString intdnum = ui->comboBox->currentText();
	//appendLog("======= Dang ket noi ===== ", Qt::cyan);
	// QString str = ("\nKet noi voi cong COM : " + intdnum.right(2));
	// log(kLogTypeWarning, str);
//	int dnum = (intdnum.right(2).toInt());
	int dnum = 29;
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
	emmc_cmd_e cmd = EMMC_CMD_INFO;
	uint64 uiStartSector = 0;
	uint64 uiNumSectors = 0;
	uint64 uiOffset = 0x40000000;
	DWORD dwGPP1 = 0, dwGPP2 = 0, dwGPP3 = 0, dwGPP4 = 0;
	bool bGppQuiet = FALSE;



	// status = InitDiskList(true);

	// QString strFlashProg = ui.lineEdit_FireHose->text();

	QString szqFileName;// = ui->lineEdit_FireHose->text();
	qint64 nLen = szqFileName.length();
	//
	// QString to TCHAR*
	//
	TCHAR *szFileName = NULL;
#ifdef UNICODE
	szFileName = (wchar_t*)szqFileName.utf16();
#else
	QByteArray byteArray = szqFileName.toLocal8Bit();
	szFileName = byteArray.constData();
#endif // UNICODE
	szFlashProg = szFileName;
	//szFileName = TEXT(FILE_NAME);
#ifdef UNICODE
	szqFileName = QString::fromUtf16((ushort*)szFileName);
#else
	szqFileName = QString::fromLocal8Bit(szFileName);
#endif

	QString msg;
	if (szFlashProg != NULL ){
		m_port.Open(dnum);
		status = LoadFlashProg(szFlashProg);
		if (status == ERROR_SUCCESS) {
			log(kLogTypeInfo, msg.sprintf("Waiting for flash programmer to boot\n"));
			Sleep(2000);
		}
		else {
			log(kLogTypeInfo, msg.sprintf("! WARNING: Flash programmer failed to load trying to continue !"));
		}
		m_emergency = true;
	}




	log(kLogTypeInfo, msg.sprintf("Device Class : %s / Protocol : %s  / Emergency : %s", m_class == CLASS_SAHARA ? "sahara" : "dload",
		m_protocol == FIREHOSE_PROTOCOL ? "firehose" : "streaming",
		m_emergency ? "true" : "false"));



	switch (cmd) {
	case EMMC_CMD_DUMP:
		if (szOutputFile && (dnum >= 0)) {
			wprintf(_T("Dumping data to file %s\n"), szOutputFile);
			status = RawDiskDump(uiStartSector, uiNumSectors, szOutputFile, dnum, szPartName);
		}
		else {
			PrintHelp();
		}
		break;
	case EMMC_CMD_ERASE:
		wprintf(_T("Erasing Disk\n"));
		status = EraseDisk(uiStartSector, uiNumSectors, dnum, szPartName);
		break;
	case EMMC_CMD_SPLIT_FFU:
		status = FFURawProgram(szFFUImage, szOutputFile);
		break;
	case EMMC_CMD_FFU:
		status = FFULoad(szFFUImage, szPartName, szOutputFile);
		break;
	case EMMC_CMD_LOAD_FFU:
		status = FFUProgram(szFFUImage);
		break;
	case EMMC_CMD_WRITE:
		if ((szXMLFile[0] != NULL) && (szSingleImage != NULL)) {
			PrintHelp();
		}
		if (m_emergency) {
			status = EDownloadProgram(szSingleImage, szXMLFile);
		}
		else {
			wprintf(_T("Programming image\n"));
			status = RawDiskProgram(szXMLFile, szOutputFile, dnum);
		}
		break;
	case EMMC_CMD_WIPE:
		wprintf(_T("Wipping Disk\n"));
		if (dnum > 0) {
			status = WipeDisk(dnum);
		}
		break;
		// case EMMC_CMD_RAW:
		//  wprintf(_T("Sending RAW data to COM%i\n"), dnum);
		//  status = RawSerialSend(dnum, szSerialData, argc - 4);
		//  break;
	case EMMC_CMD_TEST:
		wprintf(_T("Running performance tests disk %i\n"), dnum);
		status = RawDiskTest(dnum, uiOffset);
		break;
	case EMMC_CMD_GPP:
		wprintf(_T("Create GPP1=%iMB, GPP2=%iMB, GPP3=%iMB, GPP4=%iMB\n"), (int)dwGPP1, (int)dwGPP2, (int)dwGPP3, (int)dwGPP4);
		if (!bGppQuiet) {
			wprintf(_T("Are you sure? (y/n)"));
			if (getchar() != 'y') {
				wprintf(_T("\nGood choice back to safety\n"));
				break;
			}
		}
		wprintf(_T("Sending command to create GPP\n"));
		status = CreateGPP(dwGPP1 * 1024 * 2, dwGPP2 * 1024 * 2, dwGPP3 * 1024 * 2, dwGPP4 * 1024 * 2);
		if (status == ERROR_SUCCESS) {
			wprintf(_T("Power cycle device to complete operation\n"));
		}
		break;
	case EMMC_CMD_WRITE_GPT:
		if ((szSingleImage != NULL) && (szPartName != NULL) && (dnum >= 0)) {
			status = WriteGPT(dnum, szPartName, szSingleImage);
		}
		break;
	case EMMC_CMD_RESET:
		wprintf(_T("Sending command to reset device\n"));
		status = ResetDevice();
		break;
	case EMMC_CMD_LOAD_MRPG:
		break;
	case EMMC_CMD_GPT:
		// Read and dump GPT information from given disk
		status = ReadGPT(dnum);
		break;
	case EMMC_CMD_INFO:
		m_port.Open(dnum);
		status = DumpDeviceInfo();

		break;
	case EMMC_CMD_NONE:
		break;
	}



	//str = ("Firehose : " + szqFileName.right(19));
	// log(kLogTypeWarning, str);




	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,status,MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0, NULL);

	// Display the error message and exit the process
	log(kLogTypeInfo, msg.sprintf("Status  :  0%i   %s\n", status, (TCHAR*)lpMsgBuf));
	return status;
}




int MainWindow::GuiReadGPT(bool debug)
{
	int status = ERROR_SUCCESS;
	DWORD bytesRead;
	gpt_header_t gpt_hdr;
	gpt_entries = (gpt_entry_t*)malloc(sizeof(gpt_entry_t) * 128);

	if (gpt_entries == NULL) {
		return ERROR_OUTOFMEMORY;
	}

	status = ERROR_SUCCESS; //ReadData((BYTE *)&gpt_hdr, DISK_SECTOR_SIZE, DISK_SECTOR_SIZE, &bytesRead, 0);

	if ((status == ERROR_SUCCESS) && (memcmp("EFI PART", gpt_hdr.signature, 8) == 0)) {
		if (debug) log(kLogTypeInfo, "\nSuccessfully found GPT partition\n");// wprintf(L"\nSuccessfully found GPT partition\n");
		status = ERROR_SUCCESS;// ReadData((BYTE *)gpt_entries, 2 * DISK_SECTOR_SIZE, 32 * DISK_SECTOR_SIZE, &bytesRead, 0);
		if ((status == ERROR_SUCCESS) && debug) {
			for (int i = 0; (i < gpt_hdr.num_entries) && (i < 128); i++) {
				if (gpt_entries[i].first_lba > 0) {

					//log(kLogTypeInfo, "%i. Partition Name: %s Start LBA: %I64d Size in LBA: %I64d");
					QString msg;
					log(kLogTypeInfo, msg.sprintf("%i. Partition Name: %s Start LBA: %I64d Size in LBA: %I64d", i + 1, gpt_entries[i].part_name, gpt_entries[i].first_lba, gpt_entries[i].last_lba - gpt_entries[i].first_lba + 1));
					//Log(L"%i. Partition Name: %s Start LBA: %I64d Size in LBA: %I64d", i + 1, gpt_entries[i].part_name, gpt_entries[i].first_lba, gpt_entries[i].last_lba - gpt_entries[i].first_lba + 1);


				}


			}
		}
	}
	else {
		if (debug)log(kLogTypeInfo, "\n  No valid GPT found");// Log(L"\nNo valid GPT found");
		free(gpt_entries);
		gpt_entries = NULL;
		status = ERROR_INVALID_DATA;
	}
	return status;
}


