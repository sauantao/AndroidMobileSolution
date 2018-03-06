#include "AsusWidget.h"
#include "ui_AsusWidget.h"
#include <QFileDialog>


AsusWidget::AsusWidget(QTabWidget *parent, MainWindow *window) :
	TabWidgetBase(5, tr("&Asus Widget"), parent),ui(new Ui::AsusWidget),main_window(window)
{
	ui->setupUi(this);
}
AsusWidget::~AsusWidget()
{
	delete ui;
}
void AsusWidget::LockOnUI()
{
	//enableControl(false);
}
void AsusWidget::DoFinished()
{
	//enableControl(true);
}
void AsusWidget::UpdateUI()
{
	ui->retranslateUi(this);
}
void AsusWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
	QString label = "CMD";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

	tab_widget->setTabText(index, label);
}
void AsusWidget::SetShortCut(int, const QString &)
{

}



