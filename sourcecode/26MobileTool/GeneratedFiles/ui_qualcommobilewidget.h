/********************************************************************************
** Form generated from reading UI file 'qualcommobilewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUALCOMMOBILEWIDGET_H
#define UI_QUALCOMMOBILEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QualComMobileWidget
{
public:
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_Option;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_ReadInfo;
    QRadioButton *radioButton_Flash;
    QRadioButton *radioButton_FormatErase;
    QRadioButton *radioButton_Readback;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *checkBox_QcOnly;
    QCheckBox *checkBox_AutoBoot;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_ListCom;
    QPushButton *pushButton_Com_Reload;
    QPushButton *pushButton_Com_Connec;
    QGroupBox *groupBox_BootSelect;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox_BootSelect;
    QPushButton *pushButton_BootSelect;
    QGroupBox *groupBox_RomSelect;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *lineEdit_FolderRom;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_RawProgramXml;
    QLineEdit *lineEdit_PatchXml;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_RomBootFolder;
    QPushButton *pushButton_RawXmlPatchXml;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *toolButton_TurnOff_4;
    QToolButton *toolButton_TurnOff_3;
    QToolButton *toolButton_TurnOff;
    QToolButton *toolButton_Reboot;
    QToolButton *toolButton_TurnOff_2;
    QToolButton *toolButton_Start;

    void setupUi(QWidget *QualComMobileWidget)
    {
        if (QualComMobileWidget->objectName().isEmpty())
            QualComMobileWidget->setObjectName(QStringLiteral("QualComMobileWidget"));
        QualComMobileWidget->resize(704, 593);
        horizontalLayout_8 = new QHBoxLayout(QualComMobileWidget);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        groupBox_Option = new QGroupBox(QualComMobileWidget);
        groupBox_Option->setObjectName(QStringLiteral("groupBox_Option"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_Option);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton_ReadInfo = new QRadioButton(groupBox_Option);
        radioButton_ReadInfo->setObjectName(QStringLiteral("radioButton_ReadInfo"));

        horizontalLayout_2->addWidget(radioButton_ReadInfo);

        radioButton_Flash = new QRadioButton(groupBox_Option);
        radioButton_Flash->setObjectName(QStringLiteral("radioButton_Flash"));

        horizontalLayout_2->addWidget(radioButton_Flash);

        radioButton_FormatErase = new QRadioButton(groupBox_Option);
        radioButton_FormatErase->setObjectName(QStringLiteral("radioButton_FormatErase"));

        horizontalLayout_2->addWidget(radioButton_FormatErase);

        radioButton_Readback = new QRadioButton(groupBox_Option);
        radioButton_Readback->setObjectName(QStringLiteral("radioButton_Readback"));

        horizontalLayout_2->addWidget(radioButton_Readback);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        checkBox_QcOnly = new QCheckBox(groupBox_Option);
        checkBox_QcOnly->setObjectName(QStringLiteral("checkBox_QcOnly"));

        verticalLayout_7->addWidget(checkBox_QcOnly);

        checkBox_AutoBoot = new QCheckBox(groupBox_Option);
        checkBox_AutoBoot->setObjectName(QStringLiteral("checkBox_AutoBoot"));

        verticalLayout_7->addWidget(checkBox_AutoBoot);


        horizontalLayout_4->addLayout(verticalLayout_7);


        verticalLayout_8->addWidget(groupBox_Option);

        groupBox = new QGroupBox(QualComMobileWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox_ListCom = new QComboBox(groupBox);
        comboBox_ListCom->setObjectName(QStringLiteral("comboBox_ListCom"));
        comboBox_ListCom->setMinimumSize(QSize(400, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        comboBox_ListCom->setFont(font1);

        horizontalLayout->addWidget(comboBox_ListCom);

        pushButton_Com_Reload = new QPushButton(groupBox);
        pushButton_Com_Reload->setObjectName(QStringLiteral("pushButton_Com_Reload"));
        pushButton_Com_Reload->setMinimumSize(QSize(100, 0));
        pushButton_Com_Reload->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Com_Reload);

        pushButton_Com_Connec = new QPushButton(groupBox);
        pushButton_Com_Connec->setObjectName(QStringLiteral("pushButton_Com_Connec"));
        pushButton_Com_Connec->setMinimumSize(QSize(100, 0));
        pushButton_Com_Connec->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Com_Connec);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_8->addWidget(groupBox);

        groupBox_BootSelect = new QGroupBox(QualComMobileWidget);
        groupBox_BootSelect->setObjectName(QStringLiteral("groupBox_BootSelect"));
        verticalLayout_2 = new QVBoxLayout(groupBox_BootSelect);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox_BootSelect = new QComboBox(groupBox_BootSelect);
        comboBox_BootSelect->setObjectName(QStringLiteral("comboBox_BootSelect"));
        QFont font2;
        font2.setFamily(QStringLiteral("Consolas"));
        font2.setPointSize(10);
        comboBox_BootSelect->setFont(font2);

        horizontalLayout_3->addWidget(comboBox_BootSelect);

        pushButton_BootSelect = new QPushButton(groupBox_BootSelect);
        pushButton_BootSelect->setObjectName(QStringLiteral("pushButton_BootSelect"));
        pushButton_BootSelect->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(pushButton_BootSelect);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_8->addWidget(groupBox_BootSelect);

        groupBox_RomSelect = new QGroupBox(QualComMobileWidget);
        groupBox_RomSelect->setObjectName(QStringLiteral("groupBox_RomSelect"));
        verticalLayout_6 = new QVBoxLayout(groupBox_RomSelect);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        lineEdit_FolderRom = new QLineEdit(groupBox_RomSelect);
        lineEdit_FolderRom->setObjectName(QStringLiteral("lineEdit_FolderRom"));

        verticalLayout_5->addWidget(lineEdit_FolderRom);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_RawProgramXml = new QLineEdit(groupBox_RomSelect);
        lineEdit_RawProgramXml->setObjectName(QStringLiteral("lineEdit_RawProgramXml"));

        horizontalLayout_6->addWidget(lineEdit_RawProgramXml);

        lineEdit_PatchXml = new QLineEdit(groupBox_RomSelect);
        lineEdit_PatchXml->setObjectName(QStringLiteral("lineEdit_PatchXml"));

        horizontalLayout_6->addWidget(lineEdit_PatchXml);


        verticalLayout_5->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_RomBootFolder = new QPushButton(groupBox_RomSelect);
        pushButton_RomBootFolder->setObjectName(QStringLiteral("pushButton_RomBootFolder"));
        pushButton_RomBootFolder->setMinimumSize(QSize(100, 0));

        verticalLayout_4->addWidget(pushButton_RomBootFolder);

        pushButton_RawXmlPatchXml = new QPushButton(groupBox_RomSelect);
        pushButton_RawXmlPatchXml->setObjectName(QStringLiteral("pushButton_RawXmlPatchXml"));
        pushButton_RawXmlPatchXml->setMinimumSize(QSize(100, 0));

        verticalLayout_4->addWidget(pushButton_RawXmlPatchXml);


        horizontalLayout_7->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(horizontalLayout_7);


        verticalLayout_8->addWidget(groupBox_RomSelect);

        plainTextEdit = new QPlainTextEdit(QualComMobileWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setFont(font);

        verticalLayout_8->addWidget(plainTextEdit);

        groupBox_3 = new QGroupBox(QualComMobileWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        toolButton_TurnOff_4 = new QToolButton(groupBox_3);
        toolButton_TurnOff_4->setObjectName(QStringLiteral("toolButton_TurnOff_4"));
        toolButton_TurnOff_4->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_4->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_4->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-check_blue_68680.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_4->setIcon(icon);
        toolButton_TurnOff_4->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_4);

        toolButton_TurnOff_3 = new QToolButton(groupBox_3);
        toolButton_TurnOff_3->setObjectName(QStringLiteral("toolButton_TurnOff_3"));
        toolButton_TurnOff_3->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_3->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_3->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-cross_red_69065.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_3->setIcon(icon1);
        toolButton_TurnOff_3->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_3);

        toolButton_TurnOff = new QToolButton(groupBox_3);
        toolButton_TurnOff->setObjectName(QStringLiteral("toolButton_TurnOff"));
        toolButton_TurnOff->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ImageButton/image/Button/checl.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff->setIcon(icon2);
        toolButton_TurnOff->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff);

        toolButton_Reboot = new QToolButton(groupBox_3);
        toolButton_Reboot->setObjectName(QStringLiteral("toolButton_Reboot"));
        toolButton_Reboot->setMaximumSize(QSize(64, 64));
        toolButton_Reboot->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ImageButton/image/Button/reboot.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Reboot->setIcon(icon3);
        toolButton_Reboot->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_Reboot);

        toolButton_TurnOff_2 = new QToolButton(groupBox_3);
        toolButton_TurnOff_2->setObjectName(QStringLiteral("toolButton_TurnOff_2"));
        toolButton_TurnOff_2->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_2->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_2->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-power_red_69071.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_2->setIcon(icon4);
        toolButton_TurnOff_2->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_2);

        toolButton_Start = new QToolButton(groupBox_3);
        toolButton_Start->setObjectName(QStringLiteral("toolButton_Start"));
        toolButton_Start->setMaximumSize(QSize(64, 64));
        toolButton_Start->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/ImageButton/image/Button/power.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Start->setIcon(icon5);
        toolButton_Start->setIconSize(QSize(64, 64));
        toolButton_Start->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton_Start->setAutoRaise(true);

        horizontalLayout_5->addWidget(toolButton_Start);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_8->addWidget(groupBox_3);


        horizontalLayout_8->addLayout(verticalLayout_8);


        retranslateUi(QualComMobileWidget);

        QMetaObject::connectSlotsByName(QualComMobileWidget);
    } // setupUi

    void retranslateUi(QWidget *QualComMobileWidget)
    {
        QualComMobileWidget->setWindowTitle(QApplication::translate("QualComMobileWidget", "Form", 0));
        groupBox_Option->setTitle(QApplication::translate("QualComMobileWidget", "Option", 0));
        radioButton_ReadInfo->setText(QApplication::translate("QualComMobileWidget", "InFo", 0));
        radioButton_Flash->setText(QApplication::translate("QualComMobileWidget", "Flash", 0));
        radioButton_FormatErase->setText(QApplication::translate("QualComMobileWidget", "Format/Erase", 0));
        radioButton_Readback->setText(QApplication::translate("QualComMobileWidget", "Readback", 0));
        checkBox_QcOnly->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\211 hi\341\273\203n th\341\273\213 k\341\272\277t n\341\273\221i qualcom", 0));
        checkBox_AutoBoot->setText(QApplication::translate("QualComMobileWidget", "T\341\273\261 \304\221\341\273\231ng ch\341\273\215n boot", 0));
        groupBox->setTitle(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n COM", 0));
        pushButton_Com_Reload->setText(QApplication::translate("QualComMobileWidget", "L\303\240m M\341\273\233i", 0));
        pushButton_Com_Connec->setText(QApplication::translate("QualComMobileWidget", "K\341\272\277t N\341\273\221i", 0));
        groupBox_BootSelect->setTitle(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n boot", 0));
        pushButton_BootSelect->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n file", 0));
        groupBox_RomSelect->setTitle(QApplication::translate("QualComMobileWidget", "Flash ", 0));
        pushButton_RomBootFolder->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n file", 0));
        pushButton_RawXmlPatchXml->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n file", 0));
        groupBox_3->setTitle(QString());
        toolButton_TurnOff_4->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff_3->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_Reboot->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff_2->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_Start->setText(QApplication::translate("QualComMobileWidget", "T\341\272\257t m\303\241y", 0));
    } // retranslateUi

};

namespace Ui {
    class QualComMobileWidget: public Ui_QualComMobileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUALCOMMOBILEWIDGET_H
