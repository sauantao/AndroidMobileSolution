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
void MediatekWidget::on_pushButton_Loadfile_clicked()
{

}

void MediatekWidget::on_pushButton_Save_clicked()
{
	QFile file("d:/aa.txt");
	QTextStream textstream(&file);
	if (file.open(QIODevice::ReadOnly))
	{
		QString str = ui->textEdit->toPlainText();//textstream.readAll();
		ui->textEdit->setPlainText(str);
		file.close();
	}
	else
	{
		QMessageBox::critical(this,QString::fromUtf8("Chú ý"), QString::fromUtf8("Chú ý không mở được file"));
	}
}

void MediatekWidget::on_pushButton_Load_clicked()
{
	QFile file("d:/aa.txt");
	QTextStream textstream(&file);
	QString str = textstream.readAll();
	ui->textEdit->setPlainText(str);
	file.close();
}

void MediatekWidget::on_pushButton_Clear_clicked()
{
	ui->textEdit->clear();
}
