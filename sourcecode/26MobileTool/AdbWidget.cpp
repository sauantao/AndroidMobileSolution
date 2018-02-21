// adb shell getprop ro.serialno 
// adb shell getprop ro.product.model
//                   ro.product.name 
//                   ro.product.brand
// adb shell getprop ro.build.version.release 
// adb shell getprop ro.build.version.sdk
// adb shell getprop 
//[ril.product_code]: [SM - G570YZKDXXV]
//[ril.product_code2] : [SM - G570YZKDXXV]
//[ro.boot.hardware]: [samsungexynos7570]
//[ro.bootloader]: [G570YDXU1BQJ1]
//[ril.sw_ver]: [G570YDXU1BQJ1]
//[ril.sw_ver2]: [G570YDXU1BQJ1]
//[storage.mmc.size]: [15758000128]
// adb shell pm list packages

#include "AdbWidget.h"
#include "ui_AdbWidget.h"
#include <Windows.h>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QClipboard>
#include <QLabel>
#include <QTimer>

QTimer *timer;
QString danger = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #FF0350,stop: 0.4999 #FF0020,stop: 0.5 #FF0019,stop: 1 #FF0000 );border-bottom-right-radius: 0px;border-bottom-left-radius:0px;border: .px solid black;}";
QString safe = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #ffff00,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );border-bottom-right-radius: 0px;border-bottom-left-radius: 0px;border: 1px solid black;}";

AdbWidget::AdbWidget(QTabWidget *parent, MainWindow *window) :
    TabWidgetBase(1, tr("&Adb Widget"), parent),
	ui(new Ui::AdbWidget),
	 main_window(window)
{
    ui->setupUi(this);
	

	if (ui->progressBar->value()<40)
		ui->progressBar->setStyleSheet(danger);
	else
		ui->progressBar->setStyleSheet(safe);
	
    pattern = 0;
       myProcess = new QProcess(this);
       program =  QDir::currentPath()+QDir::separator()+"adb"+QDir::separator()+"adb.exe";
     //  storagePathLabel = new QLabel(this,Qt::Window); //第二个参数要加，否则会出现设备未连接时打开软件第一个menu不能点到

   // connect(main_window_, SIGNAL(signal_DeviceTestCallback()),this, SLOT(slot_DeviceTestCallback(const QString &,QColor)));
    t_process = new QProcess(this);
    emmcdl_program =  QDir::currentPath()+QDir::separator()+"Data"+QDir::separator()+"adb"+QDir::separator()+"emmcdl.exe";
    adb_program =  QDir::currentPath()+QDir::separator()+"Data"+QDir::separator()+"adb"+QDir::separator()+"adb.exe";
    folder_program =  QDir::currentPath()+QDir::separator()+"Data"+QDir::separator()+"adb"+QDir::separator();
   // connect(t_process, SIGNAL(readyReadStandardOutput()), this, SLOT(AdbsetStdout()) );
   // connect(ui->AdblineEdit, SIGNAL(returnPressed()), this, SLOT(Adbcommand()) );
    // ui->AdbtextEdit->append(emmcdl_program);
    // ui->AdbtextEdit->append(adb_program);
	
    //getStoragePath();
	

       // connect(ui->Link_Devices,SIGNAL(triggered(bool)),this,SLOT(Link_Devices));
       // connect(ui->WIFI_MAC,SIGNAL(triggered(bool)),this,SLOT(GetWifiMac()));
       // connect(ui->Ethernet_MAC,SIGNAL(triggered(bool)),this,SLOT(GetEthernetMac()));
       // connect(ui->Device_Module,SIGNAL(triggered(bool)),this,SLOT(GetModuleName()));
       // connect(ui->SerialNumber,SIGNAL(triggered(bool)),this,SLOT(GetSerialNumber()));
       // connect(ui->AndroidVersion,SIGNAL(triggered(bool)),this,SLOT(GetAndroidVersion()));
       // connect(ui->Resolution,SIGNAL(triggered(bool)),this,SLOT(GetScreenResolution()));
       // connect(ui->ICType,SIGNAL(triggered(bool)),this,SLOT(GetICType()));
       // connect(ui->getAll_Info_btn,SIGNAL(clicked(bool)),this,SLOT(GetAllInfo()));
      //  connect(ui->Apk_List,SIGNAL(triggered(bool)),this,SLOT(GetAllApkPackageName()));
        //connect(ui->Log,SIGNAL(triggered(bool)),this,SLOT(SaveLog()));
       // connect(ui->PullFile,SIGNAL(triggered(bool)),this,SLOT(PullFile()));
       // connect(ui->PushFile,SIGNAL(triggered(bool)),this,SLOT(PushFile()));
       // connect(ui->InstallAPK,SIGNAL(triggered(bool)),this,SLOT(InstallAPK()));
       // connect(ui->UninstallAPK,SIGNAL(triggered(bool)),this,SLOT(UninstallAPK()));
       // connect(ui->apk_listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(ListWeightCopy(QListWidgetItem*)));
       // connect(ui->Capture,SIGNAL(triggered(bool)),this,SLOT(CaptureScreen()));
       // connect(ui->Vedio,SIGNAL(triggered(bool)),this,SLOT(Vedio()));
       // connect(ui->Restart,SIGNAL(triggered(bool)),this,SLOT(Restart()));
       // connect(ui->NetWorkConnect,SIGNAL(triggered(bool)),this,SLOT(NetworkConnect()));
       // connect(ui->Recovery,SIGNAL(triggered(bool)),this,SLOT(Recovery()));
        //connect(ui->FastBoot,SIGNAL(triggered(bool)),this,SLOT(Fastboot()));
       //  connect(ui->About,SIGNAL(triggered(bool)),this,SLOT(About()));
        connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
}

