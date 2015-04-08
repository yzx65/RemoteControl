/********************************************************************************
** Form generated from reading UI file 'AppInfoDlg.ui'
**
** Created: Wed Apr 8 14:23:31 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPINFODLG_H
#define UI_APPINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppInfoDlg
{
public:
    QVBoxLayout *verticalLayout_5;
    QFrame *toolbar;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *btnGetData;
    QToolButton *btnRefresh;
    QToolButton *btnClean;
    QToolButton *btnExport;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *lstApplication;
    QStackedWidget *stkApplicationInfo;
    QWidget *page;
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QComboBox *cmbWeixinAccount;
    QSpacerItem *horizontalSpacer_3;
    QSplitter *splitter;
    QTreeWidget *trWeixinFriends;
    QTextBrowser *edtWeixinChactHistory;
    QWidget *framexxx;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *cmbQQAccount;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_2;
    QTreeWidget *trQQFriends;
    QTextBrowser *edtQQChatHistory;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QTreeWidget *trQQTroops;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QTextEdit *edtTroopMemo;
    QTextBrowser *edtQQTroopHistory;

    void setupUi(QDialog *AppInfoDlg)
    {
        if (AppInfoDlg->objectName().isEmpty())
            AppInfoDlg->setObjectName(QString::fromUtf8("AppInfoDlg"));
        AppInfoDlg->resize(1126, 666);
        AppInfoDlg->setStyleSheet(QString::fromUtf8("QWidget#AppInfoDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(AppInfoDlg);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        toolbar = new QFrame(AppInfoDlg);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        toolbar->setMinimumSize(QSize(0, 0));
        toolbar->setStyleSheet(QString::fromUtf8("QFrame#toolbar\n"
"{\n"
"	background-color:rgb(239,241,250);\n"
"	border:0px solid #cccccc;\n"
"	color:#333333;\n"
"	border-bottom-width:1px;\n"
"}"));
        toolbar->setFrameShape(QFrame::StyledPanel);
        toolbar->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(toolbar);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnGetData = new QToolButton(toolbar);
        btnGetData->setObjectName(QString::fromUtf8("btnGetData"));
        btnGetData->setMinimumSize(QSize(115, 40));
        btnGetData->setMaximumSize(QSize(115, 40));
        btnGetData->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border:0px solid #aaaaaa;\n"
"	color:#555555;\n"
"	padding-left:5px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"	margin:1px;\n"
"}\n"
"\n"
"QToolButton:disabled\n"
"{\n"
"	color:#aaaaaa;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/autoget.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnGetData->setIcon(icon);
        btnGetData->setIconSize(QSize(16, 16));
        btnGetData->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(btnGetData);

        btnRefresh = new QToolButton(toolbar);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setMinimumSize(QSize(115, 40));
        btnRefresh->setMaximumSize(QSize(115, 40));
        btnRefresh->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border:0px solid #aaaaaa;\n"
"	color:#333333;\n"
"	padding-left:5px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"	margin:1px;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRefresh->setIcon(icon1);
        btnRefresh->setIconSize(QSize(16, 16));
        btnRefresh->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(btnRefresh);

        btnClean = new QToolButton(toolbar);
        btnClean->setObjectName(QString::fromUtf8("btnClean"));
        btnClean->setMinimumSize(QSize(115, 40));
        btnClean->setMaximumSize(QSize(115, 40));
        btnClean->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border:0px solid #aaaaaa;\n"
"	color:#333333;\n"
"	padding-left:5px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"	margin:1px;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClean->setIcon(icon2);
        btnClean->setIconSize(QSize(16, 16));
        btnClean->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(btnClean);

        btnExport = new QToolButton(toolbar);
        btnExport->setObjectName(QString::fromUtf8("btnExport"));
        btnExport->setMinimumSize(QSize(115, 40));
        btnExport->setMaximumSize(QSize(115, 40));
        btnExport->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border:0px solid #aaaaaa;\n"
"	color:#333333;\n"
"	padding-left:5px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"	margin:1px;\n"
"}"));
        btnExport->setIcon(icon);
        btnExport->setIconSize(QSize(16, 16));
        btnExport->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_5->addWidget(btnExport);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_5->addWidget(toolbar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstApplication = new QListWidget(AppInfoDlg);
        lstApplication->setObjectName(QString::fromUtf8("lstApplication"));
        lstApplication->setMaximumSize(QSize(200, 16777215));
        lstApplication->setFocusPolicy(Qt::NoFocus);
        lstApplication->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	/*border-right-width:0xp;*/\n"
