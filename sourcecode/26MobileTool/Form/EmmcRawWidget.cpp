#include "EmmcRawWidget.h"
#include "ui_emmcrawwidget.h"
#include <QDir>

EmmcRawWidget::EmmcRawWidget(QTabWidget *parent, MainWindow *window) :
    TabWidgetBase(2, tr("&Emmc Raw"),parent),
    ui(new Ui::EmmcRawWidget),
  main_window_(window)
{
    ui->setupUi(this);
}

EmmcRawWidget::~EmmcRawWidget()
{
    delete ui;
}
void EmmcRawWidget::LockOnUI()
{
    //enableControl(false);
}

void EmmcRawWidget::DoFinished()
{
    //enableControl(true);
}

void EmmcRawWidget::UpdateUI()
{
    ui->retranslateUi(this);
}

void EmmcRawWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
    QString label = "EMMCRAW";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

    tab_widget->setTabText(index, label);
}

void EmmcRawWidget::SetShortCut(int , const QString &)
{

}

int EmmcRawWidget::AddItem()
{
    unsigned int row = 0;

        while(ui->tableWidget->rowCount()>0)
        {
             ui->tableWidget->removeRow(0);
        }

   for(int i = 0; i< 30 ; i++ )
   {

    QTableWidgetItem *item;
   int row =30;
   row = ui->tableWidget->rowCount();
   ui->tableWidget->insertRow(row);
   item = new QTableWidgetItem("PrimaryGPT");

   item->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
   ui->tableWidget->setItem(row, ColumnName, item);
   item = new QTableWidgetItem("0");
   ui->tableWidget->setItem(row,ColumnReadFlag, item);
   item = new QTableWidgetItem("34");
   ui->tableWidget->setItem(row,ColumnAddr, item);
   QString cfg_name = QDir::currentPath() + "/PrimaryGPT.bin";
   item = new QTableWidgetItem(cfg_name);
   ui->tableWidget->setItem(row,ColumnLength, item);

   QCheckBox *checkbox;
   checkbox = (QCheckBox *)ui->tableWidget->cellWidget(row,ColumnEnable);
   if(checkbox == NULL)
   {
      checkbox = new QCheckBox(ui->tableWidget);
      ui->tableWidget->setCellWidget(row, ColumnEnable, checkbox);
   }
   //checkbox->setChecked(false);
   checkbox->setChecked(true);

   }
   ui->tableWidget->removeRow(row);
return(0);
}

void EmmcRawWidget::on_pushButton_7_clicked()
{
   AddItem();
}