AdbWidget::~AdbWidget()
{
    delete ui;
}
void AdbWidget::LockOnUI()
{
    //enableControl(false);
}

void AdbWidget::DoFinished()
{
    //enableControl(true);
}

void AdbWidget::UpdateUI()
{
    ui->retranslateUi(this);
}
//void AdbWidget::UpdateUI(const QString& text, QColor color = Qt::black)
//{

//}

void AdbWidget::SetTabLabel(QTabWidget *tab_widget, int index)
{
    QString label = "ADB";// LoadQString(LANGUAGE_TAG, IDS_STRING_CLONEDOWNLOAD);

    tab_widget->setTabText(index, label);
}

void AdbWidget::SetShortCut(int , const QString &)
{

}
//void AdbWidget::GetModuleName()
//{
//    if(t_process->state() == QProcess::Running)
//        return;
//    QStringList arguments;
//    arguments<<"-p"<<"Com20"<<"-info";

//    if(t_process != NULL && emmcdl_program != NULL)
//    {
//       // adb_process->setProperty("process","11");
//         ui->AdbtextEdit->clear();
//        t_process->start(emmcdl_program, arguments);
//        //myProcess->waitForFinished();
//        //qDebug() <<t_process->readAllStandardOutput();

//    }
//}

void AdbWidget::on_pushButton_clicked()
{
	PushFile();
}
void AdbWidget::AdbsetStdout()
{
	if (QSysInfo::productType() == "windows")
	{
		QTextCodec *codec = QTextCodec::codecForName("IBM 866");
		//  ui->AdbtextEdit->append(codec->toUnicode(t_process->readAllStandardOutput()));

	}
	else
		// ui->AdbtextEdit->append(t_process->readAllStandardOutput());
		QString msg;
}
void AdbWidget::Adbcommand()
{
   // ui->AdbtextEdit->clear();
    QString strCommand;
   if(QSysInfo::productType()=="windows")
        strCommand = "cmd /C ";
   // strCommand += ui->AdblineEdit->text();
    t_process->start(strCommand);


}
void AdbWidget::AdbDevices()
{
//    if(t_process->state() == QProcess::Running)
//        return;
//    QStringList arguments;
//    arguments<<"devices";//<<"Com20"<<"-info";

//    if(t_process != NULL && adb_program != NULL)
//    {
//       // adb_process->setProperty("process","11");
//        t_process->start(adb_program, arguments);
//        //myProcess->waitForFinished();
//        //qDebug() <<t_process->readAllStandardOutput();


//    }

//    QString extPath = "C:\\Python27\\python.exe";

//          // QProcess process;

//           QStringList parameter;

//           std::string temp = "P-Decode.py";

//           parameter << temp.c_str()<<"-f"<<"gesture.key";

//          // process.startDetached(extPath, parameter);
//          t_process->start(extPath, parameter);

          QString extPath = "D:\\26-MOBILE\\CPP\\Mobiletool\\Win32\\26MobileTool\\mobiletool.exe";

                // QProcess process;

                 QStringList parameter;

                 std::string temp = "-d";

                 parameter << temp.c_str()<<"MTK_AllInOne_DA.bin"<<"-s"<<"D:\\ROM\\inni\\22\\MT6735_Android_scatter.txt"<<"-c"<<"download"<<"-b"<<"-r";

                // process.startDetached(extPath, parameter);
                t_process->start(extPath, parameter);

}
void AdbWidget::GpttoRawprogram()
{
    QString extPath = "C:\\Python27\\python.exe";

          // QProcess process;

           QStringList parameter;

           std::string temp = "GPTAnalyzer.py";

           parameter << temp.c_str()<<"PrimaryGPT.bin";

          // process.startDetached(extPath, parameter);
         //  ui->AdbtextEdit->clear();

          t_process->start(extPath, parameter);


}
void AdbWidget::on_toolButton_2_clicked()
{
  //AdbDevices();
  //GpttoRawprogram();

  /// ShellExecute(NULL, QString("open").toStdWString().c_str(), QString("devmgmt.msc").toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
   // std::string as_par = "01478.svg";

   // ShellExecute(NULL,QString("open").toStdWString().c_str(), QString("D:\\26-MOBILE\\PADSVX.0\\New folder\\powerpcb.exe").toStdWString().c_str(),QString("D:\\26-MOBILE\\pcbview\\26mobile-iPhone6Splus.pcb").toStdWString().c_str(), NULL, SW_SHOWNORMAL);
    //QString path = "c:\\temp";//QString::fromLocal8Bit(Logger::GetSPFlashToolLogFolder().c_str());

    //QProcess::startDetached("explorer "+path);

    //QString extPath = "D:\\26-MOBILE\\CPP\\Mobiletool\\Win32\\26MobileTool\\mobiletool.exe";

    //      // QProcess process;

    //       QStringList parameter;

    //       std::string temp = "-d";

    //       parameter << temp.c_str()<<"C:\\MTK_AllInOne_DA.bin"<<"-s"<<"D:\\ROM\\inni\\22\\MT6735_Android_scatter.txt"<<"-c"<<"download"<<"-b"<<"-r";

    //      // process.startDetached(extPath, parameter);
    //      t_process->start(extPath, parameter);
	GetAllInfo();


}

