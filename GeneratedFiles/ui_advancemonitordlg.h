/********************************************************************************
** Form generated from reading UI file 'advancemonitordlg.ui'
**
** Created: Wed May 20 21:08:17 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVANCEMONITORDLG_H
#define UI_ADVANCEMONITORDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AdvanceMonitorDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeWidget *trAdvanceFileMonitor;
    QVBoxLayout *verticalLayout_16;
    QLabel *lbAdvanceFileMonitor;
    QStackedWidget *stkAdvanceFileMonitor;
    QWidget *page_9;
    QVBoxLayout *verticalLayout_18;
    QTableWidget *tbUsbRetrieve;
    QWidget *page_7;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tbUsbPlugRecord;
    QTableWidget *tbUsbDir;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_17;
    QFrame *toolbar;
    QHBoxLayout *horizontalLayout_32;
    QToolButton *btnCleanMonitorRecord;
    QToolButton *btnCancelMonitor;
    QSpacerItem *horizontalSpacer_11;
    QTreeWidget *trFileStatus;

    void setupUi(QWidget *AdvanceMonitorDlg)
    {
        if (AdvanceMonitorDlg->objectName().isEmpty())
            AdvanceMonitorDlg->setObjectName(QString::fromUtf8("AdvanceMonitorDlg"));
        AdvanceMonitorDlg->resize(1038, 617);
        horizontalLayout = new QHBoxLayout(AdvanceMonitorDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        trAdvanceFileMonitor = new QTreeWidget(AdvanceMonitorDlg);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/usbplugrecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/downsearchfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/usbmonitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/interception.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/userfileaction.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(trAdvanceFileMonitor);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(trAdvanceFileMonitor);
        __qtreewidgetitem3->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem3);
        __qtreewidgetitem4->setIcon(0, icon4);
        trAdvanceFileMonitor->setObjectName(QString::fromUtf8("trAdvanceFileMonitor"));
        trAdvanceFileMonitor->setMaximumSize(QSize(200, 16777215));
        trAdvanceFileMonitor->setFocusPolicy(Qt::NoFocus);
        trAdvanceFileMonitor->setStyleSheet(QString::fromUtf8(" QWidget\n"
" {\n"
"	border:0px solid #cccccc;\n"
"	border-right-width:1px;\n"
"	border-bottom-width:1px;\n"
"	border-left-width:1px;\n"
"	background-color:rgb(240,240,240);\n"
" }\n"
"QTreeWidget::item {\n"
"	min-height:30px;\n"
"	background-color:transparent;\n"
"	padding-left:5px;\n"
" }\n"
" QTreeWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
"	min-height:30px;\n"
" }\n"
"  QTreeWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
" QTreeWidget::item:!has-children\n"
" {\n"
"	background-color:transparent;\n"
"	padding-left:25px;\n"
" }\n"
"  QTreeWidget::item:!has-children:hover\n"
" {\n"
"	background-color:rgba(100,100,100,50);\n"
"	padding-left:25px;\n"
" }\n"
" QTreeWidget::item:!has-children:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
" QTreeWidget::branch {\n"
"    background: transparent;\n"
" }"));
        trAdvanceFileMonitor->setIndentation(0);
        trAdvanceFileMonitor->setRootIsDecorated(false);
        trAdvanceFileMonitor->header()->setVisible(false);

        horizontalLayout->addWidget(trAdvanceFileMonitor);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(0);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        lbAdvanceFileMonitor = new QLabel(AdvanceMonitorDlg);
        lbAdvanceFileMonitor->setObjectName(QString::fromUtf8("lbAdvanceFileMonitor"));
        lbAdvanceFileMonitor->setMinimumSize(QSize(0, 35));
        lbAdvanceFileMonitor->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_16->addWidget(lbAdvanceFileMonitor);

        stkAdvanceFileMonitor = new QStackedWidget(AdvanceMonitorDlg);
        stkAdvanceFileMonitor->setObjectName(QString::fromUtf8("stkAdvanceFileMonitor"));
        page_9 = new QWidget();
        page_9->setObjectName(QString::fromUtf8("page_9"));
        verticalLayout_18 = new QVBoxLayout(page_9);
        verticalLayout_18->setSpacing(0);
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        tbUsbRetrieve = new QTableWidget(page_9);
        if (tbUsbRetrieve->columnCount() < 5)
            tbUsbRetrieve->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbUsbRetrieve->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbUsbRetrieve->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbUsbRetrieve->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbUsbRetrieve->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbUsbRetrieve->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tbUsbRetrieve->setObjectName(QString::fromUtf8("tbUsbRetrieve"));
        tbUsbRetrieve->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"\n"
"QTableWidget QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbUsbRetrieve{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image:none;\n"
"}\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
""
                        " QScrollBar::handle:vertical {\n"
"     background: #cccccc;;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        tbUsbRetrieve->setFrameShape(QFrame::NoFrame);
        tbUsbRetrieve->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUsbRetrieve->setSelectionMode(QAbstractItemView::SingleSelection);
        tbUsbRetrieve->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUsbRetrieve->setShowGrid(false);
        tbUsbRetrieve->horizontalHeader()->setDefaultSectionSize(200);
        tbUsbRetrieve->horizontalHeader()->setHighlightSections(false);
        tbUsbRetrieve->horizontalHeader()->setMinimumSectionSize(20);
        tbUsbRetrieve->horizontalHeader()->setStretchLastSection(true);
        tbUsbRetrieve->verticalHeader()->setVisible(false);
        tbUsbRetrieve->verticalHeader()->setDefaultSectionSize(20);
        tbUsbRetrieve->verticalHeader()->setHighlightSections(false);
        tbUsbRetrieve->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_18->addWidget(tbUsbRetrieve);

        stkAdvanceFileMonitor->addWidget(page_9);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        page_7->setStyleSheet(QString::fromUtf8("QWidget#page_7\n"
"{\n"
"	border:0px solid #aaaaaa;\n"
"	border-bottom-width:1px;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(page_7);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tbUsbPlugRecord = new QTableWidget(page_7);
        if (tbUsbPlugRecord->columnCount() < 4)
            tbUsbPlugRecord->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbUsbPlugRecord->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbUsbPlugRecord->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbUsbPlugRecord->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbUsbPlugRecord->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        tbUsbPlugRecord->setObjectName(QString::fromUtf8("tbUsbPlugRecord"));
        tbUsbPlugRecord->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"\n"
"QTableWidget QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbUsbPlugRecord{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
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
""
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
        tbUsbPlugRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUsbPlugRecord->setSelectionMode(QAbstractItemView::SingleSelection);
        tbUsbPlugRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUsbPlugRecord->setShowGrid(false);
        tbUsbPlugRecord->horizontalHeader()->setDefaultSectionSize(200);
        tbUsbPlugRecord->horizontalHeader()->setHighlightSections(false);
        tbUsbPlugRecord->horizontalHeader()->setMinimumSectionSize(20);
        tbUsbPlugRecord->horizontalHeader()->setStretchLastSection(true);
        tbUsbPlugRecord->verticalHeader()->setVisible(false);
        tbUsbPlugRecord->verticalHeader()->setDefaultSectionSize(20);
        tbUsbPlugRecord->verticalHeader()->setHighlightSections(false);
        tbUsbPlugRecord->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_4->addWidget(tbUsbPlugRecord);

        tbUsbDir = new QTableWidget(page_7);
        if (tbUsbDir->columnCount() < 5)
            tbUsbDir->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbUsbDir->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbUsbDir->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbUsbDir->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbUsbDir->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbUsbDir->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        tbUsbDir->setObjectName(QString::fromUtf8("tbUsbDir"));
        tbUsbDir->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"\n"
"QTableWidget QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbUsbDir{\n"
"	border:1px solid #cccccc;\n"
"	border-top-width:0px;\n"
"	border-left-width:0px;\n"
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
""
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
        tbUsbDir->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUsbDir->setSelectionMode(QAbstractItemView::SingleSelection);
        tbUsbDir->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUsbDir->setShowGrid(false);
        tbUsbDir->horizontalHeader()->setDefaultSectionSize(200);
        tbUsbDir->horizontalHeader()->setHighlightSections(false);
        tbUsbDir->horizontalHeader()->setMinimumSectionSize(20);
        tbUsbDir->horizontalHeader()->setStretchLastSection(true);
        tbUsbDir->verticalHeader()->setVisible(false);
        tbUsbDir->verticalHeader()->setDefaultSectionSize(20);
        tbUsbDir->verticalHeader()->setHighlightSections(false);
        tbUsbDir->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_4->addWidget(tbUsbDir);

        stkAdvanceFileMonitor->addWidget(page_7);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        verticalLayout_17 = new QVBoxLayout(page_6);
        verticalLayout_17->setSpacing(0);
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        toolbar = new QFrame(page_6);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        toolbar->setMinimumSize(QSize(0, 30));
        toolbar->setStyleSheet(QString::fromUtf8("QFrame#toolbar\n"
"{\n"
"	background-color:white;\n"
"}"));
        toolbar->setFrameShape(QFrame::StyledPanel);
        toolbar->setFrameShadow(QFrame::Raised);
        horizontalLayout_32 = new QHBoxLayout(toolbar);
        horizontalLayout_32->setSpacing(10);
        horizontalLayout_32->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(9, 4, -1, 4);
        btnCleanMonitorRecord = new QToolButton(toolbar);
        btnCleanMonitorRecord->setObjectName(QString::fromUtf8("btnCleanMonitorRecord"));
        btnCleanMonitorRecord->setMinimumSize(QSize(80, 25));
        btnCleanMonitorRecord->setMaximumSize(QSize(80, 25));
        btnCleanMonitorRecord->setStyleSheet(QString::fromUtf8("QToolButton\n"
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
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/destroy.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCleanMonitorRecord->setIcon(icon5);
        btnCleanMonitorRecord->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_32->addWidget(btnCleanMonitorRecord);

        btnCancelMonitor = new QToolButton(toolbar);
        btnCancelMonitor->setObjectName(QString::fromUtf8("btnCancelMonitor"));
        btnCancelMonitor->setMinimumSize(QSize(80, 25));
        btnCancelMonitor->setMaximumSize(QSize(80, 25));
        btnCancelMonitor->setStyleSheet(QString::fromUtf8("QToolButton\n"
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
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancelMonitor->setIcon(icon6);
        btnCancelMonitor->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_32->addWidget(btnCancelMonitor);

        horizontalSpacer_11 = new QSpacerItem(596, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_11);


        verticalLayout_17->addWidget(toolbar);

        trFileStatus = new QTreeWidget(page_6);
        trFileStatus->setObjectName(QString::fromUtf8("trFileStatus"));
        trFileStatus->setStyleSheet(QString::fromUtf8("/* QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(172, 197, 224, 255), stop:1 rgba(200, 230, 255, 225));\n"
"    padding-left: 4px;\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(130, 140, 190, 255), stop:1 rgba(172, 197, 255, 225));;\n"
"	height:25px;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
" }*/\n"
"\n"
"\n"
"QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"TableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trFileStatus{\n"
"	border:1px sol"
                        "id #cccccc;\n"
"	border-left-width:0px;\n"
"	border-right-width:0px;\n"
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
""
                        "     min-width: 100px;\n"
" }\n"
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trFileStatus->setIconSize(QSize(24, 24));
        trFileStatus->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

        verticalLayout_17->addWidget(trFileStatus);

        stkAdvanceFileMonitor->addWidget(page_6);

        verticalLayout_16->addWidget(stkAdvanceFileMonitor);


        horizontalLayout->addLayout(verticalLayout_16);


        retranslateUi(AdvanceMonitorDlg);

        stkAdvanceFileMonitor->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(AdvanceMonitorDlg);
    } // setupUi

    void retranslateUi(QWidget *AdvanceMonitorDlg)
    {
        AdvanceMonitorDlg->setWindowTitle(QApplication::translate("AdvanceMonitorDlg", "AdvanceMonitorDlg", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trAdvanceFileMonitor->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("AdvanceMonitorDlg", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trAdvanceFileMonitor->isSortingEnabled();
        trAdvanceFileMonitor->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trAdvanceFileMonitor->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("AdvanceMonitorDlg", "USB \350\256\276\345\244\207\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("AdvanceMonitorDlg", "\350\207\252\345\212\250\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("AdvanceMonitorDlg", "\346\217\222\346\213\224\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = trAdvanceFileMonitor->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("AdvanceMonitorDlg", "\346\226\207\344\273\266\347\212\266\346\200\201\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("AdvanceMonitorDlg", "\347\233\221\346\216\247\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        trAdvanceFileMonitor->setSortingEnabled(__sortingEnabled);

        lbAdvanceFileMonitor->setText(QApplication::translate("AdvanceMonitorDlg", "USB \350\256\276\345\244\207\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbUsbRetrieve->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("AdvanceMonitorDlg", "\346\226\207\344\273\266\347\233\256\346\240\207\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbUsbRetrieve->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("AdvanceMonitorDlg", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbUsbRetrieve->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("AdvanceMonitorDlg", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbUsbRetrieve->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("AdvanceMonitorDlg", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbUsbRetrieve->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("AdvanceMonitorDlg", "\344\273\216U\347\233\230\350\216\267\345\217\226\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbUsbPlugRecord->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("AdvanceMonitorDlg", "\346\217\222\345\205\245\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbUsbPlugRecord->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("AdvanceMonitorDlg", "\347\233\230\347\254\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbUsbPlugRecord->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QApplication::translate("AdvanceMonitorDlg", "USB \350\256\276\345\244\207 ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbUsbPlugRecord->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QApplication::translate("AdvanceMonitorDlg", "\346\227\266\351\225\277 (\347\247\222)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbUsbDir->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("AdvanceMonitorDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbUsbDir->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("AdvanceMonitorDlg", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbUsbDir->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("AdvanceMonitorDlg", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbUsbDir->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("AdvanceMonitorDlg", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbUsbDir->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("AdvanceMonitorDlg", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        btnCleanMonitorRecord->setText(QApplication::translate("AdvanceMonitorDlg", "\346\270\205\347\251\272\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        btnCancelMonitor->setText(QApplication::translate("AdvanceMonitorDlg", "\345\217\226\346\266\210\347\233\221\350\247\206", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = trFileStatus->headerItem();
        ___qtreewidgetitem6->setText(2, QApplication::translate("AdvanceMonitorDlg", "   \345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem6->setText(1, QApplication::translate("AdvanceMonitorDlg", "   \344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem6->setText(0, QApplication::translate("AdvanceMonitorDlg", "   \346\226\207\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AdvanceMonitorDlg: public Ui_AdvanceMonitorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVANCEMONITORDLG_H
