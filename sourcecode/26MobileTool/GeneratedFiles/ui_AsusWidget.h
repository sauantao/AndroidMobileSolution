/********************************************************************************
** Form generated from reading UI file 'AsusWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASUSWIDGET_H
#define UI_ASUSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsusWidget
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_fwdnx;
    QLabel *label_fwimage;
    QLabel *label_osdnx;
    QLabel *label_osimage;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_fwdnx;
    QLineEdit *lineEdit_fwimage;
    QLineEdit *lineEdit_osdnx;
    QLineEdit *lineEdit_osimage;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_fwdnx;
    QPushButton *pushButton_fwimage;
    QPushButton *pushButton_osdnx;
    QPushButton *pushButton_osimage;
    QPlainTextEdit *plainTextEdit;
    QGroupBox *groupBox_Button;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Start;
    QPushButton *pushButton_Stop;

    void setupUi(QWidget *AsusWidget)
    {
        if (AsusWidget->objectName().isEmpty())
            AsusWidget->setObjectName(QStringLiteral("AsusWidget"));
        AsusWidget->resize(843, 518);
        horizontalLayout_4 = new QHBoxLayout(AsusWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        groupBox_2 = new QGroupBox(AsusWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout_3->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout_3->addWidget(radioButton_2);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_3->addWidget(comboBox);

        pushButton = new QPushButton(groupBox_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_7->addWidget(groupBox_2);

        groupBox = new QGroupBox(AsusWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_fwdnx = new QLabel(groupBox);
        label_fwdnx->setObjectName(QStringLiteral("label_fwdnx"));

        verticalLayout_2->addWidget(label_fwdnx);

        label_fwimage = new QLabel(groupBox);
        label_fwimage->setObjectName(QStringLiteral("label_fwimage"));

        verticalLayout_2->addWidget(label_fwimage);

        label_osdnx = new QLabel(groupBox);
        label_osdnx->setObjectName(QStringLiteral("label_osdnx"));

        verticalLayout_2->addWidget(label_osdnx);

        label_osimage = new QLabel(groupBox);
        label_osimage->setObjectName(QStringLiteral("label_osimage"));

        verticalLayout_2->addWidget(label_osimage);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit_fwdnx = new QLineEdit(groupBox);
        lineEdit_fwdnx->setObjectName(QStringLiteral("lineEdit_fwdnx"));

        verticalLayout->addWidget(lineEdit_fwdnx);

        lineEdit_fwimage = new QLineEdit(groupBox);
        lineEdit_fwimage->setObjectName(QStringLiteral("lineEdit_fwimage"));

        verticalLayout->addWidget(lineEdit_fwimage);

        lineEdit_osdnx = new QLineEdit(groupBox);
        lineEdit_osdnx->setObjectName(QStringLiteral("lineEdit_osdnx"));

        verticalLayout->addWidget(lineEdit_osdnx);

        lineEdit_osimage = new QLineEdit(groupBox);
        lineEdit_osimage->setObjectName(QStringLiteral("lineEdit_osimage"));

        verticalLayout->addWidget(lineEdit_osimage);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_fwdnx = new QPushButton(groupBox);
        pushButton_fwdnx->setObjectName(QStringLiteral("pushButton_fwdnx"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AsusWidget/image/Button/Add_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_fwdnx->setIcon(icon);
        pushButton_fwdnx->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_fwdnx);

        pushButton_fwimage = new QPushButton(groupBox);
        pushButton_fwimage->setObjectName(QStringLiteral("pushButton_fwimage"));
        pushButton_fwimage->setIcon(icon);
        pushButton_fwimage->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_fwimage);

        pushButton_osdnx = new QPushButton(groupBox);
        pushButton_osdnx->setObjectName(QStringLiteral("pushButton_osdnx"));
        pushButton_osdnx->setIcon(icon);
        pushButton_osdnx->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_osdnx);

        pushButton_osimage = new QPushButton(groupBox);
        pushButton_osimage->setObjectName(QStringLiteral("pushButton_osimage"));
        pushButton_osimage->setIcon(icon);
        pushButton_osimage->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_osimage);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_6->addLayout(horizontalLayout);


        verticalLayout_7->addWidget(groupBox);

        plainTextEdit = new QPlainTextEdit(AsusWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout_7->addWidget(plainTextEdit);

        groupBox_Button = new QGroupBox(AsusWidget);
        groupBox_Button->setObjectName(QStringLiteral("groupBox_Button"));
        verticalLayout_4 = new QVBoxLayout(groupBox_Button);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(528, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Start = new QPushButton(groupBox_Button);
        pushButton_Start->setObjectName(QStringLiteral("pushButton_Start"));

        horizontalLayout_2->addWidget(pushButton_Start);

        pushButton_Stop = new QPushButton(groupBox_Button);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));

        horizontalLayout_2->addWidget(pushButton_Stop);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_7->addWidget(groupBox_Button);


        horizontalLayout_4->addLayout(verticalLayout_7);


        retranslateUi(AsusWidget);

        QMetaObject::connectSlotsByName(AsusWidget);
    } // setupUi

    void retranslateUi(QWidget *AsusWidget)
    {
        AsusWidget->setWindowTitle(QApplication::translate("AsusWidget", "Form", 0));
        groupBox_2->setTitle(QApplication::translate("AsusWidget", "Option", 0));
        radioButton->setText(QApplication::translate("AsusWidget", "Auto ", 0));
        radioButton_2->setText(QApplication::translate("AsusWidget", "RadioButton", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("AsusWidget", "Zenfon 5", 0)
         << QApplication::translate("AsusWidget", "Zenfon 6", 0)
        );
        pushButton->setText(QApplication::translate("AsusWidget", "Ch\341\273\215n", 0));
        groupBox->setTitle(QApplication::translate("AsusWidget", "Ch\341\273\215n file", 0));
        label_fwdnx->setText(QApplication::translate("AsusWidget", "fwdnx ", 0));
        label_fwimage->setText(QApplication::translate("AsusWidget", "fwimage", 0));
        label_osdnx->setText(QApplication::translate("AsusWidget", "osdnx ", 0));
        label_osimage->setText(QApplication::translate("AsusWidget", "osimage", 0));
        pushButton_fwdnx->setText(QApplication::translate("AsusWidget", "Ch\341\273\215n file", 0));
        pushButton_fwimage->setText(QApplication::translate("AsusWidget", "Ch\341\273\215n file", 0));
        pushButton_osdnx->setText(QApplication::translate("AsusWidget", "Ch\341\273\215n File", 0));
        pushButton_osimage->setText(QApplication::translate("AsusWidget", "Ch\341\273\215n file", 0));
        groupBox_Button->setTitle(QString());
        pushButton_Start->setText(QApplication::translate("AsusWidget", "B\341\272\257t \304\221\341\272\247u", 0));
        pushButton_Stop->setText(QApplication::translate("AsusWidget", "H\341\273\247y", 0));
    } // retranslateUi

};

namespace Ui {
    class AsusWidget: public Ui_AsusWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASUSWIDGET_H