void AdbWidget::on_pushButton_2_clicked()
{
   // GestureDialog dialog(this);
   // dialog.setModal(true);
   // dialog.exec();
}
void AdbWidget::slot_DeviceTestCallback(const QString &msg, QColor color)
{

   // ui->AdbtextEdit->setUpdatesEnabled(FALSE);
   // ui->AdbtextEdit->setTextColor(color);
   // ui->AdbtextEdit->append(msg+"ggggggggggg");
    /* mtk10304[nailiang.song] data_bus_test + addr_bus_test, hit append(msg) 93 times, then tool crash,
    comment qApp->processEvents(), tool NOT crash */
    //qApp->processEvents();
   // ui->AdbtextEdit->setUpdatesEnabled(TRUE);
}
void AdbWidget::getStoragePath()
{
    QStringList arguments;
    arguments<<"shell"<<"echo"<<"$EXTERNAL_STORAGE";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","17");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::LinkDevices()
{
    if(myProcess->state() == QProcess::Running)
        return;
   // ui->DeviceList->clear();
    QStringList arguments;
    arguments<<"devices";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","8");
        myProcess->start(program, arguments);

    }

}

void AdbWidget::GetWifiMac()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"cat"<<"/sys/class/net/wlan0/address";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","9");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }

}

void AdbWidget::GetEthernetMac()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"cat"<<"/sys/class/net/eth0/address";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","10");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();

    }
}

void AdbWidget::GetModuleName()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.product.model";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","11");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::GetSerialNumber()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.serialno";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","12");
        myProcess->start(program, arguments);
    }
}

