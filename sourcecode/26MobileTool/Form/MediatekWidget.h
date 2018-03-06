#ifndef MEDIATEKWIDGET_H
#define MEDIATEKWIDGET_H

#include <QWidget>
#include <QtCore>
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
private:

	Ui::MediatekWidget* ui;
	MainWindow* main_window_;

};
#endif // MEDIATEKWIDGET_H
