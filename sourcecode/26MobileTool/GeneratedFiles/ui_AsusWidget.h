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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsusWidget
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
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
        verticalLayout_6 = new QVBoxLayout(AsusWidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_fwdnx = new QLabel(AsusWidget);
        label_fwdnx->setObjectName(QStringLiteral("label_fwdnx"));

        verticalLayout_2->addWidget(label_fwdnx);

        label_fwimage = new QLabel(AsusWidget);
        label_fwimage->setObjectName(QStringLiteral("label_fwimage"));

        verticalLayout_2->addWidget(label_fwimage);

        label_osdnx = new QLabel(AsusWidget);
        label_osdnx->setObjectName(QStringLiteral("label_osdnx"));

        verticalLayout_2->addWidget(label_osdnx);

        label_osimage = new QLabel(AsusWidget);
        label_osimage->setObjectName(QStringLiteral("label_osimage"));

        verticalLayout_2->addWidget(label_osimage);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit_fwdnx = new QLineEdit(AsusWidget);
        lineEdit_fwdnx->setObjectName(QStringLiteral("lineEdit_fwdnx"));

        verticalLayout->addWidget(lineEdit_fwdnx);

        lineEdit_fwimage = new QLineEdit(AsusWidget);
        lineEdit_fwimage->setObjectName(QStringLiteral("lineEdit_fwimage"));

        verticalLayout->addWidget(lineEdit_fwimage);

        lineEdit_osdnx = new QLineEdit(AsusWidget);
        lineEdit_osdnx->setObjectName(QStringLiteral("lineEdit_osdnx"));

        verticalLayout->addWidget(lineEdit_osdnx);

        lineEdit_osimage = new QLineEdit(AsusWidget);
        lineEdit_osimage->setObjectName(QStringLiteral("lineEdit_osimage"));

        verticalLayout->addWidget(lineEdit_osimage);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        pushButton_fwdnx = new QPushButton(AsusWidget);
        pushButton_fwdnx->setObjectName(QStringLiteral("pushButton_fwdnx"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AsusWidget/image/Button/Add_folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_fwdnx->setIcon(icon);
        pushButton_fwdnx->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_fwdnx);

        pushButton_fwimage = new QPushButton(AsusWidget);
        pushButton_fwimage->setObjectName(QStringLiteral("pushButton_fwimage"));
        pushButton_fwimage->setIcon(icon);
        pushButton_fwimage->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_fwimage);

        pushButton_osdnx = new QPushButton(AsusWidget);
        pushButton_osdnx->setObjectName(QStringLiteral("pushButton_osdnx"));
        pushButton_osdnx->setIcon(icon);
        pushButton_osdnx->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_osdnx);

        pushButton_osimage = new QPushButton(AsusWidget);
        pushButton_osimage->setObjectName(QStringLiteral("pushButton_osimage"));
        pushButton_osimage->setIcon(icon);
        pushButton_osimage->setIconSize(QSize(24, 24));

        verticalLayout_3->addWidget(pushButton_osimage);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout);

        plainTextEdit = new QPlainTextEdit(AsusWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout_5->addWidget(plainTextEdit);

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


        verticalLayout_5->addWidget(groupBox_Button);


        verticalLayout_6->addLayout(verticalLayout_5);


        retranslateUi(AsusWidget);

        QMetaObject::connectSlotsByName(AsusWidget);
    } // setupUi

    void retranslateUi(QWidget *AsusWidget)
    {
        AsusWidget->setWindowTitle(QApplication::translate("AsusWidget", "Form", 0));
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
