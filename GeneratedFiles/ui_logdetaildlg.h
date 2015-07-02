/********************************************************************************
** Form generated from reading UI file 'logdetaildlg.ui'
**
** Created: Tue Jun 30 23:21:58 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGDETAILDLG_H
#define UI_LOGDETAILDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <pagetablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_LogDetailDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame4;
    QVBoxLayout *verticalLayout_22;
    QRadioButton *chkOnlineLog;
    QRadioButton *chkLogDownload;
    QRadioButton *chkLogUpload;
    QRadioButton *chkLogPlugin;
    QRadioButton *chkDetailLog;
    QSpacerItem *verticalSpacer_2;
    QStackedWidget *stkLog;
    QWidget *page_16;
    QHBoxLayout *horizontalLayout_22;
    PageTableWidget *tbLog;
    QWidget *page_18;
    QHBoxLayout *horizontalLayout_24;
    PageTableWidget *tbDetailLog;
    QWidget *page_19;
    QHBoxLayout *horizontalLayout_27;
    PageTableWidget *tbLogDownload;
    QWidget *page_26;
    QHBoxLayout *horizontalLayout_26;
    PageTableWidget *tbLogUpload;
    QWidget *page_27;
    QHBoxLayout *horizontalLayout_25;
    PageTableWidget *tbLogPlugin;

    void setupUi(QWidget *LogDetailDlg)
    {
        if (LogDetailDlg->objectName().isEmpty())
            LogDetailDlg->setObjectName(QString::fromUtf8("LogDetailDlg"));
        LogDetailDlg->resize(871, 483);
        horizontalLayout = new QHBoxLayout(LogDetailDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame4 = new QFrame(LogDetailDlg);
        frame4->setObjectName(QString::fromUtf8("frame4"));
        frame4->setMaximumSize(QSize(200, 16777215));
        frame4->setStyleSheet(QString::fromUtf8(" QWidget#frame4\n"
" {\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-left-width:1px;\n"
"	border-right-width:1px;\n"
"	background-color:white;\n"
" }"));
        verticalLayout_22 = new QVBoxLayout(frame4);
        verticalLayout_22->setSpacing(0);
        verticalLayout_22->setContentsMargins(0, 0, 0, 0);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        chkOnlineLog = new QRadioButton(frame4);
        chkOnlineLog->setObjectName(QString::fromUtf8("chkOnlineLog"));
        chkOnlineLog->setMinimumSize(QSize(200, 0));
        chkOnlineLog->setStyleSheet(QString::fromUtf8("QRadioButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color:rgba(100,100,100, 50);\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QRadioButton::indicator \n"
"{\n"
"     width: 10px;\n"
"     height: 32px;\n"
"	 image:none;\n"
" }"));
        chkOnlineLog->setChecked(true);

        verticalLayout_22->addWidget(chkOnlineLog);

        chkLogDownload = new QRadioButton(frame4);
        chkLogDownload->setObjectName(QString::fromUtf8("chkLogDownload"));
        chkLogDownload->setStyleSheet(QString::fromUtf8("QRadioButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color:rgba(100,100,100, 50);\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QRadioButton::indicator \n"
"{\n"
"     width: 10px;\n"
"     height: 32px;\n"
"	 image:none;\n"
" }"));

        verticalLayout_22->addWidget(chkLogDownload);

        chkLogUpload = new QRadioButton(frame4);
        chkLogUpload->setObjectName(QString::fromUtf8("chkLogUpload"));
        chkLogUpload->setStyleSheet(QString::fromUtf8("QRadioButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color:rgba(100,100,100, 50);\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QRadioButton::indicator \n"
"{\n"
"     width: 10px;\n"
"     height: 32px;\n"
"	 image:none;\n"
" }"));

        verticalLayout_22->addWidget(chkLogUpload);

        chkLogPlugin = new QRadioButton(frame4);
        chkLogPlugin->setObjectName(QString::fromUtf8("chkLogPlugin"));
        chkLogPlugin->setStyleSheet(QString::fromUtf8("QRadioButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color:rgba(100,100,100, 50);\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QRadioButton::indicator \n"
"{\n"
"     width: 10px;\n"
"     height: 32px;\n"
"	 image:none;\n"
" }"));

        verticalLayout_22->addWidget(chkLogPlugin);

        chkDetailLog = new QRadioButton(frame4);
        chkDetailLog->setObjectName(QString::fromUtf8("chkDetailLog"));
        chkDetailLog->setMinimumSize(QSize(200, 30));
        chkDetailLog->setStyleSheet(QString::fromUtf8("QRadioButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color:rgba(100,100,100, 50);\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QRadioButton::indicator \n"
"{\n"
"     width: 10px;\n"
"     height: 32px;\n"
"	 image:none;\n"
" }"));

        verticalLayout_22->addWidget(chkDetailLog);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_22->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(frame4);

        stkLog = new QStackedWidget(LogDetailDlg);
        stkLog->setObjectName(QString::fromUtf8("stkLog"));
        page_16 = new QWidget();
        page_16->setObjectName(QString::fromUtf8("page_16"));
        horizontalLayout_22 = new QHBoxLayout(page_16);
        horizontalLayout_22->setSpacing(0);
        horizontalLayout_22->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        tbLog = new PageTableWidget(page_16);
        tbLog->setObjectName(QString::fromUtf8("tbLog"));
        tbLog->setMaximumSize(QSize(1677215, 16777215));
        tbLog->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_22->addWidget(tbLog);

        stkLog->addWidget(page_16);
        page_18 = new QWidget();
        page_18->setObjectName(QString::fromUtf8("page_18"));
        horizontalLayout_24 = new QHBoxLayout(page_18);
        horizontalLayout_24->setSpacing(0);
        horizontalLayout_24->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        tbDetailLog = new PageTableWidget(page_18);
        tbDetailLog->setObjectName(QString::fromUtf8("tbDetailLog"));
        tbDetailLog->setMaximumSize(QSize(1677215, 16777215));
        tbDetailLog->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_24->addWidget(tbDetailLog);

        stkLog->addWidget(page_18);
        page_19 = new QWidget();
        page_19->setObjectName(QString::fromUtf8("page_19"));
        horizontalLayout_27 = new QHBoxLayout(page_19);
        horizontalLayout_27->setSpacing(0);
        horizontalLayout_27->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        tbLogDownload = new PageTableWidget(page_19);
        tbLogDownload->setObjectName(QString::fromUtf8("tbLogDownload"));
        tbLogDownload->setMaximumSize(QSize(1677215, 16777215));
        tbLogDownload->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_27->addWidget(tbLogDownload);

        stkLog->addWidget(page_19);
        page_26 = new QWidget();
        page_26->setObjectName(QString::fromUtf8("page_26"));
        horizontalLayout_26 = new QHBoxLayout(page_26);
        horizontalLayout_26->setSpacing(0);
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        tbLogUpload = new PageTableWidget(page_26);
        tbLogUpload->setObjectName(QString::fromUtf8("tbLogUpload"));
        tbLogUpload->setMaximumSize(QSize(1677215, 16777215));
        tbLogUpload->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_26->addWidget(tbLogUpload);

        stkLog->addWidget(page_26);
        page_27 = new QWidget();
        page_27->setObjectName(QString::fromUtf8("page_27"));
        horizontalLayout_25 = new QHBoxLayout(page_27);
        horizontalLayout_25->setSpacing(0);
        horizontalLayout_25->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        tbLogPlugin = new PageTableWidget(page_27);
        tbLogPlugin->setObjectName(QString::fromUtf8("tbLogPlugin"));
        tbLogPlugin->setMaximumSize(QSize(1677215, 16777215));
        tbLogPlugin->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_25->addWidget(tbLogPlugin);

        stkLog->addWidget(page_27);

        horizontalLayout->addWidget(stkLog);


        retranslateUi(LogDetailDlg);

        stkLog->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LogDetailDlg);
    } // setupUi

    void retranslateUi(QWidget *LogDetailDlg)
    {
        LogDetailDlg->setWindowTitle(QApplication::translate("LogDetailDlg", "LogDetailDlg", 0, QApplication::UnicodeUTF8));
        chkOnlineLog->setText(QApplication::translate("LogDetailDlg", "\344\270\212\344\270\213\347\272\277\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
        chkLogDownload->setText(QApplication::translate("LogDetailDlg", "\346\226\207\344\273\266\344\270\213\350\275\275\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkLogUpload->setText(QApplication::translate("LogDetailDlg", "\346\226\207\344\273\266\344\270\212\344\274\240\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkLogPlugin->setText(QApplication::translate("LogDetailDlg", "\346\217\222\344\273\266\346\225\260\346\215\256\345\233\236\344\274\240\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkDetailLog->setText(QApplication::translate("LogDetailDlg", "\345\205\250\351\203\250\346\227\245\345\277\227", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LogDetailDlg: public Ui_LogDetailDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGDETAILDLG_H
