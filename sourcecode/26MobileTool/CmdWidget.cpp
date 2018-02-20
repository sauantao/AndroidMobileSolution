#include "CmdWidget.h"
#include "ui_cmdwidget.h"
#include <QSerialPortInfo>




CmdWidget::CmdWidget(QTabWidget *parent, MainWindow *window) :
    TabWidgetBase(0, tr("&Cmd Widget"), parent),
    ui(new Ui::CmdWidget),
    main_window_(window)
{
    ui->setupUi(this);
    m_process = new QProcess(this);
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(setStdout()) );
   // connect(ui->comboBox, SIGNAL(currentIndexChanged()), this, SLOT(command()));
	//connect(ui->comboBox, SIGNAL(currentTextChanged()), this, SLOT(command()));
	//connect(ui->comboBox, SIGNAL(editTextChanged()), this, SLOT(command()));
	connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(commandLineEdit()));
	connect(ui->pushButton_Execute, SIGNAL(clicked()), this, SLOT(command()));
	//command();
}
CmdWidget::~CmdWidget()
{
    delete ui;
}
void CmdWidget::LockOnUI()
{
    //enableControl(false);
}

void CmdWidget::DoFinished()
{
    //enableControl(true);
}

void CmdWidget::UpdateUI()
{
    ui->retranslateUi(this);
}

void CmdWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
    QString label = "CMD";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

    tab_widget->setTabText(index, label);
}

void CmdWidget::SetShortCut(int , const QString &)
{

}
void CmdWidget::setStdout()
{
    if(QSysInfo::productType()=="windows")
    {
        QTextCodec *codec = QTextCodec::codecForName("IBM 866");
        ui->textEdit->append( codec->toUnicode(m_process->readAllStandardOutput()));

    }
    else
        ui->textEdit->append( m_process->readAllStandardOutput());
}
void CmdWidget::command()
{
    ui->textEdit->clear();
    QString strCommand;
    if(QSysInfo::productType()=="windows")
        strCommand = "cmd /C ";
	strCommand += ui->comboBox->currentText();
    m_process->start(strCommand);
	//ui->textEdit->append(strCommand);
}
void CmdWidget::commandLineEdit()
{
	ui->textEdit->clear();
	QString strCommand;
	if (QSysInfo::productType() == "windows")
		strCommand = "cmd /C ";
	strCommand += ui->lineEdit->text();
	m_process->start(strCommand);
	//ui->textEdit->append(strCommand);
}
//void CmdWidget::on_pushButton_clicked()
//{
//	command();
//}
