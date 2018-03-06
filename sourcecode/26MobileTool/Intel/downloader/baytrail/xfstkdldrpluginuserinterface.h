/*
    Copyright (C) 2015  Intel Corporation

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
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
#include "xfstkdldrpluginoptionsinterface.h"
namespace Ui {
    class XfstkDldrPluginUserInterface;
}


struct OptionsInterfaceState;

struct UserInterfaceState {
    QString IFWIBin;
    QString DownloadButtonLabel;
    QString DownloadStatusDetails;
    QString DownloadStatusProgress;
    QString DeviceStatusScanning;
    QString ProvisionCount;
    QString CurrentSearchDir;
    QString DesktopDir;
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
    int StartDownload;
    bool ShowDownloadDetails;
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

public slots:

};

class XfstkDldrPluginUserInterface : public QWidget {
    Q_OBJECT
public:
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
    XfstkDldrPluginUserInterface(QWidget *parent = 0);
    ~XfstkDldrPluginUserInterface();
    QTabWidget *GetTabInterface();
    Ui::XfstkDldrPluginUserInterface *ui;
    bool IgnoreIncrementalUIChanges;
    QTimer *UsbDetectionTimer;
    QTimer *UpdateStatusTimer;
    xfstkdldrthread xfstknewthread;
    xfstkdldrthreadobj xfstknewthreadobj;

    char *c_str_FWImage;
    QByteArray baFWImage;
    QString FWImage;
    bool bFWOnly;

signals:
    void UserInterfaceChanged(UserInterfaceState *State);

public slots:
    void OptionsInterfaceChanged(OptionsInterfaceState *State);
    void UpdateUsbStatus();
    void UpdateUiStatus();
    void ThreadComplete(bool result);
    void TargetsCompletedForThread(int numdone);
    void DownloaderDone();

protected:
    void changeEvent(QEvent *e);

private:


private slots:
    void on_BeginDownload_clicked();
    void on_IFWIBin_editingFinished();
    void on_BrowseIFWIBin_clicked();
};

#endif // XFSTKDLDRPLUGINUSERINTERFACE_H
