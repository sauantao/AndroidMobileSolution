#ifndef ASUSWIDGET_H
#define ASUSWIDGET_H

#include "TabWidgetBase.h"
#include <QTabWidget>
#include <QWidget>



namespace Ui {
	class AsusWidget;
}

class MainWindow;

class AsusWidget : public TabWidgetBase
{
		Q_OBJECT

public:
	explicit AsusWidget(QTabWidget *parent, MainWindow* window);
	~AsusWidget();

	DECLARE_TABWIDGET_VFUNCS()



private:

	Ui::AsusWidget *ui;

	MainWindow* main_window;

};


#endif // ASUSWIDGET_H
