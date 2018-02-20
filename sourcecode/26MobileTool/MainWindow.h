#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "targetver.h"
#include "emmcdl.h"
#include "partition.h"
#include "diskwriter.h"
#include "dload.h"
#include "sahara.h"
#include "serialport.h"
#include "firehose.h"
#include "ffu.h"
#include "tchar.h"
#include <QColor>
#include "mythread.h"

#define CLASS_DLOAD  0
#define CLASS_SAHARA 1

namespace Ui {
	class MainWindow;
}
class MainWindowCallback;
class TabWidgetBase;
class CmdWidget;
class QTabWidget;
class AdbWidget;
class EmmcRawWidget;
class QualComMobileWidget;
class AsusWidget;

class MainWindow : public QMainWindow





{
	Q_OBJECT
		enum LogType {
		kLogTypeError = 1,
		kLogTypeWarning = 2,
		kLogTypeInfo = 3,
		kLogTypeDebug = 4
	};

	enum QualcomBootloadFile {
		bootMsm8916 = 1,
		bootMsm8974 = 2,
		bootMsm8936 = 3,
		bootMsm8937 = 4
	};

	enum ImageColumn {
		ColumnEnable = 0,
		ColumnName,
		ColumnBeginAddr,
		ColumnEndAddr,
		columnRegion,
		ColumnLocation
	};

public:

	//MainWindow(QWidget *parent = Q_NULLPTR);
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	int PrintHelp();
	void StringToByte(TCHAR **szSerialData, BYTE *data, int len);
	int RawSerialSend(int dnum, TCHAR **szSerialData, int len);
	int LoadFlashProg(TCHAR *mprgFile);
	int EraseDisk(uint64 start, uint64 num, int dnum, TCHAR *szPartName);
	int DumpDeviceInfo(void);
	int WipeDisk(int dnum);
	int CreateGPP(DWORD dwGPP1, DWORD dwGPP2, DWORD dwGPP3, DWORD dwGPP4);
	int ReadGPT(int dnum);
	int WriteGPT(int dnum, TCHAR *szPartName, TCHAR *szBinFile);
	int ResetDevice();
	int FFUProgram(TCHAR *szFFUFile);
	int FFULoad(TCHAR *szFFUFile, TCHAR *szPartName, TCHAR *szOutputFile);
	int EDownloadProgram(TCHAR *szSingleImage, TCHAR **szXMLFile);
	int RawDiskProgram(TCHAR **pFile, TCHAR *oFile, uint64 dnum);
	int RawDiskTest(int dnum, uint64 offset);
	int RawDiskDump(uint64 start, uint64 num, TCHAR *oFile, int dnum, TCHAR *szPartName);
	int DiskList();
	int FFURawProgram(TCHAR *szFFUFile, TCHAR *szOutputFile);
	void appendLog(const QString &str, QColor color);
	int DetectDeviceClass();
    void log(int type, const char* message);
    void log(int type, std::string message);
	void log(int type, QString message);

	int InitDiskListQc();

	int GuiReadGPT(bool debug);
	
	int Tesmain();
	void CreateWidget();

	MyThread *mThread;
	Ui::MainWindow *ui;

public slots:
   


	void onValueChanged(int);

private:

	//CheckHeader * header_;
	QualComMobileWidget * qualcommobile_widget;
	CmdWidget * cmd_widget;
	AdbWidget * adb_widget;
	EmmcRawWidget * emmcraw_widget;
	AsusWidget * asus_widget;
	std::list<TabWidgetBase*> tab_widgets;
	QLabel * storagePathLabel;
protected:
	gpt_entry_t *gpt_entries;
	int DISK_SECTOR_SIZE;

	
private slots:
void on_tableWidget_cellClicked(int row, int column);
void on_pushButton_2_clicked();
void on_pushButton_clicked();
void on_pushButton_Start_clicked();
void on_pushButton_Stop_clicked();
void on_pushButton_QcBootSlect_clicked();
void on_pushButton_RawProgramSlect_clicked();
void on_pushButton_PatchSelect_clicked();

void ComReload();
signals:



};
