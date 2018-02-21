#include "MainWindow.h"
#include "cmdwidget.h"
#include "adbwidget.h"
#include "emmcrawwidget.h"
#include "QualComMobileWidget.h"
#include "AsusWidget.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow) 
{
	ui->setupUi(this);
    CreateWidget();

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
    emmcraw_widget = new EmmcRawWidget(ui->tabWidget, this);
	qualcommobile_widget = new QualComMobileWidget(ui->tabWidget, this);

	tab_widgets.push_back(adb_widget);
	tab_widgets.push_back(cmd_widget);
	tab_widgets.push_back(emmcraw_widget);
	tab_widgets.push_back(qualcommobile_widget);
	tab_widgets.push_back(asus_widget);

	for (std::list<TabWidgetBase*>::const_iterator it = tab_widgets.begin();
		it != tab_widgets.end(); ++it)
	{
		(*it)->Attach();
	}

	ui->tabWidget->setCurrentWidget(cmd_widget);
}


int MainWindow::Tesmain()
{
//	//InitDiskListQc();
//
//	//int dnum = 29;
//	//QString intdnum = ui->comboBox->currentText();
//	//appendLog("======= Dang ket noi ===== ", Qt::cyan);
//	// QString str = ("\nKet noi voi cong COM : " + intdnum.right(2));
//	// log(kLogTypeWarning, str);
////	int dnum = (intdnum.right(2).toInt());
//	int dnum = 29;
//	int status = 0;
//	bool bEmergdl = FALSE;
//	TCHAR *szOutputFile = NULL;
//	TCHAR *szXMLFile[8] = { NULL };
//	TCHAR **szSerialData = { NULL };
//	DWORD dwXMLCount = 0;
//	TCHAR *szFFUImage = NULL;
//
//	TCHAR *szFlashProg = NULL;
//	TCHAR *szSingleImage = NULL;
//	TCHAR *szPartName = NULL;
//	emmc_cmd_e cmd = EMMC_CMD_INFO;
//	uint64 uiStartSector = 0;
//	uint64 uiNumSectors = 0;
//	uint64 uiOffset = 0x40000000;
//	DWORD dwGPP1 = 0, dwGPP2 = 0, dwGPP3 = 0, dwGPP4 = 0;
//	bool bGppQuiet = FALSE;
//
//
//
//	// status = InitDiskList(true);
//
//	// QString strFlashProg = ui.lineEdit_FireHose->text();
//
//	QString szqFileName;// = ui->lineEdit_FireHose->text();
//	qint64 nLen = szqFileName.length();
//	//
//	// QString to TCHAR*
//	//
//	TCHAR *szFileName = NULL;
//#ifdef UNICODE
//	szFileName = (wchar_t*)szqFileName.utf16();
//#else
//	QByteArray byteArray = szqFileName.toLocal8Bit();
//	szFileName = byteArray.constData();
//#endif // UNICODE
//	szFlashProg = szFileName;
//	//szFileName = TEXT(FILE_NAME);
//#ifdef UNICODE
//	szqFileName = QString::fromUtf16((ushort*)szFileName);
//#else
//	szqFileName = QString::fromLocal8Bit(szFileName);
//#endif
//
//
//
//	//str = ("Firehose : " + szqFileName.right(19));
//	// log(kLogTypeWarning, str);
//
//
//
//
//	LPVOID lpMsgBuf;
//
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,status,MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0, NULL);
//
//	// Display the error message and exit the process
////	log(kLogTypeInfo, msg.sprintf("Status  :  0%i   %s\n", status, (TCHAR*)lpMsgBuf));
	return 0;
}