void AdbWidget::GetAndroidVersion()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"getprop"<<"ro.build.version.release";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","13");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::GetScreenResolution()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"wm"<<"size";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","14");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::GetICType()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"cat"<<"/proc/cpuinfo";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","15");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::GetAllInfo()
{
	
	pattern = 1;
	
    GetWifiMac();
    myProcess->waitForFinished();
    GetSerialNumber();
    myProcess->waitForFinished();
    GetScreenResolution();
    myProcess->waitForFinished();
    GetAndroidVersion();
    myProcess->waitForFinished();
    GetEthernetMac();
    myProcess->waitForFinished();
    GetModuleName();
    myProcess->waitForFinished();
    GetICType();
    myProcess->waitForFinished();
	GetModel();
	myProcess->waitForFinished();
	GetEmmcSize();
	myProcess->waitForFinished();
	if (pattern)
	//	ui->AdbtextEdit->append("一键获取所有信息完成");

		
    pattern = 0;

}

void AdbWidget::GetAllApkPackageName()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"shell"<<"pm"<<"list"<<"packages";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->setProperty("process","16");
      //  ui->apk_listWidget->clear();
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::SaveLog()
{
    //QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存Log文件到"),"D:\\",tr("Text files (*.txt);"));
    ////qDebug() <<fileName;

    //QStringList arguments;
    //arguments<<"logcat"<<"-v"<<"threadtime";
    //if(myProcess != NULL && program != NULL && fileName != "")
    //{
    //    myProcess->setStandardOutputFile(fileName);
    //    myProcess->start(program, arguments);
    //    if(QMessageBox::information(this,QStringLiteral("读取Log中...."),
    //                                QStringLiteral("是否停止读取？"))==QMessageBox::Ok)
    //    {
    //       myProcess->close();
    //       myProcess = new QProcess(this);
    //       connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
    //    }

   // }


}

void AdbWidget::PullFile()
{
    //bool ok;
    //QString fileName;
    //QStringList arguments;
    //QString remotePath = QInputDialog::getText(this,QStringLiteral("系统目录"),
    //                                           QStringLiteral("请输入要读取的系统文件:"),
    //                                           QLineEdit::Normal,
    //                                           QStringLiteral("/sdcard/"), &ok);
    //if(ok && !remotePath.isEmpty())
    //{
    //   fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存文件到"),"D:\\");
    //}
    //else
    //{
    //   return;
    //}

    //arguments<<"pull"<<remotePath<<fileName;
    //if(myProcess != NULL && program != NULL)
    //{
    //    myProcess->setProperty("process","1");
    //    myProcess->start(program, arguments);
    //    //myProcess->waitForFinished();

    //}
}

void AdbWidget::PushFile()
{
    bool ok = false;
    QString remotePath;
    QStringList arguments;
    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("选择要发送的文件"),"D:\\");

    if(!fileName.isEmpty())
    {
        remotePath = QInputDialog::getText(this,QStringLiteral("系统目录"),
                                                   QStringLiteral("请输入要发送到的目录:"),
                                                   QLineEdit::Normal,
                                                   QStringLiteral("/sdcard/"), &ok);
    }

    arguments<<"push"<<fileName<<remotePath;
    if(myProcess != NULL && program != NULL && ok)
    {
        myProcess->setProperty("process","2");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
    }
}

void AdbWidget::InstallAPK()
{
    QStringList arguments;
    QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("选择要安装的文件"),"D:\\");
    arguments<<"install"<<fileName;
    if(myProcess != NULL && program != NULL && !fileName.isEmpty())
    {
        myProcess->setProperty("process","3");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();
    }
}

void AdbWidget::UninstallAPK()
{
    bool ok;
    QStringList arguments;
    QString packageName = QInputDialog::getText(this,QStringLiteral("应用包名"),
                                                          QStringLiteral("请输入要卸载的应用的包名:"),
                                                          QLineEdit::Normal,
                                                          QStringLiteral("com."), &ok);
    arguments<<"uninstall"<<packageName;
    if(myProcess != NULL && program != NULL && !packageName.isEmpty() && ok)
    {
        myProcess->setProperty("process","4");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
        //qDebug() <<myProcess->readAllStandardOutput();

    }
}

void AdbWidget::ListWeightCopy(QListWidgetItem * item)
{
    QClipboard *clipboard = QApplication::clipboard();   //获取系统剪贴板指针
    clipboard->clear();                                 //清空剪贴板中的内容
    clipboard->setText(item->text());                  //设置剪贴板内容
}

