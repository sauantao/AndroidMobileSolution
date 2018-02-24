/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QVBoxLayout *verticalLayout_process;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QLabel *label_SpeedInfo;
    QLabel *label_total;
    QLabel *label_COMPortInfo;
    QLabel *label_storage;
    QLabel *label_usbStatus;
    QLabel *label_time;
    QLabel *label_status_port;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 685);
        MainWindow->setMinimumSize(QSize(1000, 685));
        MainWindow->setMaximumSize(QSize(1000, 685));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AppIcon/image/Mobile.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(3, 3, 3, 3);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setStyleSheet(QStringLiteral(""));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(true);
        tabWidget->setMovable(true);

        verticalLayout->addWidget(tabWidget);

        verticalLayout_process = new QVBoxLayout();
        verticalLayout_process->setSpacing(0);
        verticalLayout_process->setObjectName(QStringLiteral("verticalLayout_process"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_process->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_SpeedInfo = new QLabel(centralWidget);
        label_SpeedInfo->setObjectName(QStringLiteral("label_SpeedInfo"));
        label_SpeedInfo->setMinimumSize(QSize(100, 0));
        label_SpeedInfo->setMaximumSize(QSize(500, 100));
        label_SpeedInfo->setFrameShape(QFrame::Panel);
        label_SpeedInfo->setFrameShadow(QFrame::Sunken);
        label_SpeedInfo->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_SpeedInfo);

        label_total = new QLabel(centralWidget);
        label_total->setObjectName(QStringLiteral("label_total"));
        label_total->setMinimumSize(QSize(100, 0));
        label_total->setMaximumSize(QSize(500, 100));
        label_total->setFrameShape(QFrame::Panel);
        label_total->setFrameShadow(QFrame::Sunken);
        label_total->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_total);

        label_COMPortInfo = new QLabel(centralWidget);
        label_COMPortInfo->setObjectName(QStringLiteral("label_COMPortInfo"));
        label_COMPortInfo->setMinimumSize(QSize(100, 0));
        label_COMPortInfo->setMaximumSize(QSize(500, 100));
        label_COMPortInfo->setFrameShape(QFrame::Panel);
        label_COMPortInfo->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_COMPortInfo);

        label_storage = new QLabel(centralWidget);
        label_storage->setObjectName(QStringLiteral("label_storage"));
        label_storage->setMinimumSize(QSize(100, 0));
        label_storage->setMaximumSize(QSize(500, 100));
        label_storage->setFrameShape(QFrame::Panel);
        label_storage->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_storage);

        label_usbStatus = new QLabel(centralWidget);
        label_usbStatus->setObjectName(QStringLiteral("label_usbStatus"));
        label_usbStatus->setMinimumSize(QSize(100, 0));
        label_usbStatus->setMaximumSize(QSize(500, 100));
        label_usbStatus->setFrameShape(QFrame::Panel);
        label_usbStatus->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_usbStatus);

        label_time = new QLabel(centralWidget);
        label_time->setObjectName(QStringLiteral("label_time"));
        label_time->setMinimumSize(QSize(100, 0));
        label_time->setMaximumSize(QSize(500, 100));
        label_time->setFrameShape(QFrame::Panel);
        label_time->setFrameShadow(QFrame::Sunken);
        label_time->setLineWidth(1);
        label_time->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_time);

        label_status_port = new QLabel(centralWidget);
        label_status_port->setObjectName(QStringLiteral("label_status_port"));
        label_status_port->setMinimumSize(QSize(300, 0));
        label_status_port->setMaximumSize(QSize(300, 100));
        label_status_port->setFrameShape(QFrame::Panel);
        label_status_port->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(label_status_port);


        verticalLayout_process->addLayout(horizontalLayout);


        verticalLayout->addLayout(verticalLayout_process);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMinimumSize(QSize(0, 0));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setEnabled(false);
        statusBar->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(10);
        statusBar->setFont(font);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "26 QualCom Tool", 0));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_SpeedInfo->setText(QApplication::translate("MainWindow", "0 B/s", 0));
        label_total->setText(QApplication::translate("MainWindow", "0 Bytes", 0));
        label_COMPortInfo->setText(QString());
        label_storage->setText(QString());
        label_usbStatus->setText(QString());
        label_time->setText(QApplication::translate("MainWindow", "00 : 00", 0));
        label_status_port->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
