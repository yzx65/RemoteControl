/********************************************************************************
** Form generated from reading UI file 'multimediadlg.ui'
**
** Created: Tue Apr 14 09:44:29 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIMEDIADLG_H
#define UI_MULTIMEDIADLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MultimediaDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_24;
    QLabel *label_17;
    QListWidget *lstMonitorApp;
    QVBoxLayout *verticalLayout_25;
    QLabel *label_18;
    QListWidget *lstSaveTime;
    QVBoxLayout *verticalLayout_26;
    QLabel *label_19;
    QListWidget *lstFileType;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_20;
    QListWidget *lstFileList;

    void setupUi(QWidget *MultimediaDlg)
    {
        if (MultimediaDlg->objectName().isEmpty())
            MultimediaDlg->setObjectName(QString::fromUtf8("MultimediaDlg"));
        MultimediaDlg->resize(868, 529);
        MultimediaDlg->setStyleSheet(QString::fromUtf8("QWidget#MultimediaDlg\n"
"{\n"
"	background-color:rgb(240,240,240);\n"
"}"));
        horizontalLayout = new QHBoxLayout(MultimediaDlg);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(0);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        label_17 = new QLabel(MultimediaDlg);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMaximumSize(QSize(200, 16777215));
        label_17->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:white;\n"
"	color:#333333;\n"
"	min-height:30px;\n"
"	border: 1px solid #cccccc;\n"
"	border-top: 3px solid rgb(108,168,255);\n"
"	border-bottom-width:0px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_24->addWidget(label_17);

        lstMonitorApp = new QListWidget(MultimediaDlg);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/skype.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(lstMonitorApp);
        __qlistwidgetitem->setIcon(icon);
        lstMonitorApp->setObjectName(QString::fromUtf8("lstMonitorApp"));
        lstMonitorApp->setMaximumSize(QSize(200, 16777215));
        lstMonitorApp->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	/*border-right-width:0xp;*/\n"
"	font-size:13px;\n"
"}\n"
"\n"
"QListWidget::item\n"
"{\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
" QListWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
" }\n"
"\n"
"  QListWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }"));
        lstMonitorApp->setIconSize(QSize(16, 16));

        verticalLayout_24->addWidget(lstMonitorApp);


        horizontalLayout->addLayout(verticalLayout_24);

        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setSpacing(0);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        label_18 = new QLabel(MultimediaDlg);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMaximumSize(QSize(200, 16777215));
        label_18->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:white;\n"
"	color:#333333;\n"
"	min-height:30px;\n"
"	border: 1px solid #cccccc;\n"
"	border-top: 3px solid rgb(108,168,255);\n"
"	border-bottom-width:0px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_25->addWidget(label_18);

        lstSaveTime = new QListWidget(MultimediaDlg);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/time.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(lstSaveTime);
        __qlistwidgetitem1->setIcon(icon1);
        lstSaveTime->setObjectName(QString::fromUtf8("lstSaveTime"));
        lstSaveTime->setMaximumSize(QSize(200, 16777215));
        lstSaveTime->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	/*border-right-width:0xp;*/\n"
"	font-size:13px;\n"
"}\n"
"\n"
"QListWidget::item\n"
"{\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
" QListWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
" }\n"
"\n"
"  QListWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
"\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     background: #cccccc;;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
"     min-heiht: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));

        verticalLayout_25->addWidget(lstSaveTime);


        horizontalLayout->addLayout(verticalLayout_25);

        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setSpacing(0);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        label_19 = new QLabel(MultimediaDlg);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setMaximumSize(QSize(200, 16777215));
        label_19->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:white;\n"
"	color:#333333;\n"
"	min-height:30px;\n"
"	border: 1px solid #cccccc;\n"
"	border-top: 3px solid rgb(108,168,255);\n"
"	border-bottom-width:0px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_26->addWidget(label_19);

        lstFileType = new QListWidget(MultimediaDlg);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(lstFileType);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/album.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(lstFileType);
        __qlistwidgetitem3->setIcon(icon3);
        lstFileType->setObjectName(QString::fromUtf8("lstFileType"));
        lstFileType->setMaximumSize(QSize(200, 16777215));
        lstFileType->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	/*border-right-width:0xp;*/\n"
"	font-size:13px;\n"
"}\n"
"\n"
"QListWidget::item\n"
"{\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
" QListWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
" }\n"
"\n"
"  QListWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
"\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     background: #cccccc;;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
"     min-heiht: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));

        verticalLayout_26->addWidget(lstFileType);


        horizontalLayout->addLayout(verticalLayout_26);

        verticalLayout_27 = new QVBoxLayout();
        verticalLayout_27->setSpacing(0);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        label_20 = new QLabel(MultimediaDlg);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:white;\n"
"	color:#333333;\n"
"	min-height:30px;\n"
"	border: 1px solid #cccccc;\n"
"	border-top: 3px solid rgb(108,168,255);\n"
"	border-bottom-width:0px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_27->addWidget(label_20);

        lstFileList = new QListWidget(MultimediaDlg);
        lstFileList->setObjectName(QString::fromUtf8("lstFileList"));
        lstFileList->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"}\n"
"\n"
"QListWidget::item\n"
"{\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
" QListWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
" }\n"
"\n"
"  QListWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
"\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     background: #cccccc;;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
"     min-heiht: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
"}"));

        verticalLayout_27->addWidget(lstFileList);


        horizontalLayout->addLayout(verticalLayout_27);


        retranslateUi(MultimediaDlg);

        QMetaObject::connectSlotsByName(MultimediaDlg);
    } // setupUi

    void retranslateUi(QWidget *MultimediaDlg)
    {
        MultimediaDlg->setWindowTitle(QApplication::translate("MultimediaDlg", "MultimediaDlg", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MultimediaDlg", "\351\200\232\344\277\241\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = lstMonitorApp->isSortingEnabled();
        lstMonitorApp->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = lstMonitorApp->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MultimediaDlg", "Skype", 0, QApplication::UnicodeUTF8));
        lstMonitorApp->setSortingEnabled(__sortingEnabled);

        label_18->setText(QApplication::translate("MultimediaDlg", "\350\216\267\345\217\226\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = lstSaveTime->isSortingEnabled();
        lstSaveTime->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = lstSaveTime->item(0);
        ___qlistwidgetitem1->setText(QApplication::translate("MultimediaDlg", "2013-02-14 13:00:00", 0, QApplication::UnicodeUTF8));
        lstSaveTime->setSortingEnabled(__sortingEnabled1);

        label_19->setText(QApplication::translate("MultimediaDlg", "\346\226\207\344\273\266\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = lstFileType->isSortingEnabled();
        lstFileType->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = lstFileType->item(0);
        ___qlistwidgetitem2->setText(QApplication::translate("MultimediaDlg", "\351\200\232\350\257\235\345\275\225\351\237\263", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = lstFileType->item(1);
        ___qlistwidgetitem3->setText(QApplication::translate("MultimediaDlg", "\350\247\206\351\242\221\346\210\252\345\233\276", 0, QApplication::UnicodeUTF8));
        lstFileType->setSortingEnabled(__sortingEnabled2);

        label_20->setText(QApplication::translate("MultimediaDlg", "\346\226\207\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MultimediaDlg: public Ui_MultimediaDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIMEDIADLG_H