void AdbWidget::CaptureScreen()
{
//    QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存文件到"),"D:\\",
//                                 tr("Images (*.png);"));
//    //qDebug() <<fileName;
//
//    QStringList arguments;
//    if(storagePath == NULL || storagePath == "" || storagePath.isEmpty())
//    {
//      //  getStoragePath();
//        myProcess->waitForFinished();
//    }
//    arguments<<"shell"<<"screencap"<<"-p"<<storagePath+"/sc.png";
//    if(myProcess != NULL && program != NULL && fileName != "")
//    {
//        myProcess->setProperty("process","5");
//        fileNameTemp = fileName;
//        myProcess->start(program, arguments);
//    }
}

void AdbWidget::Vedio()
{
    //QString fileName = QFileDialog::getSaveFileName(this,QStringLiteral("保存视频文件到"),"D:\\",
    //                             tr("Vedio files (*.mp4);"));
    ////qDebug() <<fileName;

    //QStringList arguments;
    //if(storagePath == NULL || storagePath == "" || storagePath.isEmpty())
    //{
    //   /// getStoragePath();
    //    myProcess->waitForFinished();
    //}
    //arguments<<"shell"<<"screenrecord"<<storagePath+"/1.mp4";
    //if(myProcess != NULL && program != NULL && fileName != "")
    //{
    //    myProcess->start(program, arguments);
    //    if(QMessageBox::information(this,QStringLiteral("录屏中...."),
    //                                QStringLiteral("是否停止录屏？"))==QMessageBox::Ok)
    //    {
    //       myProcess->close();
    //       myProcess = new QProcess(this);
    //       connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
    //       arguments.clear();
    //       arguments<<"pull"<<storagePath+"/1.mp4"<<fileName;
    //       myProcess->start(program, arguments);
    //    }

    //}

}

void AdbWidget::Restart()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"reboot";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void AdbWidget::NetworkConnect()
{
    bool ok;
    QStringList arguments;
    QString IP = QInputDialog::getText(this,QStringLiteral("设备IP"),
                                                          QStringLiteral("请输入连接的设备的IP:"),
                                                          QLineEdit::Normal,
                                                          QStringLiteral("192.168."), &ok);
    arguments<<"connect"<<IP;
    if(myProcess != NULL && program != NULL && !IP.isEmpty() && ok)
    {
        myProcess->setProperty("process","7");
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();

    }
}

void AdbWidget::Recovery()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"reboot"<<"recovery";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void AdbWidget::Fastboot()
{
    if(myProcess->state() == QProcess::Running)
        return;
    QStringList arguments;
    arguments<<"reboot"<<"bootloader";
    if(myProcess != NULL && program != NULL)
    {
        myProcess->start(program, arguments);
    }
}

void AdbWidget::About()
{
    QMessageBox::about(this,QStringLiteral("关于"),QStringLiteral("<font size='26' color='blue'>欢迎使用ADB Tool</font>\
                         <font size='5' color='black'><div style='text-align:center'>版本：V1.2</div></font>\
                         <font size='5' color='black'><div style='text-align:center'>作者：杨永达</div></font>"));
}

