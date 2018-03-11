#ifndef MEDIATEKWIDGET_H
#define MEDIATEKWIDGET_H

#include <QWidget>
#include <QtCore>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "TabWidgetBase.h"

namespace Ui {

	class MediatekWidget;
}
class MainWindow;
class MediatekWidget : public TabWidgetBase
{
	Q_OBJECT

public:
	explicit MediatekWidget(QTabWidget *parent, MainWindow* window);
	
	~MediatekWidget();
	DECLARE_TABWIDGET_VFUNCS()

 private slots:
    void on_pushButton_Loadfile_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Load_clicked();

    void on_pushButton_Clear_clicked();

private:

	Ui::MediatekWidget* ui;
	MainWindow* main_window_;

};
#endif // MEDIATEKWIDGET_H
