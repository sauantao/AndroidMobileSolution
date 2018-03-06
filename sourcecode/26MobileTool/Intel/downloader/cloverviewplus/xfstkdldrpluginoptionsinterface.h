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
#ifndef XFSTKDLDRPLUGINOPTIONSINTERFACE_H
#define XFSTKDLDRPLUGINOPTIONSINTERFACE_H
#include <QTabWidget>
#include <QWidget>
#include <QFileDialog>
#include "xfstkdldrpluginuserinterface.h"
namespace Ui {
    class XfstkDldrPluginOptionsInterface;
}
struct UserInterfaceState;

struct OptionsInterfaceState {
    QString FWDnXPath;
    QString IFWIPath;
    QString OSDnXPath;
    QString OSIPath;
    QString SoftfusesPath;
    QString GPFlagOverrideValue;
    QString LoggingPath;
    QString ProvisionCount;
    QString DesktopDir;
    QString CurrentSearchDir;
    QString USBTimeout;
    bool EnableGpFlagOverride;
    bool EnableLogging;
    bool EnableProvisionCount;
    bool SoftfuseInclude;
    bool SuppressErrors;
};

class XfstkDldrPluginOptionsInterface : public QWidget {
    Q_OBJECT
public:
    OptionsInterfaceState CurrentState;
    OptionsInterfaceState PrevState;
    XfstkDldrPluginOptionsInterface(QWidget *parent = 0);
    ~XfstkDldrPluginOptionsInterface();
    QTabWidget *GetTabInterface();
    QString DetermineCurrentFileSearchPath(QString BinPath);
    bool VerifyBinaryFilePath(QString BinPath);
    QString LastError;
    bool LineEditWA;
    void ReportErrors();
    Ui::XfstkDldrPluginOptionsInterface *ui;
    QFileDialog OpenFile;
signals:
    void OptionsInterfaceChanged(OptionsInterfaceState *State);

public slots:
    void UserInterfaceChanged(UserInterfaceState *State);

protected:
    void changeEvent(QEvent *e);

private:
    void on_SoftfusePath_editingFinished();

private slots:
    void on_ResetProvisionCount_clicked();
    void on_RestoreDefaultLogPath_clicked();
    void on_BrowseLoggingPath_clicked();
    void on_LoggingPath_editingFinished();
    void on_BrowseSoftfusePath_clicked();
    void on_SoftfuseInclude_toggled(bool checked);
    void on_EnableLogging_toggled(bool checked);
    void on_ProvisionCountEnabled_toggled(bool checked);
    void on_GPFlagOverrideValue_editingFinished();
    void on_GPFlagOverrideEnable_toggled(bool checked);
    void on_ClearAllStoredPaths_clicked();
    void on_ClearOSImagePath_clicked();
    void on_ClearOSDnXPath_clicked();
    void on_ClearIFWIPath_clicked();
    void on_ClearFWDnXPath_clicked();
    void on_UsbTimeoutOption_editingFinished();
};

#endif // XFSTKDLDRPLUGINOPTIONSINTERFACE_H
