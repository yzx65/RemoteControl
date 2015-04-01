/********************************************************************************
** Form generated from reading UI file 'autogetdlg.ui'
**
** Created: Wed Apr 1 09:44:52 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOGETDLG_H
#define UI_AUTOGETDLG_H

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
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AutoGetDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QCheckBox *chkAutoGet;
    QFrame *frmDetail;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QSpinBox *spnDepth;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *chkFullDepth;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnOK;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *AutoGetDlg)
    {
        if (AutoGetDlg->objectName().isEmpty())
            AutoGetDlg->setObjectName(QString::fromUtf8("AutoGetDlg"));
        AutoGetDlg->resize(412, 172);
        AutoGetDlg->setMinimumSize(QSize(412, 0));
        AutoGetDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(AutoGetDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 9);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(AutoGetDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));
        label_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        frame_2 = new QFrame(AutoGetDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        horizontalLayout_5 = new QHBoxLayout(frame_2);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_4 = new QLabel(frame_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(250, 0));
        label_4->setMaximumSize(QSize(250, 16777215));
        label_4->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(label_4);

        chkAutoGet = new QCheckBox(frame_2);
        chkAutoGet->setObjectName(QString::fromUtf8("chkAutoGet"));
        chkAutoGet->setMinimumSize(QSize(100, 30));
        chkAutoGet->setMaximumSize(QSize(100, 30));
        chkAutoGet->setStyleSheet(QString::fromUtf8(" QCheckBox::indicator {\n"
"     width: 80px;\n"
"     height: 25px;\n"
" }\n"
"\n"
" QCheckBox::indicator:unchecked {\n"
"	image: url(:/image/btncheckoff.png);\n"
" }\n"
"\n"
" QCheckBox::indicator:checked {\n"
"	image: url(:/image/btncheckon.png);\n"
" }"));

        horizontalLayout_5->addWidget(chkAutoGet);


        verticalLayout->addWidget(frame_2);

        frmDetail = new QFrame(AutoGetDlg);
        frmDetail->setObjectName(QString::fromUtf8("frmDetail"));
        horizontalLayout_7 = new QHBoxLayout(frmDetail);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_9 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        label_5 = new QLabel(frmDetail);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(60, 0));
        label_5->setMaximumSize(QSize(60, 16777215));
        label_5->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_7->addWidget(label_5);

        spnDepth = new QSpinBox(frmDetail);
        spnDepth->setObjectName(QString::fromUtf8("spnDepth"));

        horizontalLayout_7->addWidget(spnDepth);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        chkFullDepth = new QCheckBox(frmDetail);
        chkFullDepth->setObjectName(QString::fromUtf8("chkFullDepth"));
        chkFullDepth->setMinimumSize(QSize(180, 30));
        chkFullDepth->setMaximumSize(QSize(180, 30));
        chkFullDepth->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_7->addWidget(chkFullDepth);


        verticalLayout->addWidget(frmDetail);

        frame = new QFrame(AutoGetDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        btnOK = new QPushButton(AutoGetDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 30));
        btnOK->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(btnOK);

        horizontalSpacer_8 = new QSpacerItem(23, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(AutoGetDlg);

        QMetaObject::connectSlotsByName(AutoGetDlg);
    } // setupUi

    void retranslateUi(QDialog *AutoGetDlg)
    {
        AutoGetDlg->setWindowTitle(QApplication::translate("AutoGetDlg", "\350\207\252\345\212\250\350\216\267\345\217\226\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AutoGetDlg", "\345\275\223\347\233\256\346\240\207\344\270\212\347\272\277\346\227\266 : ", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AutoGetDlg", "\350\207\252\345\212\250\350\216\267\345\217\226\347\233\256\346\240\207\346\226\207\344\273\266\347\263\273\347\273\237\347\232\204\347\233\256\345\275\225\347\273\223\346\236\204", 0, QApplication::UnicodeUTF8));
        chkAutoGet->setText(QString());
        label_5->setText(QApplication::translate("AutoGetDlg", "\350\216\267\345\217\226\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        chkFullDepth->setText(QApplication::translate("AutoGetDlg", "\350\216\267\345\217\226\346\211\200\346\234\211\345\261\202\346\254\241\347\233\256\345\275\225\347\273\223\346\236\204\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("AutoGetDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AutoGetDlg: public Ui_AutoGetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOGETDLG_H
