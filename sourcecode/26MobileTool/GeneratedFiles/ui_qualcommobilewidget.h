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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QualComMobileWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_ListCom;
    QPushButton *pushButton_Com_Reload;
    QPushButton *pushButton_Com_Connec;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_QcOnly;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *QualComMobileWidget)
    {
        if (QualComMobileWidget->objectName().isEmpty())
            QualComMobileWidget->setObjectName(QStringLiteral("QualComMobileWidget"));
        QualComMobileWidget->resize(886, 593);
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        QualComMobileWidget->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(QualComMobileWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(QualComMobileWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        groupBox->setFont(font1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox_ListCom = new QComboBox(groupBox);
        comboBox_ListCom->setObjectName(QStringLiteral("comboBox_ListCom"));
        comboBox_ListCom->setMinimumSize(QSize(500, 0));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        comboBox_ListCom->setFont(font2);

        horizontalLayout->addWidget(comboBox_ListCom);

        pushButton_Com_Reload = new QPushButton(groupBox);
        pushButton_Com_Reload->setObjectName(QStringLiteral("pushButton_Com_Reload"));

        horizontalLayout->addWidget(pushButton_Com_Reload);

        pushButton_Com_Connec = new QPushButton(groupBox);
        pushButton_Com_Connec->setObjectName(QStringLiteral("pushButton_Com_Connec"));

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


        verticalLayout_2->addWidget(groupBox);

        plainTextEdit = new QPlainTextEdit(QualComMobileWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setFont(font1);

        verticalLayout_2->addWidget(plainTextEdit);


        horizontalLayout_3->addLayout(verticalLayout_2);


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
    } // retranslateUi

};

namespace Ui {
    class QualComMobileWidget: public Ui_QualComMobileWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUALCOMMOBILEWIDGET_H
