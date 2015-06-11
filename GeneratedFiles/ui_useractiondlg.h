/********************************************************************************
** Form generated from reading UI file 'useractiondlg.ui'
**
** Created: Sun Jun 7 19:02:07 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERACTIONDLG_H
#define UI_USERACTIONDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <pagetablewidget.h>

QT_BEGIN_NAMESPACE

class Ui_UserActionDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeWidget *trUserAction;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_15;
    QFrame *title;
    QHBoxLayout *horizontalLayout_21;
    QLabel *lbUserAction;
    QToolButton *btnRefreshData;
    QStackedWidget *stkUserAction;
    QWidget *page_20;
    QVBoxLayout *verticalLayout_49;
    QTableWidget *tbUserFileAction;
    QWidget *page_21;
    QVBoxLayout *verticalLayout_50;
    PageTableWidget *tbKeyboardRecord;
    QLabel *label_3;
    QTextEdit *edtKeyboardRecordDetail;
    QWidget *page_22;
    QVBoxLayout *verticalLayout_52;
    QTableWidget *tbPasswordRecord;
    QLabel *label_4;
    QTextEdit *edtPasswordDetail;
    QWidget *page_23;
    QVBoxLayout *verticalLayout_54;
    QTableWidget *tbClipboardData;
    QLabel *label_5;
    QTextEdit *edtClipboardDataDetail;
    QWidget *page_24;
    QVBoxLayout *verticalLayout_56;
    QTableWidget *tbFileAccessRecord;
    QWidget *page_25;
    QVBoxLayout *verticalLayout_57;
    QTableWidget *tbCommandRecord;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_13;
    QTableWidget *tbMessageInfo;
    QLabel *label_11;
    QTextEdit *edtMessageInfoDetail;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_14;
    QTableWidget *tbCallInfo;
    QWidget *page_15;
    QVBoxLayout *verticalLayout_19;
    QTableWidget *tbAddressBook;

    void setupUi(QWidget *UserActionDlg)
    {
        if (UserActionDlg->objectName().isEmpty())
            UserActionDlg->setObjectName(QString::fromUtf8("UserActionDlg"));
        UserActionDlg->resize(928, 602);
        horizontalLayout = new QHBoxLayout(UserActionDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        trUserAction = new QTreeWidget(UserActionDlg);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/userfileaction.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/allfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/point.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/sensitiveinfo.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/useraction.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/secretwindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/clipboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/processmonitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/ios_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/message.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/call.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/group.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(trUserAction);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem3->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem4->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem5->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem6->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(__qtreewidgetitem);
        __qtreewidgetitem7->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(trUserAction);
        __qtreewidgetitem8->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem9->setIcon(0, icon4);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem10->setIcon(0, icon5);
        QTreeWidgetItem *__qtreewidgetitem11 = new QTreeWidgetItem(__qtreewidgetitem8);
        __qtreewidgetitem11->setIcon(0, icon6);
        QTreeWidgetItem *__qtreewidgetitem12 = new QTreeWidgetItem(trUserAction);
        __qtreewidgetitem12->setIcon(0, icon7);
        QTreeWidgetItem *__qtreewidgetitem13 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem13->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem14 = new QTreeWidgetItem(__qtreewidgetitem12);
        __qtreewidgetitem14->setIcon(0, icon8);
        QTreeWidgetItem *__qtreewidgetitem15 = new QTreeWidgetItem(trUserAction);
        __qtreewidgetitem15->setIcon(0, icon9);
        QTreeWidgetItem *__qtreewidgetitem16 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem16->setIcon(0, icon10);
        QTreeWidgetItem *__qtreewidgetitem17 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem17->setIcon(0, icon11);
        QTreeWidgetItem *__qtreewidgetitem18 = new QTreeWidgetItem(__qtreewidgetitem15);
        __qtreewidgetitem18->setIcon(0, icon12);
        trUserAction->setObjectName(QString::fromUtf8("trUserAction"));
        trUserAction->setMinimumSize(QSize(200, 0));
        trUserAction->setMaximumSize(QSize(200, 16777215));
        trUserAction->setStyleSheet(QString::fromUtf8(" QWidget\n"
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
        trUserAction->setSelectionBehavior(QAbstractItemView::SelectItems);
        trUserAction->setIndentation(0);
        trUserAction->setRootIsDecorated(false);
        trUserAction->header()->setVisible(false);

        horizontalLayout->addWidget(trUserAction);

        frame_10 = new QFrame(UserActionDlg);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        verticalLayout_15 = new QVBoxLayout(frame_10);
        verticalLayout_15->setSpacing(0);
        verticalLayout_15->setContentsMargins(0, 0, 0, 0);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        title = new QFrame(frame_10);
        title->setObjectName(QString::fromUtf8("title"));
        title->setStyleSheet(QString::fromUtf8("QFrame\n"
"{	\n"
"	background-color: #dddddd;\n"
"}"));
        horizontalLayout_21 = new QHBoxLayout(title);
        horizontalLayout_21->setSpacing(0);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(0, 0, 6, 0);
        lbUserAction = new QLabel(title);
        lbUserAction->setObjectName(QString::fromUtf8("lbUserAction"));
        lbUserAction->setMinimumSize(QSize(0, 35));
        lbUserAction->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        horizontalLayout_21->addWidget(lbUserAction);

        btnRefreshData = new QToolButton(title);
        btnRefreshData->setObjectName(QString::fromUtf8("btnRefreshData"));
        btnRefreshData->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/image/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRefreshData->setIcon(icon13);
        btnRefreshData->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnRefreshData->setAutoRaise(true);

        horizontalLayout_21->addWidget(btnRefreshData);


        verticalLayout_15->addWidget(title);

        stkUserAction = new QStackedWidget(frame_10);
        stkUserAction->setObjectName(QString::fromUtf8("stkUserAction"));
        page_20 = new QWidget();
        page_20->setObjectName(QString::fromUtf8("page_20"));
        verticalLayout_49 = new QVBoxLayout(page_20);
        verticalLayout_49->setSpacing(0);
        verticalLayout_49->setContentsMargins(0, 0, 0, 0);
        verticalLayout_49->setObjectName(QString::fromUtf8("verticalLayout_49"));
        tbUserFileAction = new QTableWidget(page_20);
        if (tbUserFileAction->columnCount() < 4)
            tbUserFileAction->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbUserFileAction->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbUserFileAction->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbUserFileAction->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbUserFileAction->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tbUserFileAction->setObjectName(QString::fromUtf8("tbUserFileAction"));
        tbUserFileAction->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbUserFileAction{\n"
"	border:1px solid #cccccc;	\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbUserFileAction->setFrameShape(QFrame::NoFrame);
        tbUserFileAction->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUserFileAction->setSelectionMode(QAbstractItemView::SingleSelection);
        tbUserFileAction->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUserFileAction->setShowGrid(false);
        tbUserFileAction->setSortingEnabled(false);
        tbUserFileAction->horizontalHeader()->setDefaultSectionSize(200);
        tbUserFileAction->horizontalHeader()->setHighlightSections(false);
        tbUserFileAction->horizontalHeader()->setMinimumSectionSize(20);
        tbUserFileAction->horizontalHeader()->setStretchLastSection(true);
        tbUserFileAction->verticalHeader()->setVisible(false);
        tbUserFileAction->verticalHeader()->setDefaultSectionSize(20);
        tbUserFileAction->verticalHeader()->setHighlightSections(false);
        tbUserFileAction->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_49->addWidget(tbUserFileAction);

        stkUserAction->addWidget(page_20);
        page_21 = new QWidget();
        page_21->setObjectName(QString::fromUtf8("page_21"));
        verticalLayout_50 = new QVBoxLayout(page_21);
        verticalLayout_50->setSpacing(0);
        verticalLayout_50->setContentsMargins(0, 0, 0, 0);
        verticalLayout_50->setObjectName(QString::fromUtf8("verticalLayout_50"));
        tbKeyboardRecord = new PageTableWidget(page_21);
        tbKeyboardRecord->setObjectName(QString::fromUtf8("tbKeyboardRecord"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tbKeyboardRecord->sizePolicy().hasHeightForWidth());
        tbKeyboardRecord->setSizePolicy(sizePolicy);

        verticalLayout_50->addWidget(tbKeyboardRecord);

        label_3 = new QLabel(page_21);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 30));
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_50->addWidget(label_3);

        edtKeyboardRecordDetail = new QTextEdit(page_21);
        edtKeyboardRecordDetail->setObjectName(QString::fromUtf8("edtKeyboardRecordDetail"));
        edtKeyboardRecordDetail->setMaximumSize(QSize(16777215, 120));
        edtKeyboardRecordDetail->setStyleSheet(QString::fromUtf8("QTextEdit\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));
        edtKeyboardRecordDetail->setReadOnly(true);

        verticalLayout_50->addWidget(edtKeyboardRecordDetail);

        stkUserAction->addWidget(page_21);
        page_22 = new QWidget();
        page_22->setObjectName(QString::fromUtf8("page_22"));
        verticalLayout_52 = new QVBoxLayout(page_22);
        verticalLayout_52->setSpacing(0);
        verticalLayout_52->setContentsMargins(0, 0, 0, 0);
        verticalLayout_52->setObjectName(QString::fromUtf8("verticalLayout_52"));
        tbPasswordRecord = new QTableWidget(page_22);
        if (tbPasswordRecord->columnCount() < 4)
            tbPasswordRecord->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbPasswordRecord->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbPasswordRecord->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbPasswordRecord->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbPasswordRecord->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        tbPasswordRecord->setObjectName(QString::fromUtf8("tbPasswordRecord"));
        tbPasswordRecord->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbPasswordRecord{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbPasswordRecord->setFrameShape(QFrame::NoFrame);
        tbPasswordRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbPasswordRecord->setSelectionMode(QAbstractItemView::SingleSelection);
        tbPasswordRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbPasswordRecord->setShowGrid(false);
        tbPasswordRecord->setSortingEnabled(false);
        tbPasswordRecord->horizontalHeader()->setDefaultSectionSize(150);
        tbPasswordRecord->horizontalHeader()->setHighlightSections(false);
        tbPasswordRecord->horizontalHeader()->setStretchLastSection(true);
        tbPasswordRecord->verticalHeader()->setVisible(false);
        tbPasswordRecord->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_52->addWidget(tbPasswordRecord);

        label_4 = new QLabel(page_22);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 30));
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_52->addWidget(label_4);

        edtPasswordDetail = new QTextEdit(page_22);
        edtPasswordDetail->setObjectName(QString::fromUtf8("edtPasswordDetail"));
        edtPasswordDetail->setMaximumSize(QSize(16777215, 120));
        edtPasswordDetail->setStyleSheet(QString::fromUtf8("QTextEdit\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}"));
        edtPasswordDetail->setReadOnly(true);

        verticalLayout_52->addWidget(edtPasswordDetail);

        stkUserAction->addWidget(page_22);
        page_23 = new QWidget();
        page_23->setObjectName(QString::fromUtf8("page_23"));
        verticalLayout_54 = new QVBoxLayout(page_23);
        verticalLayout_54->setSpacing(0);
        verticalLayout_54->setContentsMargins(0, 0, 0, 0);
        verticalLayout_54->setObjectName(QString::fromUtf8("verticalLayout_54"));
        tbClipboardData = new QTableWidget(page_23);
        if (tbClipboardData->columnCount() < 4)
            tbClipboardData->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbClipboardData->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbClipboardData->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbClipboardData->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbClipboardData->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        tbClipboardData->setObjectName(QString::fromUtf8("tbClipboardData"));
        tbClipboardData->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbClipboardData{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbClipboardData->setFrameShape(QFrame::NoFrame);
        tbClipboardData->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbClipboardData->setSelectionMode(QAbstractItemView::SingleSelection);
        tbClipboardData->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbClipboardData->setShowGrid(false);
        tbClipboardData->setSortingEnabled(false);
        tbClipboardData->horizontalHeader()->setDefaultSectionSize(150);
        tbClipboardData->horizontalHeader()->setHighlightSections(false);
        tbClipboardData->horizontalHeader()->setStretchLastSection(true);
        tbClipboardData->verticalHeader()->setVisible(false);
        tbClipboardData->verticalHeader()->setDefaultSectionSize(20);
        tbClipboardData->verticalHeader()->setHighlightSections(false);

        verticalLayout_54->addWidget(tbClipboardData);

        label_5 = new QLabel(page_23);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 30));
        label_5->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_54->addWidget(label_5);

        edtClipboardDataDetail = new QTextEdit(page_23);
        edtClipboardDataDetail->setObjectName(QString::fromUtf8("edtClipboardDataDetail"));
        edtClipboardDataDetail->setMaximumSize(QSize(16777215, 120));
        edtClipboardDataDetail->setStyleSheet(QString::fromUtf8("QTextEdit\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}"));
        edtClipboardDataDetail->setReadOnly(true);

        verticalLayout_54->addWidget(edtClipboardDataDetail);

        stkUserAction->addWidget(page_23);
        page_24 = new QWidget();
        page_24->setObjectName(QString::fromUtf8("page_24"));
        verticalLayout_56 = new QVBoxLayout(page_24);
        verticalLayout_56->setSpacing(6);
        verticalLayout_56->setContentsMargins(0, 0, 0, 0);
        verticalLayout_56->setObjectName(QString::fromUtf8("verticalLayout_56"));
        tbFileAccessRecord = new QTableWidget(page_24);
        if (tbFileAccessRecord->columnCount() < 6)
            tbFileAccessRecord->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(4, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbFileAccessRecord->setHorizontalHeaderItem(5, __qtablewidgetitem17);
        tbFileAccessRecord->setObjectName(QString::fromUtf8("tbFileAccessRecord"));
        tbFileAccessRecord->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbFileAccessRecord{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbFileAccessRecord->setFrameShape(QFrame::NoFrame);
        tbFileAccessRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbFileAccessRecord->setSelectionMode(QAbstractItemView::SingleSelection);
        tbFileAccessRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbFileAccessRecord->setShowGrid(false);
        tbFileAccessRecord->setSortingEnabled(false);
        tbFileAccessRecord->horizontalHeader()->setDefaultSectionSize(100);
        tbFileAccessRecord->horizontalHeader()->setHighlightSections(false);
        tbFileAccessRecord->horizontalHeader()->setStretchLastSection(true);
        tbFileAccessRecord->verticalHeader()->setVisible(false);
        tbFileAccessRecord->verticalHeader()->setDefaultSectionSize(20);
        tbFileAccessRecord->verticalHeader()->setHighlightSections(false);

        verticalLayout_56->addWidget(tbFileAccessRecord);

        stkUserAction->addWidget(page_24);
        page_25 = new QWidget();
        page_25->setObjectName(QString::fromUtf8("page_25"));
        verticalLayout_57 = new QVBoxLayout(page_25);
        verticalLayout_57->setSpacing(6);
        verticalLayout_57->setContentsMargins(0, 0, 0, 0);
        verticalLayout_57->setObjectName(QString::fromUtf8("verticalLayout_57"));
        tbCommandRecord = new QTableWidget(page_25);
        if (tbCommandRecord->columnCount() < 4)
            tbCommandRecord->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbCommandRecord->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbCommandRecord->setHorizontalHeaderItem(1, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbCommandRecord->setHorizontalHeaderItem(2, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tbCommandRecord->setHorizontalHeaderItem(3, __qtablewidgetitem21);
        tbCommandRecord->setObjectName(QString::fromUtf8("tbCommandRecord"));
        tbCommandRecord->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbCommandRecord{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbCommandRecord->setFrameShape(QFrame::NoFrame);
        tbCommandRecord->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbCommandRecord->setSelectionMode(QAbstractItemView::SingleSelection);
        tbCommandRecord->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbCommandRecord->setShowGrid(false);
        tbCommandRecord->setSortingEnabled(false);
        tbCommandRecord->horizontalHeader()->setDefaultSectionSize(150);
        tbCommandRecord->horizontalHeader()->setStretchLastSection(true);
        tbCommandRecord->verticalHeader()->setVisible(false);
        tbCommandRecord->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_57->addWidget(tbCommandRecord);

        stkUserAction->addWidget(page_25);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        verticalLayout_13 = new QVBoxLayout(page_4);
        verticalLayout_13->setSpacing(0);
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        tbMessageInfo = new QTableWidget(page_4);
        if (tbMessageInfo->columnCount() < 5)
            tbMessageInfo->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tbMessageInfo->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tbMessageInfo->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tbMessageInfo->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbMessageInfo->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbMessageInfo->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        tbMessageInfo->setObjectName(QString::fromUtf8("tbMessageInfo"));
        tbMessageInfo->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbMessageInfo{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" "
                        "}\n"
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
        tbMessageInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbMessageInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        tbMessageInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbMessageInfo->setShowGrid(false);
        tbMessageInfo->setSortingEnabled(false);
        tbMessageInfo->horizontalHeader()->setDefaultSectionSize(150);
        tbMessageInfo->horizontalHeader()->setHighlightSections(false);
        tbMessageInfo->horizontalHeader()->setStretchLastSection(true);
        tbMessageInfo->verticalHeader()->setVisible(false);
        tbMessageInfo->verticalHeader()->setDefaultSectionSize(20);
        tbMessageInfo->verticalHeader()->setHighlightSections(false);

        verticalLayout_13->addWidget(tbMessageInfo);

        label_11 = new QLabel(page_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 30));
        label_11->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_13->addWidget(label_11);

        edtMessageInfoDetail = new QTextEdit(page_4);
        edtMessageInfoDetail->setObjectName(QString::fromUtf8("edtMessageInfoDetail"));
        edtMessageInfoDetail->setMaximumSize(QSize(16777215, 120));
        edtMessageInfoDetail->setStyleSheet(QString::fromUtf8("QTextEdit\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));
        edtMessageInfoDetail->setReadOnly(true);

        verticalLayout_13->addWidget(edtMessageInfoDetail);

        stkUserAction->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        verticalLayout_14 = new QVBoxLayout(page_5);
        verticalLayout_14->setSpacing(0);
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        tbCallInfo = new QTableWidget(page_5);
        if (tbCallInfo->columnCount() < 7)
            tbCallInfo->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(3, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(4, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(5, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbCallInfo->setHorizontalHeaderItem(6, __qtablewidgetitem33);
        tbCallInfo->setObjectName(QString::fromUtf8("tbCallInfo"));
        tbCallInfo->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbCallInfo{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
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
        tbCallInfo->setFrameShape(QFrame::NoFrame);
        tbCallInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbCallInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        tbCallInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbCallInfo->setShowGrid(false);
        tbCallInfo->setSortingEnabled(false);
        tbCallInfo->horizontalHeader()->setDefaultSectionSize(150);
        tbCallInfo->horizontalHeader()->setHighlightSections(false);
        tbCallInfo->horizontalHeader()->setStretchLastSection(true);
        tbCallInfo->verticalHeader()->setVisible(false);
        tbCallInfo->verticalHeader()->setDefaultSectionSize(20);
        tbCallInfo->verticalHeader()->setHighlightSections(false);

        verticalLayout_14->addWidget(tbCallInfo);

        stkUserAction->addWidget(page_5);
        page_15 = new QWidget();
        page_15->setObjectName(QString::fromUtf8("page_15"));
        verticalLayout_19 = new QVBoxLayout(page_15);
        verticalLayout_19->setSpacing(0);
        verticalLayout_19->setContentsMargins(0, 0, 0, 0);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        tbAddressBook = new QTableWidget(page_15);
        if (tbAddressBook->columnCount() < 6)
            tbAddressBook->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(3, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(4, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbAddressBook->setHorizontalHeaderItem(5, __qtablewidgetitem39);
        tbAddressBook->setObjectName(QString::fromUtf8("tbAddressBook"));
        tbAddressBook->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbAddressBook{\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" "
                        "}\n"
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
        tbAddressBook->setFrameShape(QFrame::NoFrame);
        tbAddressBook->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbAddressBook->setSelectionMode(QAbstractItemView::SingleSelection);
        tbAddressBook->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbAddressBook->setShowGrid(false);
        tbAddressBook->setSortingEnabled(false);
        tbAddressBook->horizontalHeader()->setDefaultSectionSize(150);
        tbAddressBook->horizontalHeader()->setHighlightSections(false);
        tbAddressBook->horizontalHeader()->setStretchLastSection(true);
        tbAddressBook->verticalHeader()->setVisible(false);
        tbAddressBook->verticalHeader()->setDefaultSectionSize(20);
        tbAddressBook->verticalHeader()->setHighlightSections(false);

        verticalLayout_19->addWidget(tbAddressBook);

        stkUserAction->addWidget(page_15);

        verticalLayout_15->addWidget(stkUserAction);


        horizontalLayout->addWidget(frame_10);


        retranslateUi(UserActionDlg);

        stkUserAction->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UserActionDlg);
    } // setupUi

    void retranslateUi(QWidget *UserActionDlg)
    {
        UserActionDlg->setWindowTitle(QApplication::translate("UserActionDlg", "UserActionDlg", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trUserAction->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("UserActionDlg", "\345\212\237\350\203\275\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trUserAction->isSortingEnabled();
        trUserAction->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trUserAction->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("UserActionDlg", "\347\224\250\346\210\267\346\226\207\344\273\266\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("UserActionDlg", "\345\205\250\351\203\250\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("UserActionDlg", "\346\226\260\345\273\272\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("UserActionDlg", "\345\210\240\351\231\244\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("UserActionDlg", "\346\213\267\350\264\235\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QApplication::translate("UserActionDlg", "\347\247\273\345\212\250\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QApplication::translate("UserActionDlg", "\346\226\260\345\273\272\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem1->child(6);
        ___qtreewidgetitem8->setText(0, QApplication::translate("UserActionDlg", "\345\210\240\351\231\244\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = trUserAction->topLevelItem(1);
        ___qtreewidgetitem9->setText(0, QApplication::translate("UserActionDlg", "\347\224\250\346\210\267\346\225\217\346\204\237\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem9->child(0);
        ___qtreewidgetitem10->setText(0, QApplication::translate("UserActionDlg", "\351\224\256\347\233\230\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem9->child(1);
        ___qtreewidgetitem11->setText(0, QApplication::translate("UserActionDlg", "\345\257\206\347\240\201\347\252\227\345\217\243\346\204\237\347\237\245", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem9->child(2);
        ___qtreewidgetitem12->setText(0, QApplication::translate("UserActionDlg", "\345\211\252\345\210\207\346\235\277\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = trUserAction->topLevelItem(2);
        ___qtreewidgetitem13->setText(0, QApplication::translate("UserActionDlg", "\350\277\233\347\250\213\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(0, QApplication::translate("UserActionDlg", "\346\226\207\344\273\266\350\256\277\351\227\256", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem13->child(1);
        ___qtreewidgetitem15->setText(0, QApplication::translate("UserActionDlg", "\346\211\247\350\241\214\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem16 = trUserAction->topLevelItem(3);
        ___qtreewidgetitem16->setText(0, QApplication::translate("UserActionDlg", "\351\200\232\350\256\257\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(0, QApplication::translate("UserActionDlg", "\347\237\255\344\277\241\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem16->child(1);
        ___qtreewidgetitem18->setText(0, QApplication::translate("UserActionDlg", "\351\200\232\350\257\235\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem16->child(2);
        ___qtreewidgetitem19->setText(0, QApplication::translate("UserActionDlg", "\351\200\232\350\256\257\345\275\225", 0, QApplication::UnicodeUTF8));
        trUserAction->setSortingEnabled(__sortingEnabled);

        lbUserAction->setText(QApplication::translate("UserActionDlg", "\347\224\250\346\210\267\346\225\217\346\204\237\350\241\214\344\270\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnRefreshData->setToolTip(QApplication::translate("UserActionDlg", "\345\210\267\346\226\260\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnRefreshData->setText(QApplication::translate("UserActionDlg", "\345\210\267\346\226\260\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbUserFileAction->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbUserFileAction->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UserActionDlg", "\345\212\250\344\275\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbUserFileAction->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("UserActionDlg", "\346\226\207\344\273\266\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbUserFileAction->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("UserActionDlg", "\347\233\256\346\240\207\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UserActionDlg", "\350\257\246\347\273\206\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbPasswordRecord->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbPasswordRecord->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbPasswordRecord->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbPasswordRecord->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QApplication::translate("UserActionDlg", "\347\252\227\345\217\243\346\240\207\351\242\230", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UserActionDlg", "\350\257\246\347\273\206\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbClipboardData->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbClipboardData->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbClipboardData->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbClipboardData->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("UserActionDlg", "\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UserActionDlg", "\350\257\246\347\273\206\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbFileAccessRecord->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbFileAccessRecord->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbFileAccessRecord->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tbFileAccessRecord->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QApplication::translate("UserActionDlg", "\345\212\250\344\275\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tbFileAccessRecord->horizontalHeaderItem(4);
        ___qtablewidgetitem16->setText(QApplication::translate("UserActionDlg", "\346\226\207\344\273\266\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tbFileAccessRecord->horizontalHeaderItem(5);
        ___qtablewidgetitem17->setText(QApplication::translate("UserActionDlg", "\347\233\256\346\240\207\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbCommandRecord->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbCommandRecord->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbCommandRecord->horizontalHeaderItem(2);
        ___qtablewidgetitem20->setText(QApplication::translate("UserActionDlg", "\350\277\233\347\250\213\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbCommandRecord->horizontalHeaderItem(3);
        ___qtablewidgetitem21->setText(QApplication::translate("UserActionDlg", "\345\221\275\344\273\244\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbMessageInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem22->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbMessageInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem23->setText(QApplication::translate("UserActionDlg", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tbMessageInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem24->setText(QApplication::translate("UserActionDlg", "\350\201\224\347\263\273\344\272\272", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tbMessageInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem25->setText(QApplication::translate("UserActionDlg", "\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbMessageInfo->horizontalHeaderItem(4);
        ___qtablewidgetitem26->setText(QApplication::translate("UserActionDlg", "\350\216\267\345\217\226\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("UserActionDlg", "\350\257\246\347\273\206\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tbCallInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("UserActionDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tbCallInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem28->setText(QApplication::translate("UserActionDlg", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tbCallInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem29->setText(QApplication::translate("UserActionDlg", "\350\201\224\347\263\273\344\272\272", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tbCallInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem30->setText(QApplication::translate("UserActionDlg", "\347\275\221\347\273\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tbCallInfo->horizontalHeaderItem(4);
        ___qtablewidgetitem31->setText(QApplication::translate("UserActionDlg", "\345\275\222\345\261\236\345\234\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tbCallInfo->horizontalHeaderItem(5);
        ___qtablewidgetitem32->setText(QApplication::translate("UserActionDlg", "\351\200\232\350\257\235\346\227\266\351\225\277", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tbCallInfo->horizontalHeaderItem(6);
        ___qtablewidgetitem33->setText(QApplication::translate("UserActionDlg", "\350\216\267\345\217\226\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tbAddressBook->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("UserActionDlg", "\350\201\224\347\263\273\344\272\272", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tbAddressBook->horizontalHeaderItem(1);
        ___qtablewidgetitem35->setText(QApplication::translate("UserActionDlg", "\347\224\265\350\257\235", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tbAddressBook->horizontalHeaderItem(2);
        ___qtablewidgetitem36->setText(QApplication::translate("UserActionDlg", "\345\275\222\345\261\236\345\234\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tbAddressBook->horizontalHeaderItem(3);
        ___qtablewidgetitem37->setText(QApplication::translate("UserActionDlg", "\347\275\221\347\273\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tbAddressBook->horizontalHeaderItem(4);
        ___qtablewidgetitem38->setText(QApplication::translate("UserActionDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = tbAddressBook->horizontalHeaderItem(5);
        ___qtablewidgetitem39->setText(QApplication::translate("UserActionDlg", "\350\216\267\345\217\226\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserActionDlg: public Ui_UserActionDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERACTIONDLG_H
