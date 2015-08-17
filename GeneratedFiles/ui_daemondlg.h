/********************************************************************************
** Form generated from reading UI file 'daemondlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DAEMONDLG_H
#define UI_DAEMONDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DaemonDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtPort1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *edtPort2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *edtPort3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *edtPassword;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkEnableLog;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *chkShowLog;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;

    void setupUi(QDialog *DaemonDlg)
    {
        if (DaemonDlg->objectName().isEmpty())
            DaemonDlg->setObjectName(QString::fromUtf8("DaemonDlg"));
        DaemonDlg->resize(326, 214);
        DaemonDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"MicroSoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(DaemonDlg);
        verticalLayout->setSpacing(5);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 5);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(DaemonDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(50, 25));
        label_2->setMaximumSize(QSize(50, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        edtPort1 = new QLineEdit(DaemonDlg);
        edtPort1->setObjectName(QString::fromUtf8("edtPort1"));
        edtPort1->setMinimumSize(QSize(0, 25));

        horizontalLayout_4->addWidget(edtPort1);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(DaemonDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 25));
        label_3->setMaximumSize(QSize(50, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        edtPort2 = new QLineEdit(DaemonDlg);
        edtPort2->setObjectName(QString::fromUtf8("edtPort2"));
        edtPort2->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(edtPort2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(DaemonDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(50, 25));
        label_4->setMaximumSize(QSize(50, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        edtPort3 = new QLineEdit(DaemonDlg);
        edtPort3->setObjectName(QString::fromUtf8("edtPort3"));
        edtPort3->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(edtPort3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(DaemonDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(50, 25));
        label->setMaximumSize(QSize(50, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        edtPassword = new QLineEdit(DaemonDlg);
        edtPassword->setObjectName(QString::fromUtf8("edtPassword"));
        edtPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout_5->addWidget(edtPassword);


        verticalLayout->addLayout(horizontalLayout_5);

        frame = new QFrame(DaemonDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkEnableLog = new QCheckBox(DaemonDlg);
        chkEnableLog->setObjectName(QString::fromUtf8("chkEnableLog"));
        chkEnableLog->setChecked(true);

        horizontalLayout->addWidget(chkEnableLog);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        chkShowLog = new QCheckBox(DaemonDlg);
        chkShowLog->setObjectName(QString::fromUtf8("chkShowLog"));
        chkShowLog->setChecked(true);

        horizontalLayout->addWidget(chkShowLog);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(DaemonDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DaemonDlg);

        QMetaObject::connectSlotsByName(DaemonDlg);
    } // setupUi

    void retranslateUi(QDialog *DaemonDlg)
    {
        DaemonDlg->setWindowTitle(QApplication::translate("DaemonDlg", "\347\224\237\346\210\220\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DaemonDlg", "\351\200\232\344\277\241\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        edtPort1->setText(QApplication::translate("DaemonDlg", "8080", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DaemonDlg", "\346\216\247\345\210\266\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        edtPort2->setText(QApplication::translate("DaemonDlg", "8088", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DaemonDlg", "\346\225\260\346\215\256\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        edtPort3->setText(QApplication::translate("DaemonDlg", "8089", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DaemonDlg", "\351\252\214\350\257\201\347\240\201", 0, QApplication::UnicodeUTF8));
        chkEnableLog->setText(QApplication::translate("DaemonDlg", "\345\220\257\347\224\250\346\227\245\345\277\227\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        chkShowLog->setText(QApplication::translate("DaemonDlg", "\346\230\276\347\244\272\346\227\245\345\277\227\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("DaemonDlg", "\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DaemonDlg: public Ui_DaemonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DAEMONDLG_H
