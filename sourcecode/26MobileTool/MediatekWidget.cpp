#include "MediatekWidget.h"
#include "ui_MediatekWidget.h"



MediatekWidget::MediatekWidget(QTabWidget *parent, MainWindow *window) :
	TabWidgetBase(6, tr("&Mediatek Widget"), parent),
	ui(new Ui::MediatekWidget),
	main_window_(window)
{
	ui->setupUi(this);
}


MediatekWidget::~MediatekWidget()
{
	delete ui;
}
void MediatekWidget::LockOnUI()
{
	//enableControl(false);
}

void MediatekWidget::DoFinished()
{
	//enableControl(true);
}

void MediatekWidget::UpdateUI()
{
	ui->retranslateUi(this);
}


void MediatekWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
	QString label = "ADB";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

	tab_widget->setTabText(index, label);
}

void MediatekWidget::SetShortCut(int, const QString &)
{

}