#ifndef XFSTKDLDRPLUGINUSERINTERFACE_H
#define XFSTKDLDRPLUGINUSERINTERFACE_H
#include <QTabWidget>
#include <QWidget>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QDesktopServices>
#include <QTimer>
#include "xfstkdldrthread.h"
#include <xfstkdldrapi.h>
//#include "xfstkdldrpluginoptionsinterface.h"
#include "TabWidgetBase.h"
#include "IntelSettingDialog.h"

namespace Ui {
    class XfstkDldrPluginUserInterface;
}
class MainWindow;

struct OptionsInterfaceState;

struct UserInterfaceState {
    QString FWDnXBin;
    QString IFWIBin;
    QString OSDnXBin;
    QString OSImageBin;
    QString SoftfusesPath;
    QString DownloadButtonLabel;
    QString DownloadStatusDetails;
    QString DownloadStatusProgress;
    QString DeviceStatusScanning;
    QString ProvisionCount;
    QString CurrentSearchDir;
    QString GPFlagOverrideValue;
    QString DesktopDir;
    QString USBTimeout;
    bool EnableGpFlagOverride;
    bool SuppressErrors;
    bool IsDownloadThreadDone;
    int NumberOfAvailableTargets;
    int TotalPassingProvisionsForCurrentThread;
    int TotalFailingProvisionsForCurrentThread;
    int TotalTargetsForCurrentThread;
    bool EnableLogging;
    QString LoggingPath;
    bool EnableProvisionCount;
    int NumProvisionCount;
    int StatusListLocation;
    int StatusListPrevLength;
    bool ShowDownloadDetails;
    bool SoftfuseInclude;
};

class XfstkDldrPluginUserInterface : public TabWidgetBase
{
   
	Q_OBJECT

public:
	explicit XfstkDldrPluginUserInterface(QTabWidget *parent, MainWindow* window);
	~XfstkDldrPluginUserInterface();

	DECLARE_TABWIDGET_VFUNCS()


    void SaveUserInterfaceStateToDisk(QString Vendor, QString ProductPlugin);
    void LoadUserInterfaceStateFromDisk(QString Vendor, QString ProductPlugin);
    void RestoreUserInterfaceFromCurrentState();
    bool SetCurrentWorkingDirectory(QString WorkingDir);
    QString DetermineCurrentFileSearchPath(QString BinPath);
    UserInterfaceState CurrentState;
    QString LastError;
    bool LineEditWA;
    void ReportErrors();
    bool ValidateUserInterfaceState();
    bool VerifyBinaryFilePath(QString BinPath);
    QFileDialog OpenFile;
    QTabWidget *GetTabInterface();
    Ui::XfstkDldrPluginUserInterface *ui;
    bool IgnoreIncrementalUIChanges;
    QTimer *UsbDetectionTimer;
    QTimer *UpdateStatusTimer;
    xfstkdldrthread xfstknewthread;
    xfstkdldrthreadobj xfstknewthreadobj;

    char *c_str_FWDnX;
    char *c_str_FWImage;
    char *c_str_OSDnx;
    char *c_str_OSImage;
    char *c_str_SoftfusePath;
    char *c_str_GPFlagsOverride;

    QByteArray baFWDnx;
    QByteArray baFWImage;
    QByteArray baOSDnx;
    QByteArray baOSImage;
    QByteArray baSoftfusePath;
    QByteArray baGPFlagsOverride;

    QString FWDnX;
    QString FWImage;
    QString OSDnX;
    QString OSImage;
    QString SoftfusesPath;
    QString GPFlagsOverride;

    bool bFWOnly;
    bool bOsOnly;
    bool bFwOs;

    unsigned int DetectDevicesTimeRemain;
#ifdef XFSTK_OS_WIN
    DevicesCallBack CallbackStruct;
#endif
    SoCDevices socDevs;
    xfstkdldrapi* dldrapi;
    QTimer *UsbCallBackTimer;
    bool devDetectWait;
    void BeginDownload();
    void emitDownloadbegin(){emit readyForDownload();}
    void cancelDetection();

signals:
    void UserInterfaceChanged(UserInterfaceState *State);
    void readyForDownload();

public slots:
    void OptionsInterfaceChanged(OptionsInterfaceState *State);
    void UpdateUsbStatus();
    void UpdateUiStatus();
    void ThreadComplete(bool result);
    void TargetsCompletedForThread(int numdone);
    void UpdatedeviceDetectStatus();
protected:
    void changeEvent(QEvent *e);

private:

	//Ui::XfstkDldrPluginUserInterface *ui;
	MainWindow* main_window_;

	IntelSettingDialog SettingDialog;


private slots:
    void on_BeginDownload_clicked();
    void on_OSImageBin_editingFinished();
    void on_OSDnXBin_editingFinished();
    void on_IFWIBin_editingFinished();
    void on_FWDnXBin_editingFinished();
    void on_BrowseOSImageBin_clicked();
    void on_BrowseOSDnXBin_clicked();
    void on_BrowseIFWIBin_clicked();
    void on_BrowseFWDnXBin_clicked();
    void on_pushButton_Setting_clicked();
};
class xfstksleep : public QThread
{
	Q_OBJECT
public:
	explicit xfstksleep(QObject *parent = 0);
	void sleep(unsigned long secs);
	void msleep(unsigned long msecs);
	void usleep(unsigned long usecs);
signals:

	public slots :

};

#endif // XFSTKDLDRPLUGINUSERINTERFACE_H
