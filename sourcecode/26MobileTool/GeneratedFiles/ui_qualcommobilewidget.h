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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QualComMobileWidget
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_ListCom;
    QPushButton *pushButton_Com_Reload;
    QPushButton *pushButton_Com_Connec;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_QcOnly;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox_BootSelect;
    QPushButton *pushButton_BootSelect;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox_AutoBoot;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *toolButton_2;
    QToolButton *toolButton_TurnOff_4;
    QToolButton *toolButton_TurnOff_3;
    QToolButton *toolButton_TurnOff;
    QToolButton *toolButton_Reboot;
    QToolButton *toolButton_TurnOff_2;

    void setupUi(QWidget *QualComMobileWidget)
    {
        if (QualComMobileWidget->objectName().isEmpty())
            QualComMobileWidget->setObjectName(QStringLiteral("QualComMobileWidget"));
        QualComMobileWidget->resize(704, 593);
        horizontalLayout_6 = new QHBoxLayout(QualComMobileWidget);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
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
        comboBox_ListCom->setMinimumSize(QSize(500, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        comboBox_ListCom->setFont(font1);

        horizontalLayout->addWidget(comboBox_ListCom);

        pushButton_Com_Reload = new QPushButton(groupBox);
        pushButton_Com_Reload->setObjectName(QStringLiteral("pushButton_Com_Reload"));
        pushButton_Com_Reload->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Com_Reload);

        pushButton_Com_Connec = new QPushButton(groupBox);
        pushButton_Com_Connec->setObjectName(QStringLiteral("pushButton_Com_Connec"));
        pushButton_Com_Connec->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Com_Connec);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        checkBox_QcOnly = new QCheckBox(groupBox);
        checkBox_QcOnly->setObjectName(QStringLiteral("checkBox_QcOnly"));

        horizontalLayout_2->addWidget(checkBox_QcOnly);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(QualComMobileWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        comboBox_BootSelect = new QComboBox(groupBox_2);
        comboBox_BootSelect->setObjectName(QStringLiteral("comboBox_BootSelect"));
        QFont font2;
        font2.setFamily(QStringLiteral("Consolas"));
        font2.setPointSize(10);
        comboBox_BootSelect->setFont(font2);

        horizontalLayout_3->addWidget(comboBox_BootSelect);

        pushButton_BootSelect = new QPushButton(groupBox_2);
        pushButton_BootSelect->setObjectName(QStringLiteral("pushButton_BootSelect"));
        pushButton_BootSelect->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(pushButton_BootSelect);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        checkBox_AutoBoot = new QCheckBox(groupBox_2);
        checkBox_AutoBoot->setObjectName(QStringLiteral("checkBox_AutoBoot"));

        horizontalLayout_4->addWidget(checkBox_AutoBoot);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_4->addWidget(groupBox_2);

        plainTextEdit = new QPlainTextEdit(QualComMobileWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setFont(font);

        verticalLayout_4->addWidget(plainTextEdit);

        groupBox_3 = new QGroupBox(QualComMobileWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        toolButton_2 = new QToolButton(groupBox_3);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setMaximumSize(QSize(64, 64));
        toolButton_2->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ImageButton/image/Button/power.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon);
        toolButton_2->setIconSize(QSize(64, 64));
        toolButton_2->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout_5->addWidget(toolButton_2);

        toolButton_TurnOff_4 = new QToolButton(groupBox_3);
        toolButton_TurnOff_4->setObjectName(QStringLiteral("toolButton_TurnOff_4"));
        toolButton_TurnOff_4->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_4->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_4->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-check_blue_68680.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_4->setIcon(icon1);
        toolButton_TurnOff_4->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_4);

        toolButton_TurnOff_3 = new QToolButton(groupBox_3);
        toolButton_TurnOff_3->setObjectName(QStringLiteral("toolButton_TurnOff_3"));
        toolButton_TurnOff_3->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_3->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_3->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-cross_red_69065.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_3->setIcon(icon2);
        toolButton_TurnOff_3->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_3);

        toolButton_TurnOff = new QToolButton(groupBox_3);
        toolButton_TurnOff->setObjectName(QStringLiteral("toolButton_TurnOff"));
        toolButton_TurnOff->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/ImageButton/image/Button/checl.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff->setIcon(icon3);
        toolButton_TurnOff->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff);

        toolButton_Reboot = new QToolButton(groupBox_3);
        toolButton_Reboot->setObjectName(QStringLiteral("toolButton_Reboot"));
        toolButton_Reboot->setMaximumSize(QSize(64, 64));
        toolButton_Reboot->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/ImageButton/image/Button/reboot.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Reboot->setIcon(icon4);
        toolButton_Reboot->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_Reboot);

        toolButton_TurnOff_2 = new QToolButton(groupBox_3);
        toolButton_TurnOff_2->setObjectName(QStringLiteral("toolButton_TurnOff_2"));
        toolButton_TurnOff_2->setMinimumSize(QSize(64, 64));
        toolButton_TurnOff_2->setMaximumSize(QSize(64, 64));
        toolButton_TurnOff_2->setStyleSheet(QStringLiteral("background: transparent; border: none;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/ImageButton/image/Button/if_button-power_red_69071.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_TurnOff_2->setIcon(icon5);
        toolButton_TurnOff_2->setIconSize(QSize(64, 64));

        horizontalLayout_5->addWidget(toolButton_TurnOff_2);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_4->addWidget(groupBox_3);


        horizontalLayout_6->addLayout(verticalLayout_4);


        retranslateUi(QualComMobileWidget);

        QMetaObject::connectSlotsByName(QualComMobileWidget);
    } // setupUi

    void retranslateUi(QWidget *QualComMobileWidget)
    {
        QualComMobileWidget->setWindowTitle(QApplication::translate("QualComMobileWidget", "Form", 0));
        groupBox->setTitle(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n COM", 0));
        pushButton_Com_Reload->setText(QApplication::translate("QualComMobileWidget", "L\303\240m M\341\273\233i", 0));
        pushButton_Com_Connec->setText(QApplication::translate("QualComMobileWidget", "K\341\272\277t N\341\273\221i", 0));
        checkBox_QcOnly->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\211 hi\341\273\203n th\341\273\213 k\341\272\277t n\341\273\221i qualcom", 0));
        groupBox_2->setTitle(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n boot", 0));
        pushButton_BootSelect->setText(QApplication::translate("QualComMobileWidget", "Ch\341\273\215n file", 0));
        checkBox_AutoBoot->setText(QApplication::translate("QualComMobileWidget", "T\341\273\261 \304\221\341\273\231ng ch\341\273\215n boot", 0));
        groupBox_3->setTitle(QString());
        toolButton_2->setText(QApplication::translate("QualComMobileWidget", "T\341\272\257t m\303\241y", 0));
        toolButton_TurnOff_4->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff_3->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_Reboot->setText(QApplication::translate("QualComMobileWidget", "...", 0));
        toolButton_TurnOff_2->setText(QApplication::translate("QualComMobileWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class QualComMobileWidget: public Ui_QualComMobileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUALCOMMOBILEWIDGET_H
