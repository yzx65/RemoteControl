/********************************************************************************
** Form generated from reading UI file 'logindatabasedlg.ui'
**
** Created: Wed May 20 21:08:16 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDATABASEDLG_H
#define UI_LOGINDATABASEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDatabaseDlg
{
public:
    QLineEdit *edtUserName;
    QLineEdit *edtPassword;
    QPushButton *btnLogin;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;

    void setupUi(QDialog *LoginDatabaseDlg)
    {
        if (LoginDatabaseDlg->objectName().isEmpty())
            LoginDatabaseDlg->setObjectName(QString::fromUtf8("LoginDatabaseDlg"));
        LoginDatabaseDlg->resize(292, 150);
        LoginDatabaseDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-size:14px;\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        edtUserName = new QLineEdit(LoginDatabaseDlg);
        edtUserName->setObjectName(QString::fromUtf8("edtUserName"));
        edtUserName->setGeometry(QRect(80, 20, 191, 25));
        edtPassword = new QLineEdit(LoginDatabaseDlg);
        edtPassword->setObjectName(QString::fromUtf8("edtPassword"));
        edtPassword->setGeometry(QRect(80, 60, 191, 25));
        edtPassword->setEchoMode(QLineEdit::Password);
        btnLogin = new QPushButton(LoginDatabaseDlg);
        btnLogin->setObjectName(QString::fromUtf8("btnLogin"));
        btnLogin->setGeometry(QRect(190, 110, 81, 31));
        label = new QLabel(LoginDatabaseDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 50, 25));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(LoginDatabaseDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 60, 50, 25));
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        frame = new QFrame(LoginDatabaseDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 90, 271, 16));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(LoginDatabaseDlg);

        QMetaObject::connectSlotsByName(LoginDatabaseDlg);
    } // setupUi

    void retranslateUi(QDialog *LoginDatabaseDlg)
    {
        LoginDatabaseDlg->setWindowTitle(QApplication::translate("LoginDatabaseDlg", "\350\277\236\346\216\245 SQL Server \346\225\260\346\215\256\345\272\223", 0, QApplication::UnicodeUTF8));
        edtUserName->setPlaceholderText(QString());
        edtPassword->setPlaceholderText(QString());
        btnLogin->setText(QApplication::translate("LoginDatabaseDlg", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LoginDatabaseDlg", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LoginDatabaseDlg", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginDatabaseDlg: public Ui_LoginDatabaseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDATABASEDLG_H