"	font-size:13px;\n"
"	border-top-width:0px;\n"
"	border-bottom-width:0px;\n"
"	background-color:rgb(240,240,240);\n"
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
        lstApplication->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(lstApplication);

        stkApplicationInfo = new QStackedWidget(AppInfoDlg);
        stkApplicationInfo->setObjectName(QString::fromUtf8("stkApplicationInfo"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_6 = new QVBoxLayout(page);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        frame_3 = new QFrame(page);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_6 = new QHBoxLayout(frame_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, -1, -1, -1);
        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	min-height:25px;\n"
"}"));

        horizontalLayout_6->addWidget(label_3);

        cmbWeixinAccount = new QComboBox(frame_3);
        cmbWeixinAccount->setObjectName(QString::fromUtf8("cmbWeixinAccount"));
        cmbWeixinAccount->setMinimumSize(QSize(402, 27));
        cmbWeixinAccount->setMaximumSize(QSize(400, 16777215));
        cmbWeixinAccount->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"	background-color:white;\n"
"	border:1px solid #aaaaaa;\n"
"	min-width:400px;\n"
"	min-height:25px;\n"
"	font-size:13px;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	color:black;\n"
"}\n"
"\n"
"QComboBox:hover\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
"QComboBox:on\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"	 border:0px solid rgb(46,52,52);\n"
" }\n"
"\n"
"QComboBox::down-arrow {\n"
"	height:8px;\n"
"	width:5px;\n"
"	image: url(:/image/arrow.png);\n"
" }\n"
"\n"
" QComboBox QAbstractItemView\n"
"{\n"
"	border:1px solid #eef0ff;\n"
"}"));

        horizontalLayout_6->addWidget(cmbWeixinAccount);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout_6->addWidget(frame_3);

        splitter = new QSplitter(page);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        splitter->setOrientation(Qt::Vertical);
        trWeixinFriends = new QTreeWidget(splitter);
        trWeixinFriends->setObjectName(QString::fromUtf8("trWeixinFriends"));
        trWeixinFriends->setMaximumSize(QSize(9999, 16777215));
        trWeixinFriends->setFocusPolicy(Qt::NoFocus);
        trWeixinFriends->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"    padding-left: 10px;\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trWeixinFriends{\n"
"	border:1px solid #cccccc;;\n"
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
"     background: "
                        "#aaaaaa;\n"
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trWeixinFriends->setIconSize(QSize(24, 24));
        trWeixinFriends->setIndentation(0);
        trWeixinFriends->setRootIsDecorated(false);
        splitter->addWidget(trWeixinFriends);
        trWeixinFriends->header()->setDefaultSectionSize(400);
        edtWeixinChactHistory = new QTextBrowser(splitter);
        edtWeixinChactHistory->setObjectName(QString::fromUtf8("edtWeixinChactHistory"));
        edtWeixinChactHistory->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"}\n"
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
"	bac"
                        "kground:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        edtWeixinChactHistory->setReadOnly(true);
        edtWeixinChactHistory->setOpenExternalLinks(false);
        edtWeixinChactHistory->setOpenLinks(false);
        splitter->addWidget(edtWeixinChactHistory);

        verticalLayout_6->addWidget(splitter);

        stkApplicationInfo->addWidget(page);
        framexxx = new QWidget();
        framexxx->setObjectName(QString::fromUtf8("framexxx"));
        framexxx->setStyleSheet(QString::fromUtf8("QFrame#framexxx\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout = new QVBoxLayout(framexxx);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(framexxx);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, -1, -1, -1);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	min-height:25px;\n"
"}"));

        horizontalLayout_3->addWidget(label);

        cmbQQAccount = new QComboBox(frame);
        cmbQQAccount->setObjectName(QString::fromUtf8("cmbQQAccount"));
        cmbQQAccount->setMinimumSize(QSize(152, 27));
        cmbQQAccount->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"	background-color:white;\n"
