/********************************************************************************
** Form generated from reading UI file 'conndlg.ui'
**
** Created: Sun Sep 20 15:23:23 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNDLG_H
#define UI_CONNDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *edtIP;
    QFrame *frmCtrlPort;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtCtrlPort;
    QFrame *frmPort;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtTargetPort;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *edtPass;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *chkAutoConn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnOk;

    void setupUi(QWidget *ConnDlg)
    {
        if (ConnDlg->objectName().isEmpty())
            ConnDlg->setObjectName(QString::fromUtf8("ConnDlg"));
        ConnDlg->resize(309, 215);
        ConnDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(ConnDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, -1, 10, 10);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(ConnDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(50, 25));
        label->setMaximumSize(QSize(50, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        edtIP = new QComboBox(ConnDlg);
        edtIP->setObjectName(QString::fromUtf8("edtIP"));
        edtIP->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edtIP->sizePolicy().hasHeightForWidth());
        edtIP->setSizePolicy(sizePolicy);
        edtIP->setMinimumSize(QSize(0, 25));
        edtIP->setEditable(true);

        horizontalLayout_3->addWidget(edtIP);


        verticalLayout->addLayout(horizontalLayout_3);

        frmCtrlPort = new QFrame(ConnDlg);
        frmCtrlPort->setObjectName(QString::fromUtf8("frmCtrlPort"));
        horizontalLayout_2 = new QHBoxLayout(frmCtrlPort);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        label_2 = new QLabel(frmCtrlPort);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(50, 25));
        label_2->setMaximumSize(QSize(50, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        edtCtrlPort = new QLineEdit(frmCtrlPort);
        edtCtrlPort->setObjectName(QString::fromUtf8("edtCtrlPort"));
        edtCtrlPort->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(edtCtrlPort);


        verticalLayout->addWidget(frmCtrlPort);

        frmPort = new QFrame(ConnDlg);
        frmPort->setObjectName(QString::fromUtf8("frmPort"));
        horizontalLayout = new QHBoxLayout(frmPort);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(frmPort);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 25));
        label_3->setMaximumSize(QSize(50, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        edtTargetPort = new QLineEdit(frmPort);
        edtTargetPort->setObjectName(QString::fromUtf8("edtTargetPort"));
        edtTargetPort->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(edtTargetPort);


        verticalLayout->addWidget(frmPort);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(ConnDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(50, 25));
        label_4->setMaximumSize(QSize(50, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        edtPass = new QLineEdit(ConnDlg);
        edtPass->setObjectName(QString::fromUtf8("edtPass"));
        edtPass->setMinimumSize(QSize(0, 25));
        edtPass->setEchoMode(QLineEdit::Password);

        horizontalLayout_5->addWidget(edtPass);


        verticalLayout->addLayout(horizontalLayout_5);

        frame = new QFrame(ConnDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        chkAutoConn = new QCheckBox(ConnDlg);
        chkAutoConn->setObjectName(QString::fromUtf8("chkAutoConn"));

        horizontalLayout_4->addWidget(chkAutoConn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        btnOk = new QPushButton(ConnDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(ConnDlg);

        QMetaObject::connectSlotsByName(ConnDlg);
    } // setupUi

    void retranslateUi(QWidget *ConnDlg)
    {
        ConnDlg->setWindowTitle(QApplication::translate("ConnDlg", "\350\277\236\346\216\245\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConnDlg", "IP \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConnDlg", "\346\216\247\345\210\266\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConnDlg", "\346\225\260\346\215\256\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ConnDlg", "\351\252\214\350\257\201\347\240\201", 0, QApplication::UnicodeUTF8));
        chkAutoConn->setText(QApplication::translate("ConnDlg", "\345\220\257\345\212\250\346\227\266\350\207\252\345\212\250\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("ConnDlg", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnDlg: public Ui_ConnDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNDLG_H
