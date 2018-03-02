#ifndef CMDWIDGET_H
#define CMDWIDGET_H

#include <QWidget>
#include "TabWidgetBase.h"
#include <QProcess>
#include <QtCore>

namespace Ui {
class CmdWidget;
}
class MainWindow;
class CmdWidget : public TabWidgetBase
{
    Q_OBJECT

public:
    explicit CmdWidget(QTabWidget *parent, MainWindow* window);
    ~CmdWidget();

DECLARE_TABWIDGET_VFUNCS()
private:
     QProcess *m_process;
    Ui::CmdWidget *ui;
    MainWindow* main_window_;
public slots:
    void setStdout();
    void command();
	void commandLineEdit();
private slots:

//void on_pushButton_clicked();

};

#endif // CMDWIDGET_H
