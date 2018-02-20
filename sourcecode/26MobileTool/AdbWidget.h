#ifndef ADBWIDGET_H
#define ADBWIDGET_H

#include <QWidget>
#include <QProcess>
#include "TabWidgetBase.h"
#include <QTcore>
#include <QListWidgetItem>



namespace Ui {
class AdbWidget;
}
class MainWindow;
class AdbWidget : public TabWidgetBase
{
    Q_OBJECT

public:

	explicit AdbWidget(QTabWidget  *parent, MainWindow *window);

   ~AdbWidget();

DECLARE_TABWIDGET_VFUNCS()

QString sdk;

private:
    QProcess *t_process;

    Ui::AdbWidget *ui;

    MainWindow* main_window;
    QString adb_program;
    QString emmcdl_program;
    QString folder_program;
    /*void UpdateUI();
    void UpdateUI(const QString& text, QColor color = Qt::black);*/
    QProcess *myProcess;
     //QLabel * storagePathLabel;
       QString program;
       QString fileNameTemp;
       QString storagePath;
      int pattern; //模式 0：单个  1：一键
	  void getStoragePath();

	  

private slots:

      void flashSPL();
      void flashRecovery();
      void flashRadio();
      void bootIMG();

     void AdbDevices();
     void GpttoRawprogram();
     void on_pushButton_clicked();
     void on_toolButton_2_clicked();
	 void on_toolButton_Reboot_clicked();
	 void on_toolButton_TurnOff_clicked();

     void on_pushButton_2_clicked();
    void slot_DeviceTestCallback(const QString &msg, QColor color);
public slots:
    void AdbsetStdout();
    void Adbcommand();
  

    void LinkDevices();
    void GetWifiMac();
    void GetEthernetMac();
    void GetModuleName();
    void GetSerialNumber();
    void GetAndroidVersion();
    void GetScreenResolution();
    void GetICType();
    void GetAllInfo();
    void GetAllApkPackageName();
    void SaveLog();
    void PullFile();
    void PushFile();
    void InstallAPK();
    void UninstallAPK();
    void ListWeightCopy(QListWidgetItem*);
    void CaptureScreen();
    void Vedio();
    void Restart();
    void NetworkConnect();
    void Recovery();
    void Fastboot();
    void About();
	void GetModel();
	void GetEmmcSize();
	void GetImel1();
	void GetImel2();
	void GetRegion();
	void GetProducCode();
	void GetSwVer();

    
    void FinishSolute(int);
};

#endif // ADBWIDGET_H