void AdbWidget::FinishSolute(int)
{
    if(myProcess->property("process") == "1")
    {
        QMessageBox::information(this,QStringLiteral("传输结束"),QStringLiteral("文件传输结束"));
		//ui->AdbtextEdit->append("文件传输完成");
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "2")
    {
        QMessageBox::information(this,QStringLiteral("传输结束"),QStringLiteral("文件传输结束"));
		//ui->AdbtextEdit->append("文件传输完成");
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "3")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("INSTALL_FAILED_OLDER_SDK"))
        {
            QMessageBox::warning(this, QStringLiteral("SDK版本问题"),QStringLiteral("请确认系统版本是否低于APK要求的最低SDK"));
			//ui->AdbtextEdit->append("安装失败");
        }
        else
        {
			//ui->AdbtextEdit->append("安装成功");
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "4")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("DELETE_FAILED_INTERNAL_ERROR"))
        {
            QMessageBox::warning(this, QStringLiteral("卸载失败"),QStringLiteral("请确认输入的包名正确或是否是系统应用"));
			//ui->AdbtextEdit->append("卸载失败");

        }
        else
        {
			//ui->AdbtextEdit->append("卸载成功");

        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "5")
    {
        QStringList arguments;
        myProcess->close();
        myProcess = new QProcess(this);
        myProcess->setProperty("process","6");
        connect(myProcess,SIGNAL(finished(int)),this,SLOT(FinishSolute(int)));
        arguments<<"pull"<<storagePath+"/sc.png"<<fileNameTemp;
        myProcess->start(program, arguments);
        //myProcess->waitForFinished();
    }
    else if(myProcess->property("process") == "6")
    {
        //ui->statusBar->showMessage(QStringLiteral("截图完成"),2000);
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "7")
    {
        //qDebug() <<myProcess->readAllStandardOutput();
        QString output = QString(myProcess->readAllStandardOutput());
        if(output.contains("unable to connect to"))
        {
            QMessageBox::warning(this, QStringLiteral("连接失败"),QStringLiteral("请确认IP是否正确"));
			//ui->AdbtextEdit->append("连接失败");

        }
        else
        {
			//ui->AdbtextEdit->append("连接成功");
			QString msg;
        }

        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "8")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\tdevice"))
            {
                QStringList deviceName = str.split("\t");
               // ui->DeviceList->addItem(deviceName.at(0));
				//ui->AdbtextEdit->append("扫描已连接的设备结束");
            }
        }
        myProcess->setProperty("process",0);
       // getStoragePath();
    }
    else if(myProcess->property("process") == "9")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(!output.contains("No such file or directory")){
            QStringList strList = output.split("\r\n");
            foreach (QString str, strList) {
                if(str.contains(":"))
                {
					//ui->WIFI_MAC_lineEdit->clear();
                    ui->WIFI_MAC_lineEdit->setText(str);
                    //if(!pattern)
						//ui->AdbtextEdit->append("获取WIFI MAC完成");
                }
            }
        }else{
            ui->WIFI_MAC_lineEdit->setText(QStringLiteral("请检查WIFI模块是否正常"));
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "10")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        if(!output.contains("No such file or directory")){
            QStringList strList = output.split("\r\n");
            foreach (QString str, strList) {
                if(str.contains(":"))
                {
					//ui->EthernetMAC_lineEdit->clear();
                    ui->EthernetMAC_lineEdit->setText(str);
                  //  if(!pattern)
					//	ui->AdbtextEdit->append("获取以太网 MAC完成");
                }
            }
        }else {
            ui->EthernetMAC_lineEdit->setText(QStringLiteral("请检查以太网模块是否正常"));
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "11")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
				//ui->ModuleName_lineEdit->clear();
               ui->ModuleName_lineEdit->setText(str);
			   if (!pattern)
				   // ui->AdbtextEdit->append("获取设备型号完成");
				   QString msg;
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "12")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        ui->SerialNumber_lineEdit->setText(output);
		if (!pattern) 
			//ui->AdbtextEdit->append("获取序列号完成");
		
			
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "13")
    {
        QString output = QString(myProcess->readAllStandardOutput());
       // QStringList strList = output.split("\r\n");
        ////foreach (QString str, strList) {
           // if(str.contains("\r"))
           // {
				//ui->Android_Version_lineEdit->clear();
               ui->Android_Version_lineEdit->setText(output);
			  // if (!pattern)
				   //  ui->AdbtextEdit->append("获取Android版本完成");
				 //  QString msg;

          //  }
       // }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "14")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split(":");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
				//ui->Resolution_lineEdit->clear();
               ui->Resolution_lineEdit->setText(str);
			   if (!pattern)
				   // ui->AdbtextEdit->append("获取屏幕分辨率完成");
				   QString aaab;
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "15")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\r\n");
        foreach (QString str, strList) {
            if(str.contains("Hardware")){
				//ui->ICType_lineEdit->clear();
                ui->ICType_lineEdit->setText(str.split(":").at(1));
				if (!pattern)

					//	ui->AdbtextEdit->append("获取主芯片型号完成");
					QString aaa;
					
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "16")
    {
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
                //qDebug() <<str.length();
               //ui->apk_listWidget->addItem(str.mid(8,str.length()-9));
			  // ui->AdbtextEdit->append("已获取所有APK包名");
            }
        }
        myProcess->setProperty("process",0);
    }
    else if(myProcess->property("process") == "17")
    {
        //qDebug() <<myProcess->readAllStandardOutput();
        QString output = QString(myProcess->readAllStandardOutput());
        QStringList strList = output.split("\r\n");
        foreach (QString str, strList) {
            if(str.contains("\r"))
            {
               //qDebug() <<str.mid(0,str.length()-1);
              // storagePath = str.mid(0,str.length()-1);
              // storagePathLabel->setFrameStyle(QFrame::Box | QFrame::Sunken);//设置label的形状和阴影模式的,这里采用的box形状和凹陷模式
              // storagePathLabel->setText(storagePath);//设置文本内容
              // storagePathLabel->setTextFormat(Qt::RichText);//设置文本格式为富文本格式，又称多文本格式，用于跨平台使用的
              // storagePathLabel->setOpenExternalLinks(true);//运行打开label上的链接
              // ui->statusBar->addPermanentWidget(storagePathLabel);//将label附加到状态栏上，永久性的
            }
        }
        myProcess->setProperty("process",0);
    }
	else if (myProcess->property("process") == "18")
	{
		//qDebug() <<myProcess->readAllStandardOutput();
		QString output = QString(myProcess->readAllStandardOutput());
		//QStringList strList = output.split("\n");
		//foreach(QString str, strList) {
			//if (str.contains("model"))
			//{
				ui->lineEdit_Model->setText(output);
			//}
		//}
		myProcess->setProperty("process", 0);
	}
	else if (myProcess->property("process") == "19")
	{
		QString output = QString(myProcess->readAllStandardOutput());
		
		ui->lineEdit_Emmc->setText(output);
		
		myProcess->setProperty("process", 0);
	}
	else if (myProcess->property("process") == "23")
	{
		QString output = QString(myProcess->readAllStandardOutput());

		ui->lineEdit_product_code->setText(output);

		myProcess->setProperty("process", 0);
	}
	else if (myProcess->property("process") == "24")
	{
		QString output = QString(myProcess->readAllStandardOutput());

		ui->lineEdit_sw_ver->setText(output);

		myProcess->setProperty("process", 0);
	}
}
void AdbWidget::bootIMG()
{
    QString output;
    QProcess fastboot;
    fastboot.setProcessChannelMode(QProcess::MergedChannels);
    fastboot.start("\"" + this->sdk + "\"fastboot devices");
    fastboot.waitForFinished();
    output = fastboot.readAll();
    if (output.contains("fastboot"))
    {
        QProcess *process=new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        QString tmp;
        QString imgFileName = QFileDialog::getOpenFileName(this, tr("Choose img file..."), ".", tr("IMG File ")+"(*.img)");
        if (!imgFileName.isEmpty())
        {
            process->start("\"" + sdk + "\"fastboot boot " + imgFileName);
            process->waitForFinished(-1);
            process->terminate();
        }
        else
            QMessageBox::warning(this, "Error!", "Operation cancelled!", QMessageBox::Ok);
        delete process;
    }
    else
    {
      //  this->phone->slotConnectionChanged(FASTBOOT,this->phone->serialNumber);
    }
}
void AdbWidget::flashSPL()
{
    QString output;
    QProcess fastboot;
    fastboot.setProcessChannelMode(QProcess::MergedChannels);
    fastboot.start("\"" + this->sdk + "\"fastboot devices");
    fastboot.waitForFinished();
    output = fastboot.readAll();
    if (output.contains("fastboot"))
    {
        QProcess *process=new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        QString tmp;
        QString imgFileName = QFileDialog::getOpenFileName(this, tr("Choose hboot img file..."), ".", tr("IMG File ")+"(*.img)");
        if (!imgFileName.isEmpty())
        {
            process->start("\"" + sdk + "\"fastboot flash hboot " + imgFileName);
            process->waitForFinished(-1);
            tmp = process->readAll();
            if (tmp.contains("error"))
                QMessageBox::warning(this, tr("Error!"), tmp, QMessageBox::Ok);
            else
                QMessageBox::information(this, tr("Success!"), tmp, QMessageBox::Ok);
            process->terminate();
        }
        else
            QMessageBox::warning(this, tr("Error!"), tr("Operation cancelled!"), QMessageBox::Ok);
        delete process;
    }
    else
    {
      //  this->phone->slotConnectionChanged(FASTBOOT,this->phone->serialNumber);
    }
}

