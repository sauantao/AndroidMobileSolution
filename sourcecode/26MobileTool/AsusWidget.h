#pragma once
#ifndef ASUSWIDGET_H
#define ASUSWIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "xfstkdldrapi.h"
#include <QWidget>
#include "TabWidgetBase.h"
#include <QProcess>
#include <QtCore>

namespace Ui {
	class AsusWidget;
}
class MainWindow;

class AsusWidget : public TabWidgetBase
{
	Q_OBJECT
		enum LogType {
		kLogTypeError = 1,
		kLogTypeWarning = 2,
		kLogTypeInfo = 3,
		kLogTypeDebug = 4
	};

public:
	explicit AsusWidget(QTabWidget *parent, MainWindow* window);
	~AsusWidget();

	DECLARE_TABWIDGET_VFUNCS()

	//void status(char *message, void *clientdata);
	void  status(char *message, void *clientdata);

	//int UnBrick();

private:
	//QProcess * m_process;
	Ui::AsusWidget *ui;

	MainWindow* main_window;

	void log(int type, const char* message);
	void log(int type, std::string message);
	void log(int type, QString message);
	
public slots:
	//void setStdout();
	//void command();
private slots:
    void on_pushButton_Start_clicked();
    void on_pushButton_fwdnx_clicked();
	void on_pushButton_fwimage_clicked();
	void on_pushButton_osdnx_clicked();
	void on_pushButton_osimage_clicked();
};

#endif // ASUSWIDGET_H
