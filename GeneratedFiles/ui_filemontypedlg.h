/********************************************************************************
** Form generated from reading UI file 'filemontypedlg.ui'
**
** Created: Thu Apr 2 16:13:20 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMONTYPEDLG_H
#define UI_FILEMONTYPEDLG_H

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

class Ui_FileMonTypeDlg
{
public:
    QLineEdit *edtExt;
    QPushButton *btnOk;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;

    void setupUi(QDialog *FileMonTypeDlg)
    {
        if (FileMonTypeDlg->objectName().isEmpty())
            FileMonTypeDlg->setObjectName(QString::fromUtf8("FileMonTypeDlg"));
        FileMonTypeDlg->resize(349, 171);
        FileMonTypeDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        edtExt = new QLineEdit(FileMonTypeDlg);
        edtExt->setObjectName(QString::fromUtf8("edtExt"));
        edtExt->setGeometry(QRect(20, 80, 311, 25));
        edtExt->setMinimumSize(QSize(0, 25));
        edtExt->setMaximumSize(QSize(16777215, 25));
        btnOk = new QPushButton(FileMonTypeDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(260, 130, 75, 30));
        btnOk->setMinimumSize(QSize(0, 30));
        btnOk->setMaximumSize(QSize(16777215, 30));
        label = new QLabel(FileMonTypeDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 321, 25));
        label->setMaximumSize(QSize(16777215, 25));
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color:rgb(120, 0, 0);\n"
"}"));
        label_2 = new QLabel(FileMonTypeDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 271, 25));
        label_2->setMaximumSize(QSize(16777215, 25));
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color:rgb(120, 0, 0);\n"
"}"));
        frame = new QFrame(FileMonTypeDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 110, 311, 16));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);
        QWidget::setTabOrder(btnOk, edtExt);

        retranslateUi(FileMonTypeDlg);

        QMetaObject::connectSlotsByName(FileMonTypeDlg);
    } // setupUi

    void retranslateUi(QDialog *FileMonTypeDlg)
    {
        FileMonTypeDlg->setWindowTitle(QApplication::translate("FileMonTypeDlg", "\347\233\221\346\216\247\346\214\207\345\256\232\347\261\273\345\236\213\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        edtExt->setText(QApplication::translate("FileMonTypeDlg", "*.*;", 0, QApplication::UnicodeUTF8));
        edtExt->setPlaceholderText(QApplication::translate("FileMonTypeDlg", "\350\276\223\345\205\245\346\226\207\344\273\266\346\211\251\345\261\225\345\220\215\357\274\214\344\273\245 ; \345\210\206\351\232\224 ( \345\246\202 *.doc; )", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("FileMonTypeDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FileMonTypeDlg", "<html><head/><body><p>\350\276\223\345\205\245\350\246\201\347\233\221\346\216\247\346\226\207\344\273\266\347\261\273\345\236\213\347\232\204\346\211\251\345\261\225\345\220\215\357\274\214\344\273\245 ; \345\210\206\351\232\224 ( \345\246\202 *.doc;*.txt; \357\274\211</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FileMonTypeDlg", "<html><head/><body><p>\350\276\223\345\205\245 *.*; \344\273\243\350\241\250\347\233\221\346\216\247\346\211\200\346\234\211\346\226\207\344\273\266</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FileMonTypeDlg: public Ui_FileMonTypeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMONTYPEDLG_H