"	border:1px solid #aaaaaa;\n"
"	min-width:150px;\n"
"	min-height:25px;\n"
"	font-size:13px;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	color:black;\n"
"}\n"
"\n"
"QComboBox:hover\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
"QComboBox:on\n"
"{\n"
"	background-color:#cccccc;\n"
"}\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"\n"
"	 border:0px solid rgb(46,52,52);\n"
" }\n"
"\n"
"QComboBox::down-arrow {\n"
"	height:8px;\n"
"	width:5px;\n"
"	image: url(:/image/arrow.png);\n"
" }\n"
"\n"
" QComboBox QAbstractItemView\n"
"{\n"
"	border:1px solid #eef0ff;\n"
"}"));

        horizontalLayout_3->addWidget(cmbQQAccount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame);

        tabWidget = new QTabWidget(framexxx);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8("QTabWidget::pane\n"
"{\n"
"    border-width:0px;\n"
"    border-style:solid;\n"
"    border-color:white;\n"
"	background-color:white;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: white;\n"
"	color:black;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	min-height:30px;\n"
"	min-width:120px;\n"
"	border:1px solid #cccccc;\n"
" }\n"
"\n"
"QTabBar::tab:hover {\n"
"     background: rgb(122,141,217);\n"
"	 color:white;\n"
"	 border:none;\n"
" }\n"
"\n"
"QTabBar::tab:selected {\n"
"     background: rgb(88,115,201);\n"
"	color:white;\n"
"     border:none;\n"
" }\n"
"\n"
"\n"
""));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 9, 0, 0);
        splitter_2 = new QSplitter(tab);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        splitter_2->setOrientation(Qt::Vertical);
        trQQFriends = new QTreeWidget(splitter_2);
        new QTreeWidgetItem(trQQFriends);
        trQQFriends->setObjectName(QString::fromUtf8("trQQFriends"));
        trQQFriends->setMaximumSize(QSize(15000, 16777215));
        trQQFriends->setFocusPolicy(Qt::NoFocus);
        trQQFriends->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"    padding-left: 10px;\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trQQFriends{\n"
"	border:1px solid #cccccc;;\n"
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
"     background: #aaa"
                        "aaa;\n"
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trQQFriends->setFrameShape(QFrame::NoFrame);
        trQQFriends->setIconSize(QSize(24, 24));
        splitter_2->addWidget(trQQFriends);
        trQQFriends->header()->setDefaultSectionSize(150);
        edtQQChatHistory = new QTextBrowser(splitter_2);
        edtQQChatHistory->setObjectName(QString::fromUtf8("edtQQChatHistory"));
        edtQQChatHistory->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
