/********************************************************************************
** Form generated from reading UI file 'thirdplugindlg.ui'
**
** Created: Fri Apr 10 09:05:15 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THIRDPLUGINDLG_H
#define UI_THIRDPLUGINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ThirdPluginDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QFrame *frmPlugList;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QFrame *frameThirdPluginToolBar;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnAddThirdPlugin;
    QToolButton *btnUpdateThirdPlugin;
    QToolButton *btnDeleteThirdPlugin;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tbThirdPluginList;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTreeWidget *trThirdPluginFileList;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QTextEdit *edtPreview;

    void setupUi(QWidget *ThirdPluginDlg)
    {
        if (ThirdPluginDlg->objectName().isEmpty())
            ThirdPluginDlg->setObjectName(QString::fromUtf8("ThirdPluginDlg"));
        ThirdPluginDlg->resize(752, 430);
        ThirdPluginDlg->setStyleSheet(QString::fromUtf8("QWidget#ThirdPluginDlg\n"
"{\n"
"	background-color:rgb(240,240,240);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(ThirdPluginDlg);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        frmPlugList = new QFrame(ThirdPluginDlg);
        frmPlugList->setObjectName(QString::fromUtf8("frmPlugList"));
        frmPlugList->setMaximumSize(QSize(200, 16777215));
        verticalLayout = new QVBoxLayout(frmPlugList);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(frmPlugList);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(88,148,255);\n"
"	color:white;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout->addWidget(label_2);

        frameThirdPluginToolBar = new QFrame(frmPlugList);
        frameThirdPluginToolBar->setObjectName(QString::fromUtf8("frameThirdPluginToolBar"));
        frameThirdPluginToolBar->setMinimumSize(QSize(0, 25));
        frameThirdPluginToolBar->setMaximumSize(QSize(16777215, 25));
        frameThirdPluginToolBar->setStyleSheet(QString::fromUtf8("QFrame#frameThirdPluginToolBar\n"
"{\n"
"	background-color:#eef0ff;\n"
"	color:black;;\n"
"	border-width:0px;\n"
"	border-style:solid;\n"
"	border-color:#cccccc;\n"
"	border-left-width:1px;\n"
"	border-right-width:1px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(frameThirdPluginToolBar);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnAddThirdPlugin = new QToolButton(frameThirdPluginToolBar);
        btnAddThirdPlugin->setObjectName(QString::fromUtf8("btnAddThirdPlugin"));
        btnAddThirdPlugin->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:#bbbbbb;\n"
"}\n"
"\n"
"QToolButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout->addWidget(btnAddThirdPlugin);

        btnUpdateThirdPlugin = new QToolButton(frameThirdPluginToolBar);
        btnUpdateThirdPlugin->setObjectName(QString::fromUtf8("btnUpdateThirdPlugin"));
        btnUpdateThirdPlugin->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:#bbbbbb;\n"
"}\n"
"\n"
"QToolButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout->addWidget(btnUpdateThirdPlugin);

        btnDeleteThirdPlugin = new QToolButton(frameThirdPluginToolBar);
        btnDeleteThirdPlugin->setObjectName(QString::fromUtf8("btnDeleteThirdPlugin"));
        btnDeleteThirdPlugin->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:#bbbbbb;\n"
"}\n"
"\n"
"QToolButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout->addWidget(btnDeleteThirdPlugin);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(frameThirdPluginToolBar);

        tbThirdPluginList = new QTableWidget(frmPlugList);
        if (tbThirdPluginList->columnCount() < 2)
            tbThirdPluginList->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbThirdPluginList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbThirdPluginList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbThirdPluginList->setObjectName(QString::fromUtf8("tbThirdPluginList"));
        tbThirdPluginList->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section \n"
"{\n"
"	background-color:white;\n"
"	color:black;\n"
"	min-height:25px;\n"
"	border-width:0px;\n"
"	border-style:solid;\n"
"	border-color:#cccccc;\n"
"	border-right-width:1px;\n"
"	border-bottom-width:1px;\n"
"}\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	color:black;\n"
"	padding-left:10px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image:none;\n"
"}\n"
"QWidget#tbThirdPluginList\n"
"{\n"
"	border:1px solid #cccccc;\n"
"}"));
        tbThirdPluginList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbThirdPluginList->setSelectionMode(QAbstractItemView::SingleSelection);
        tbThirdPluginList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbThirdPluginList->setShowGrid(false);
        tbThirdPluginList->horizontalHeader()->setDefaultSectionSize(50);
        tbThirdPluginList->horizontalHeader()->setHighlightSections(false);
        tbThirdPluginList->horizontalHeader()->setStretchLastSection(true);
        tbThirdPluginList->verticalHeader()->setDefaultSectionSize(25);
        tbThirdPluginList->verticalHeader()->setHighlightSections(false);

        verticalLayout->addWidget(tbThirdPluginList);


        horizontalLayout_2->addWidget(frmPlugList);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(ThirdPluginDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(88,148,255);\n"
"	color:white;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_2->addWidget(label);

        trThirdPluginFileList = new QTreeWidget(ThirdPluginDlg);
        trThirdPluginFileList->setObjectName(QString::fromUtf8("trThirdPluginFileList"));
        trThirdPluginFileList->setStyleSheet(QString::fromUtf8("/* QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(172, 197, 224, 255), stop:1 rgba(200, 230, 255, 225));\n"
"    padding-left: 4px;\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(130, 140, 190, 255), stop:1 rgba(172, 197, 255, 225));;\n"
"	height:25px;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
" }*/\n"
"\n"
"QHeaderView \n"
"{\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	background-color:#eef0ff;\n"
"	color:black;\n"
"}\n"
"QHeaderView::section \n"
"{\n"
"	background-color:#eef0ff;\n"
"	color:black;\n"
"	min-height:25px;\n"
"	border-width:0px;\n"
"	border-style:solid;\n"
"	padding-left:5px;\n"
"	border-color:#cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-top-width:1px;\n"
"}\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trThirdPluginFileList{\n"
"	border:1px solid #cccccc;\n"
"	border-top"
                        "-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image:none;\n"
