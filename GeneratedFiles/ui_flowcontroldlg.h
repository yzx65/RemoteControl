/********************************************************************************
** Form generated from reading UI file 'flowcontroldlg.ui'
**
** Created: Tue Jun 30 23:21:59 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWCONTROLDLG_H
#define UI_FLOWCONTROLDLG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FlowControlDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QCheckBox *chkPlg1;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_3;
    QCheckBox *chkPlg2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QCheckBox *chkPlg4;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *FlowControlDlg)
    {
        if (FlowControlDlg->objectName().isEmpty())
            FlowControlDlg->setObjectName(QString::fromUtf8("FlowControlDlg"));
        FlowControlDlg->resize(412, 226);
        FlowControlDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(FlowControlDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 6);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FlowControlDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_2 = new QLabel(FlowControlDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(250, 0));
        label_2->setMaximumSize(QSize(250, 16777215));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(label_2);

        chkPlg1 = new QCheckBox(FlowControlDlg);
        chkPlg1->setObjectName(QString::fromUtf8("chkPlg1"));
        chkPlg1->setMinimumSize(QSize(100, 30));
        chkPlg1->setMaximumSize(QSize(100, 30));
        chkPlg1->setStyleSheet(QString::fromUtf8(" QCheckBox::indicator {\n"
"     width: 80px;\n"
"     height: 25px;\n"
" }\n"
"\n"
" QCheckBox::indicator:unchecked {\n"
"	image: url(image/btncheckoff.png);\n"
" }\n"
"\n"
" QCheckBox::indicator:checked {\n"
"	image: url(image/btncheckon.png);\n"
" }"));

        horizontalLayout_3->addWidget(chkPlg1);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_3 = new QLabel(FlowControlDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(250, 0));
        label_3->setMaximumSize(QSize(250, 16777215));
        label_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_3);

        chkPlg2 = new QCheckBox(FlowControlDlg);
        chkPlg2->setObjectName(QString::fromUtf8("chkPlg2"));
        chkPlg2->setMinimumSize(QSize(100, 30));
        chkPlg2->setMaximumSize(QSize(100, 30));
        chkPlg2->setStyleSheet(QString::fromUtf8(" QCheckBox::indicator {\n"
"     width: 80px;\n"
"     height: 25px;\n"
" }\n"
"\n"
" QCheckBox::indicator:unchecked {\n"
"	image: url(image/btncheckoff.png);\n"
" }\n"
"\n"
" QCheckBox::indicator:checked {\n"
"	image: url(image/btncheckon.png);\n"
" }"));

        horizontalLayout_4->addWidget(chkPlg2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_4 = new QLabel(FlowControlDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(250, 0));
        label_4->setMaximumSize(QSize(250, 16777215));
        label_4->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(label_4);

        chkPlg4 = new QCheckBox(FlowControlDlg);
        chkPlg4->setObjectName(QString::fromUtf8("chkPlg4"));
        chkPlg4->setMinimumSize(QSize(100, 30));
        chkPlg4->setMaximumSize(QSize(100, 30));
        chkPlg4->setStyleSheet(QString::fromUtf8(" QCheckBox::indicator {\n"
"     width: 80px;\n"
"     height: 25px;\n"
" }\n"
"\n"
" QCheckBox::indicator:unchecked {\n"
"	image: url(image/btncheckoff.png);\n"
" }\n"
"\n"
" QCheckBox::indicator:checked {\n"
"	image: url(image/btncheckon.png);\n"
" }"));

        horizontalLayout_5->addWidget(chkPlg4);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        frame = new QFrame(FlowControlDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnOK = new QPushButton(FlowControlDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 30));
        btnOK->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(btnOK);

        horizontalSpacer_6 = new QSpacerItem(23, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(FlowControlDlg);

        QMetaObject::connectSlotsByName(FlowControlDlg);
    } // setupUi

    void retranslateUi(QDialog *FlowControlDlg)
    {
        FlowControlDlg->setWindowTitle(QApplication::translate("FlowControlDlg", "\347\247\273\345\212\250\350\256\276\345\244\207\346\265\201\351\207\217\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FlowControlDlg", "\345\275\223\347\247\273\345\212\250\350\256\276\345\244\207\344\275\277\347\224\250 3G \347\275\221\347\273\234\346\227\266 :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FlowControlDlg", "\344\270\213\350\275\275\345\222\214\344\270\212\344\274\240\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        chkPlg1->setText(QString());
        label_3->setText(QApplication::translate("FlowControlDlg", "\350\216\267\345\217\226\351\224\256\347\233\230\350\256\260\345\275\225\343\200\201\350\201\224\347\263\273\344\272\272\344\277\241\346\201\257\345\217\212\351\200\232\350\256\257\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkPlg2->setText(QString());
        label_4->setText(QApplication::translate("FlowControlDlg", "\350\216\267\345\217\226\350\256\276\345\244\207\345\261\217\345\271\225\346\210\252\345\233\276", 0, QApplication::UnicodeUTF8));
        chkPlg4->setText(QString());
        btnOK->setText(QApplication::translate("FlowControlDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FlowControlDlg: public Ui_FlowControlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWCONTROLDLG_H
