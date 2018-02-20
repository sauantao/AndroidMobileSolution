/********************************************************************************
** Form generated from reading UI file 'AdbWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADBWIDGET_H
#define UI_ADBWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdbWidget
{
public:
    QListView *listView;
    QLabel *label_8;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *WIFI_MAC_lineEdit;
    QLineEdit *EthernetMAC_lineEdit;
    QLineEdit *ModuleName_lineEdit;
    QLineEdit *SerialNumber_lineEdit;
    QLineEdit *Android_Version_lineEdit;
    QLineEdit *Resolution_lineEdit;
    QLineEdit *ICType_lineEdit;
    QProgressBar *progressBar;
    QProgressBar *progressBar_2;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_Model;
    QLineEdit *lineEdit_Imel1;
    QLineEdit *lineEdit_Imel2;
    QLineEdit *lineEdit_Emmc;
    QLineEdit *lineEdit_Region;
    QLineEdit *lineEdit_product_code;
    QLineEdit *lineEdit_sw_ver;
    QToolButton *toolButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_TurnOff_2;
    QToolButton *toolButton_TurnOff_3;
    QToolButton *toolButton_TurnOff_4;
    QToolButton *toolButton_TurnOff;
    QToolButton *toolButton_Reboot;
    QToolButton *toolButton_2;

    void setupUi(QWidget *AdbWidget)
    {
        if (AdbWidget->objectName().isEmpty())
            AdbWidget->setObjectName(QStringLiteral("AdbWidget"));
        AdbWidget->resize(967, 540);
        listView = new QListView(AdbWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 10, 171, 511));
        listView->setStyleSheet(QStringLiteral(""));
        label_8 = new QLabel(AdbWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(830, 510, 91, 16));
        groupBox = new QGroupBox(AdbWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(680, 30, 241, 331));
        groupBox->setStyleSheet(QLatin1String("border-radius: 3px;\n"
"border: 1px solid grey;"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        WIFI_MAC_lineEdit = new QLineEdit(groupBox);
        WIFI_MAC_lineEdit->setObjectName(QStringLiteral("WIFI_MAC_lineEdit"));

        verticalLayout_2->addWidget(WIFI_MAC_lineEdit);

        EthernetMAC_lineEdit = new QLineEdit(groupBox);
        EthernetMAC_lineEdit->setObjectName(QStringLiteral("EthernetMAC_lineEdit"));

        verticalLayout_2->addWidget(EthernetMAC_lineEdit);

        ModuleName_lineEdit = new QLineEdit(groupBox);
        ModuleName_lineEdit->setObjectName(QStringLiteral("ModuleName_lineEdit"));

        verticalLayout_2->addWidget(ModuleName_lineEdit);

        SerialNumber_lineEdit = new QLineEdit(groupBox);
        SerialNumber_lineEdit->setObjectName(QStringLiteral("SerialNumber_lineEdit"));

        verticalLayout_2->addWidget(SerialNumber_lineEdit);

        Android_Version_lineEdit = new QLineEdit(groupBox);
        Android_Version_lineEdit->setObjectName(QStringLiteral("Android_Version_lineEdit"));

        verticalLayout_2->addWidget(Android_Version_lineEdit);

        Resolution_lineEdit = new QLineEdit(groupBox);
        Resolution_lineEdit->setObjectName(QStringLiteral("Resolution_lineEdit"));

        verticalLayout_2->addWidget(Resolution_lineEdit);

        ICType_lineEdit = new QLineEdit(groupBox);
        ICType_lineEdit->setObjectName(QStringLiteral("ICType_lineEdit"));

        verticalLayout_2->addWidget(ICType_lineEdit);


        horizontalLayout_3->addLayout(verticalLayout_2);

        progressBar = new QProgressBar(AdbWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(420, 400, 221, 10));
        progressBar->setMinimumSize(QSize(0, 10));
        progressBar->setMaximumSize(QSize(16777215, 11));
        progressBar->setStyleSheet(QStringLiteral(""));
        progressBar->setValue(50);
        progressBar->setTextVisible(false);
        progressBar_2 = new QProgressBar(AdbWidget);
        progressBar_2->setObjectName(QStringLiteral("progressBar_2"));
        progressBar_2->setGeometry(QRect(730, 400, 201, 11));
        progressBar_2->setMinimumSize(QSize(0, 10));
        progressBar_2->setMaximumSize(QSize(16777215, 11));
        progressBar_2->setStyleSheet(QLatin1String("border-radius: 0px;\n"
"border: 1px solid grey;\n"
"background-color: #05B8CC;\n"
"background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #ffff00,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );"));
        progressBar_2->setValue(24);
        progressBar_2->setTextVisible(false);
        groupBox_2 = new QGroupBox(AdbWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(420, 20, 251, 341));
        groupBox_2->setStyleSheet(QLatin1String("border-radius: 3px;\n"
"border: 1px solid grey;"));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 76, 321));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_4->addWidget(label_9);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_4->addWidget(label_10);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_4->addWidget(label_11);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_4->addWidget(label_12);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_4->addWidget(label_13);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_4->addWidget(label_14);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_4->addWidget(label_15);

        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(100, 10, 135, 321));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_Model = new QLineEdit(layoutWidget1);
        lineEdit_Model->setObjectName(QStringLiteral("lineEdit_Model"));

        verticalLayout->addWidget(lineEdit_Model);

        lineEdit_Imel1 = new QLineEdit(layoutWidget1);
        lineEdit_Imel1->setObjectName(QStringLiteral("lineEdit_Imel1"));

        verticalLayout->addWidget(lineEdit_Imel1);

        lineEdit_Imel2 = new QLineEdit(layoutWidget1);
        lineEdit_Imel2->setObjectName(QStringLiteral("lineEdit_Imel2"));

        verticalLayout->addWidget(lineEdit_Imel2);

        lineEdit_Emmc = new QLineEdit(layoutWidget1);
        lineEdit_Emmc->setObjectName(QStringLiteral("lineEdit_Emmc"));

        verticalLayout->addWidget(lineEdit_Emmc);

        lineEdit_Region = new QLineEdit(layoutWidget1);
        lineEdit_Region->setObjectName(QStringLiteral("lineEdit_Region"));

        verticalLayout->addWidget(lineEdit_Region);

        lineEdit_product_code = new QLineEdit(layoutWidget1);
        lineEdit_product_code->setObjectName(QStringLiteral("lineEdit_product_code"));

        verticalLayout->addWidget(lineEdit_product_code);

        lineEdit_sw_ver = new QLineEdit(layoutWidget1);
        lineEdit_sw_ver->setObjectName(QStringLiteral("lineEdit_sw_ver"));

        verticalLayout->addWidget(lineEdit_sw_ver);

        toolButton = new QToolButton(AdbWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(-210, 250, 25, 19));
        widget = new QWidget(AdbWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(230, 450, 711, 66));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        toolButton_TurnOff_2 = new QToolButton(widget);
        toolButton_TurnOff_2->setObjectName(QStringLiteral("toolButton_TurnOff_2"));
        toolButton_TurnOff_2->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_2->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_2->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-power_red_69071.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_2->setIcon(icon);
        toolButton_TurnOff_2->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(toolButton_TurnOff_2);

        toolButton_TurnOff_3 = new QToolButton(widget);
        toolButton_TurnOff_3->setObjectName(QStringLiteral("toolButton_TurnOff_3"));
        toolButton_TurnOff_3->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_3->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_3->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-cross_red_69065.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_3->setIcon(icon1);
        toolButton_TurnOff_3->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(toolButton_TurnOff_3);

        toolButton_TurnOff_4 = new QToolButton(widget);
        toolButton_TurnOff_4->setObjectName(QStringLiteral("toolButton_TurnOff_4"));
        toolButton_TurnOff_4->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_4->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_4->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-check_blue_68680.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_4->setIcon(icon2);
        toolButton_TurnOff_4->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(toolButton_TurnOff_4);

        toolButton_TurnOff = new QToolButton(widget);
        toolButton_TurnOff->setObjectName(QStringLiteral("toolButton_TurnOff"));
        toolButton_TurnOff->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ImageButton/image/Button/checl.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff->setIcon(icon3);
        toolButton_TurnOff->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(toolButton_TurnOff);

        toolButton_Reboot = new QToolButton(widget);
        toolButton_Reboot->setObjectName(QStringLiteral("toolButton_Reboot"));
        toolButton_Reboot->setMaximumSize(QSize(64, 64));
        toolButton_Reboot->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ImageButton/image/Button/reboot.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Reboot->setIcon(icon4);
        toolButton_Reboot->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(toolButton_Reboot);

        toolButton_2 = new QToolButton(widget);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setMaximumSize(QSize(64, 64));
        toolButton_2->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/ImageButton/image/Button/power.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon5);
        toolButton_2->setIconSize(QSize(64, 64));
        toolButton_2->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout->addWidget(toolButton_2);


        retranslateUi(AdbWidget);

        QMetaObject::connectSlotsByName(AdbWidget);
    } // setupUi

    void retranslateUi(QWidget *AdbWidget)
    {
        AdbWidget->setWindowTitle(QApplication::translate("AdbWidget", "Form", 0));
        label_8->setText(QApplication::translate("AdbWidget", "Turn Off iDevice", 0));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("AdbWidget", "MAC WIFI", 0));
        label_2->setText(QApplication::translate("AdbWidget", "EthernetMAC", 0));
        label_3->setText(QApplication::translate("AdbWidget", "ModuleName", 0));
        label_4->setText(QApplication::translate("AdbWidget", "SerialNumber", 0));
        label_5->setText(QApplication::translate("AdbWidget", "Android_Version", 0));
        label_6->setText(QApplication::translate("AdbWidget", "Resolution", 0));
        label_7->setText(QApplication::translate("AdbWidget", "ICType", 0));
        groupBox_2->setTitle(QString());
        label_9->setText(QApplication::translate("AdbWidget", "Model", 0));
        label_10->setText(QApplication::translate("AdbWidget", "Imel 1", 0));
        label_11->setText(QApplication::translate("AdbWidget", "Imel 2", 0));
        label_12->setText(QApplication::translate("AdbWidget", "Emmc", 0));
        label_13->setText(QApplication::translate("AdbWidget", "region", 0));
        label_14->setText(QApplication::translate("AdbWidget", "product_code", 0));
        label_15->setText(QApplication::translate("AdbWidget", "sw_ver", 0));
        toolButton->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_TurnOff_2->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_TurnOff_3->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_TurnOff_4->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_TurnOff->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_Reboot->setText(QApplication::translate("AdbWidget", "...", 0));
        toolButton_2->setText(QApplication::translate("AdbWidget", "T\341\272\257t m\303\241y", 0));
    } // retranslateUi

};

namespace Ui {
    class AdbWidget: public Ui_AdbWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADBWIDGET_H