void AdbWidget::flashRadio()
{
    QString output;
    QProcess fastboot;
    fastboot.setProcessChannelMode(QProcess::MergedChannels);
    fastboot.start("\"" + this->sdk + "\"fastboot devices");
    fastboot.waitForFinished();
    output = fastboot.readAll();
    if (output.contains("fastboot"))
    {
        QProcess *process=new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        QString tmp;
        QString imgFileName = QFileDialog::getOpenFileName(this, tr("Choose radio img file..."), ".", tr("IMG File ")+"(*.img)");
        if (!imgFileName.isEmpty())
        {
            process->start("\"" + sdk + "\"fastboot flash radio " + imgFileName);
            process->waitForFinished(-1);
            tmp = process->readAll();
            if (tmp.contains("error"))
                QMessageBox::warning(this, tr("Error!"), tmp, QMessageBox::Ok);
            else
                QMessageBox::information(this, tr("Success!"), tmp, QMessageBox::Ok);
            process->terminate();
        }
        else
            QMessageBox::warning(this, tr("Error!"), tr("Operation cancelled!"), QMessageBox::Ok);
        delete process;
    }
    else
    {
       // this->phone->slotConnectionChanged(FASTBOOT,this->phone->serialNumber);
    }
}

void AdbWidget::flashRecovery()
{
    QString output;
    QProcess fastboot;
    fastboot.setProcessChannelMode(QProcess::MergedChannels);
    fastboot.start("\"" + this->sdk + "\"fastboot devices");
    fastboot.waitForFinished();
    output = fastboot.readAll();
    if (output.contains("fastboot"))
    {
        QProcess *process=new QProcess();
        process->setProcessChannelMode(QProcess::MergedChannels);
        QString tmp;
        QString imgFileName = QFileDialog::getOpenFileName(this, tr("Choose recovery img file..."), ".", tr("IMG File ")+"(*.img)");
        if (!imgFileName.isEmpty())
        {
            process->start("\"" + sdk + "\"fastboot flash recovery " + imgFileName);
            process->waitForFinished(-1);
            tmp = process->readAll();
            if (tmp.contains("error"))
                QMessageBox::warning(this, tr("Error!"), tmp, QMessageBox::Ok);
            else
                QMessageBox::information(this, tr("Success!"), tmp, QMessageBox::Ok);
            process->terminate();
        }
        else
            QMessageBox::warning(this, tr("Error!"), tr("Operation cancelled!"), QMessageBox::Ok);
        delete process;
    }
    else
    {
        //this->phone->slotConnectionChanged(FASTBOOT,this->phone->serialNumber);
    }
}
void AdbWidget::GetModel()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell"<<"getprop"<<"ro.product.model";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "18");
		myProcess->start(program, arguments);

	}
}
void AdbWidget::GetEmmcSize()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "storage.mmc.size";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "19");
		myProcess->start(program, arguments);

	}
}

