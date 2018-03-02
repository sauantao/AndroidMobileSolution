#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"


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
public:

	//MainWindow(QWidget *parent = Q_NULLPTR);
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	int Tesmain();
	void CreateWidget();

	Ui::MainWindow *ui;

public slots:
   

private:

	QualComMobileWidget * qualcommobile_widget;
	CmdWidget * cmd_widget;
	AdbWidget * adb_widget;
	EmmcRawWidget * emmcraw_widget;
	AsusWidget * asus_widget;
	std::list<TabWidgetBase*> tab_widgets;

protected:

	
private slots:


    void on_toolButton_OpQualcom_clicked();

    void on_toolButton_OpMediatek_clicked();

    void on_toolButton_OpIntel_clicked();

    void on_toolButton_OpSprd_clicked();

    void on_toolButton_OpAndroid_clicked();

signals:


};
#endif // MAINWINDOW_H