"}\n"
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
" }\n"
"\n"
" QScrollBar:horizontal {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     height: 5px;\n"
" }\n"
" QScrollBar::handle:horizontal {\n"
"     background: #cccccc;;\n"
"     min-width: 100px;\n"
" }\n"
" QScrollBar::handle:horizontal:hover {\n"
"     background: #aaaaaa;\n"
"     min-width: 100px;\n"
" }\n"
" QScrollBar::add-line:"
                        "horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trThirdPluginFileList->setIconSize(QSize(24, 24));
        trThirdPluginFileList->setIndentation(0);
        trThirdPluginFileList->header()->setDefaultSectionSize(200);
        trThirdPluginFileList->header()->setMinimumSectionSize(30);

        verticalLayout_2->addWidget(trThirdPluginFileList);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_4 = new QLabel(ThirdPluginDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(88,148,255);\n"
"	color:white;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_4->addWidget(label_4);

        edtPreview = new QTextEdit(ThirdPluginDlg);
        edtPreview->setObjectName(QString::fromUtf8("edtPreview"));
        edtPreview->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border: 1px solid #cccccc;\n"
"}"));

        verticalLayout_4->addWidget(edtPreview);


        horizontalLayout_2->addLayout(verticalLayout_4);


        retranslateUi(ThirdPluginDlg);

        QMetaObject::connectSlotsByName(ThirdPluginDlg);
    } // setupUi

    void retranslateUi(QWidget *ThirdPluginDlg)
    {
        ThirdPluginDlg->setWindowTitle(QApplication::translate("ThirdPluginDlg", "\347\254\254\344\270\211\346\226\271\346\217\222\344\273\266\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ThirdPluginDlg", "\346\217\222\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        btnAddThirdPlugin->setText(QApplication::translate("ThirdPluginDlg", "\346\226\260\345\242\236", 0, QApplication::UnicodeUTF8));
        btnUpdateThirdPlugin->setText(QApplication::translate("ThirdPluginDlg", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
        btnDeleteThirdPlugin->setText(QApplication::translate("ThirdPluginDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbThirdPluginList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ThirdPluginDlg", "  \346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbThirdPluginList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ThirdPluginDlg", "  \347\211\210\346\234\254\345\217\267", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ThirdPluginDlg", "\346\226\207\344\273\266\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trThirdPluginFileList->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("ThirdPluginDlg", "\344\277\256\346\224\271\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("ThirdPluginDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ThirdPluginDlg", "\346\226\207\344\273\266\351\242\204\350\247\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ThirdPluginDlg: public Ui_ThirdPluginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THIRDPLUGINDLG_H