void AdbWidget::GetImel1()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "ro.product.model";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "20");
		myProcess->start(program, arguments);

	}
}

void AdbWidget::GetImel2()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "ro.product.model";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "21");
		myProcess->start(program, arguments);

	}
}

void AdbWidget::GetRegion()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "ro.product.model";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "22");
		myProcess->start(program, arguments);

	}
}

void AdbWidget::GetProducCode()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "ril.product_code";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "23");
		myProcess->start(program, arguments);

	}
}

void AdbWidget::GetSwVer()
{
	if (myProcess->state() == QProcess::Running)
		return;
	// ui->DeviceList->clear();
	QStringList arguments;
	arguments << "shell" << "getprop" << "ril.sw_ver";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "24");
		myProcess->start(program, arguments);

	}
}
void AdbWidget::on_toolButton_Reboot_clicked()
{
	/*if (myProcess->state() == QProcess::Running)
		return;
	QStringList arguments;
	arguments << "reboot";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "25");
		myProcess->start(program, arguments);

	}*/
	Restart();
}
void AdbWidget::on_toolButton_TurnOff_clicked()
{
	if (myProcess->state() == QProcess::Running)
		return;
	QStringList arguments;
	arguments << "reboot"<<"recovery";
	if (myProcess != NULL && program != NULL)
	{
		myProcess->setProperty("process", "26");
		myProcess->start(program, arguments);

	}
}