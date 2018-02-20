/********************************************************************************
** Form generated from reading UI file 'CmdWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMDWIDGET_H
#define UI_CMDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CmdWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Execute;
    QPushButton *pushButton_Stop;

    void setupUi(QWidget *CmdWidget)
    {
        if (CmdWidget->objectName().isEmpty())
            CmdWidget->setObjectName(QStringLiteral("CmdWidget"));
        CmdWidget->resize(870, 549);
        horizontalLayout_3 = new QHBoxLayout(CmdWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        textEdit = new QTextEdit(CmdWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setMinimumSize(QSize(0, 450));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        textEdit->setFont(font);
        textEdit->setFrameShape(QFrame::StyledPanel);
        textEdit->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(textEdit);

        groupBox = new QGroupBox(CmdWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(400, 0));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        font1.setPointSize(10);
        comboBox->setFont(font1);
        comboBox->setEditable(true);

        verticalLayout->addWidget(comboBox);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_Execute = new QPushButton(groupBox);
        pushButton_Execute->setObjectName(QStringLiteral("pushButton_Execute"));
        pushButton_Execute->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Execute);

        pushButton_Stop = new QPushButton(groupBox);
        pushButton_Stop->setObjectName(QStringLiteral("pushButton_Stop"));
        pushButton_Stop->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(pushButton_Stop);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox);


        horizontalLayout_3->addLayout(verticalLayout_3);


        retranslateUi(CmdWidget);

        QMetaObject::connectSlotsByName(CmdWidget);
    } // setupUi

    void retranslateUi(QWidget *CmdWidget)
    {
        CmdWidget->setWindowTitle(QApplication::translate("CmdWidget", "Form", 0));
        groupBox->setTitle(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("CmdWidget", "dir", 0)
         << QApplication::translate("CmdWidget", "adb shell getprop", 0)
         << QApplication::translate("CmdWidget", "adb shell pm list packages", 0)
         << QApplication::translate("CmdWidget", "adb", 0)
        );
        pushButton_Execute->setText(QApplication::translate("CmdWidget", "Execute", 0));
        pushButton_Stop->setText(QApplication::translate("CmdWidget", "Stop", 0));
    } // retranslateUi

};

namespace Ui {
    class CmdWidget: public Ui_CmdWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMDWIDGET_H
