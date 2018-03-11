#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QWidget>


namespace Ui {
	class IntelSettingDialog;
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

class IntelSettingDialog : public QDialog
{
	Q_OBJECT

public:

	OptionsInterfaceState CurrentState;
	OptionsInterfaceState PrevState;

	explicit IntelSettingDialog(QWidget *parent = 0);
	~IntelSettingDialog();

	//QTabWidget *GetTabInterface();
	QString DetermineCurrentFileSearchPath(QString BinPath);
	bool VerifyBinaryFilePath(QString BinPath);
	QString LastError;
	bool LineEditWA;
	void ReportErrors();
	//Ui::XfstkDldrPluginOptionsInterface *ui;
	QFileDialog OpenFile;

signals:
	void OptionsInterfaceChanged(OptionsInterfaceState *State);

	public slots:
	void UserInterfaceChanged(UserInterfaceState *State);

protected:
	void changeEvent(QEvent *e);

private:
	void on_SoftfusePath_editingFinished();

	Ui::IntelSettingDialog *ui;


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

#endif // DIALOG_H