""
                        "	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        edtQQChatHistory->setReadOnly(true);
        edtQQChatHistory->setOpenLinks(false);
        splitter_2->addWidget(edtQQChatHistory);

        verticalLayout_2->addWidget(splitter_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, -1, 0, 0);
        splitter_3 = new QSplitter(tab_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:white;\n"
"}"));
        splitter_3->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(splitter_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        trQQTroops = new QTreeWidget(layoutWidget);
        trQQTroops->setObjectName(QString::fromUtf8("trQQTroops"));
        trQQTroops->setMaximumSize(QSize(9999, 16777215));
        trQQTroops->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView \n"
"{\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	background-color:#eef0ff;\n"
"	color:black;\n"
"}\n"
"QHeaderView::section \n"
"{\n"
"	background-color:#eef0ff;\n"
"	color:#333333;\n"
"	min-height:30px;\n"
"	border-width:0px;\n"
"	border-style:solid;\n"
"	padding-left:5px;\n"
"	border-color:#cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-top-width:0px;\n"
"}\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trQQTroops{\n"
"	border:1px solid #cccccc;\n"
"	border-top-width:1px;\n"
"	border-left-width:1px;\n"
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
"     background: #cccccc;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
""
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trQQTroops->setFrameShape(QFrame::NoFrame);
        trQQTroops->setIconSize(QSize(24, 24));
        trQQTroops->setIndentation(0);

        horizontalLayout_4->addWidget(trQQTroops);

        frame_2 = new QFrame(layoutWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:#eef0ff;\n"
"	color:#333333;\n"
"	border:1px solid #cccccc;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"}"));

        verticalLayout_4->addWidget(label_2);

        edtTroopMemo = new QTextEdit(frame_2);
        edtTroopMemo->setObjectName(QString::fromUtf8("edtTroopMemo"));
        edtTroopMemo->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border-top-width:0px;\n"
"}"));

        verticalLayout_4->addWidget(edtTroopMemo);


        horizontalLayout_4->addWidget(frame_2);

        splitter_3->addWidget(layoutWidget);
        edtQQTroopHistory = new QTextBrowser(splitter_3);
        edtQQTroopHistory->setObjectName(QString::fromUtf8("edtQQTroopHistory"));
        edtQQTroopHistory->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
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
" QScrollBar::add-line:horizontal {\n"
"	border:none;\n"
""
                        "	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        edtQQTroopHistory->setReadOnly(true);
        edtQQTroopHistory->setOpenLinks(false);
        splitter_3->addWidget(edtQQTroopHistory);

        verticalLayout_3->addWidget(splitter_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        stkApplicationInfo->addWidget(framexxx);

        horizontalLayout->addWidget(stkApplicationInfo);


        verticalLayout_5->addLayout(horizontalLayout);


        retranslateUi(AppInfoDlg);

        stkApplicationInfo->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AppInfoDlg);
    } // setupUi

    void retranslateUi(QDialog *AppInfoDlg)
    {
        AppInfoDlg->setWindowTitle(QApplication::translate("AppInfoDlg", "\345\256\211\345\215\223\350\201\212\345\244\251\350\256\260\345\275\225\346\237\245\347\234\213\345\231\250", 0, QApplication::UnicodeUTF8));
        btnGetData->setText(QApplication::translate("AppInfoDlg", " \350\216\267\345\217\226\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        btnGetData->setShortcut(QApplication::translate("AppInfoDlg", "1", 0, QApplication::UnicodeUTF8));
        btnRefresh->setText(QApplication::translate("AppInfoDlg", " \345\210\267\346\226\260\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        btnClean->setText(QApplication::translate("AppInfoDlg", " \346\270\205\347\251\272\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        btnExport->setText(QApplication::translate("AppInfoDlg", " \345\257\274\345\207\272\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AppInfoDlg", "\345\275\223\345\211\215\350\264\246\345\217\267\357\274\232 ", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trWeixinFriends->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("AppInfoDlg", "\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("AppInfoDlg", "\346\230\265\347\247\260", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("AppInfoDlg", "\347\224\250\346\210\267 id", 0, QApplication::UnicodeUTF8));
        edtWeixinChactHistory->setHtml(QApplication::translate("AppInfoDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft Yahei'; font-size:13px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AppInfoDlg", "\345\275\223\345\211\215\350\264\246\345\217\267\357\274\232 ", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = trQQFriends->headerItem();
        ___qtreewidgetitem1->setText(3, QApplication::translate("AppInfoDlg", "\347\255\276\345\220\215", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(2, QApplication::translate("AppInfoDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(1, QApplication::translate("AppInfoDlg", "\346\230\265\347\247\260", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("AppInfoDlg", "QQ\345\217\267", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trQQFriends->isSortingEnabled();
        trQQFriends->setSortingEnabled(false);
        trQQFriends->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("AppInfoDlg", "\345\245\275\345\217\213", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = trQQTroops->headerItem();
        ___qtreewidgetitem2->setText(1, QApplication::translate("AppInfoDlg", "\347\276\244\345\220\215", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("AppInfoDlg", "\347\276\244\345\217\267", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AppInfoDlg", "\347\276\244\345\205\254\345\221\212", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("AppInfoDlg", "QQ \347\276\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AppInfoDlg: public Ui_AppInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPINFODLG_H
