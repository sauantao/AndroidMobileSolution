#ifndef QUALCOMMOBILEWIDGET_H
#define QUALCOMMOBILEWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QtCore>
#include <QSerialPortInfo>
#include "TabWidgetBase.h"
#include "emmcdl.h"
#include "tchar.h"
#include <Windows.h>
#include <stdint.h>
#include <winerror.h>
#include <xmlparser.h>




namespace Ui {
class QualComMobileWidget;
}
class MainWindow;
class QualComMobileWidget : public TabWidgetBase
{
    Q_OBJECT
    enum LogType {
        kLogTypeError = 1,
        kLogTypeWarning = 2,
        kLogTypeInfo = 3,
        kLogTypeDebug = 4
    };

public:

    explicit QualComMobileWidget(QTabWidget *parent, MainWindow* window);
    ~QualComMobileWidget();

     DECLARE_TABWIDGET_VFUNCS()

	 void StringToByte(TCHAR **szSerialData, BYTE *data, int len);
	 int RawSerialSend(int dnum, TCHAR **szSerialData, int len);
	 int EraseDisk(uint64 start, uint64 num, int dnum, TCHAR *szPartName);
	 int DumpDeviceInfo(void);
	 int LoadFlashProg(TCHAR *mprgFile);
	 int WipeDisk(int dnum);
	 int ReadGPT(int dnum);
	 int WriteGPT(int dnum, TCHAR *szPartName, TCHAR *szBinFile);
	 int ResetDevice();
	 int RawDiskProgram(TCHAR **pFile, TCHAR *oFile, uint64 dnum);
	 int RawDiskDump(uint64 start, uint64 num, TCHAR *oFile, int dnum, TCHAR *szPartName);
    

public slots:

     int updatePortList();
	 int QcupdatePortList();
	 void AutoBootUpdateUI();
	 void ReadInfoUpdateUI();
	 void FlashUpdateUI();


private:

    Ui::QualComMobileWidget* ui;
    MainWindow* main_window;
	   
	void log(int type, const char* message);
    void log(int type, std::string message);
    void log(int type, QString message);



private slots:

	void on_pushButton_Com_Connec_clicked();
	void on_pushButton_Com_Reload_clicked();
	void on_pushButton_BootSelect_clicked();
	void on_pushButton_RomBootFolder_clicked();
	void on_pushButton_RawXmlPatchXml_clicked();
	void on_toolButton_Start_clicked();
};

#endif // QUALCOMMOBILEWIDGET_H
