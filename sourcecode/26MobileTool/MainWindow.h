#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "tchar.h"
#include <QColor>


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

	int Tesmain();
	void CreateWidget();

	Ui::MainWindow *ui;

public slots:
   

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



	
private slots:


signals:



};
