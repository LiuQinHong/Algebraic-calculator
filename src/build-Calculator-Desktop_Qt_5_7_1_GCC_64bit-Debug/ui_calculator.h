/********************************************************************************
** Form generated from reading UI file 'calculator.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATOR_H
#define UI_CALCULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calculator
{
public:
    QLabel *label_name;
    QTextEdit *textEdit_display;
    QLineEdit *lineEdit_input;
    QLabel *label_info;
    QPushButton *pushButton_equal;
    QPushButton *pushButton_del;

    void setupUi(QWidget *Calculator)
    {
        if (Calculator->objectName().isEmpty())
            Calculator->setObjectName(QStringLiteral("Calculator"));
        Calculator->resize(1024, 768);
        label_name = new QLabel(Calculator);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(30, 10, 930, 42));
        label_name->setMinimumSize(QSize(930, 42));
        QFont font;
        font.setPointSize(26);
        label_name->setFont(font);
        textEdit_display = new QTextEdit(Calculator);
        textEdit_display->setObjectName(QStringLiteral("textEdit_display"));
        textEdit_display->setGeometry(QRect(30, 70, 930, 470));
        textEdit_display->setMinimumSize(QSize(930, 470));
        textEdit_display->setSizeIncrement(QSize(0, 0));
        lineEdit_input = new QLineEdit(Calculator);
        lineEdit_input->setObjectName(QStringLiteral("lineEdit_input"));
        lineEdit_input->setGeometry(QRect(30, 600, 751, 30));
        label_info = new QLabel(Calculator);
        label_info->setObjectName(QStringLiteral("label_info"));
        label_info->setGeometry(QRect(30, 550, 930, 33));
        label_info->setMinimumSize(QSize(930, 33));
        QFont font1;
        font1.setPointSize(20);
        label_info->setFont(font1);
        pushButton_equal = new QPushButton(Calculator);
        pushButton_equal->setObjectName(QStringLiteral("pushButton_equal"));
        pushButton_equal->setGeometry(QRect(790, 600, 80, 30));
        pushButton_del = new QPushButton(Calculator);
        pushButton_del->setObjectName(QStringLiteral("pushButton_del"));
        pushButton_del->setGeometry(QRect(880, 600, 80, 30));

        retranslateUi(Calculator);

        QMetaObject::connectSlotsByName(Calculator);
    } // setupUi

    void retranslateUi(QWidget *Calculator)
    {
        Calculator->setWindowTitle(QApplication::translate("Calculator", "Calculator", Q_NULLPTR));
        label_name->setText(QApplication::translate("Calculator", "AL-Calculator", Q_NULLPTR));
        label_info->setText(QApplication::translate("Calculator", "Please input Algebraic expression:", Q_NULLPTR));
        pushButton_equal->setText(QApplication::translate("Calculator", "=", Q_NULLPTR));
        pushButton_del->setText(QApplication::translate("Calculator", "Del", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Calculator: public Ui_Calculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATOR_H
