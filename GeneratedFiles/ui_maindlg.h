/********************************************************************************
** Form generated from reading UI file 'maindlg.ui'
**
** Created: Sun Sep 20 11:18:01 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDLG_H
#define UI_MAINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDlgClass
{
public:
    QAction *actStart;
    QAction *actStop;
    QAction *actExit;
    QAction *actConfig;
    QAction *actScreenMon;
    QAction *actLog;
    QAction *actAlias;
    QAction *actDelSelf;
    QAction *actClean;
    QAction *actCreate;
    QAction *actHelp;
    QAction *actAbout;
    QAction *actUserActionMonitor;
    QAction *actUsbMonitor;
    QAction *actCleanDatabase;
    QAction *actCreateDaemon;
    QAction *actPolicy;
    QAction *actMigrateDaemon;
    QAction *actFlowControl;
    QAction *actFavorite;
    QAction *actQueryDaemonAddress;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_8;
    QTreeWidget *trTarget;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame_target_info;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QTableWidget *tbBasicInfo;
    QFrame *logFrame;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QFrame *basic_info;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_7;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_001;
    QLabel *label_001_content;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_002;
    QLabel *label_002_content;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_003;
    QLabel *label_003_content;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_004;
    QLabel *label_004_content;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_005;
    QLabel *label_005_content;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_006;
    QLabel *label_006_content;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_007;
    QLabel *label_007_content;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_008;
    QLabel *label_008_content;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_009;
    QLabel *label_009_content;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_010;
    QLabel *label_010_content;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_7;
    QTextEdit *edtLog;
    QFrame *pluginStatus;
    QVBoxLayout *verticalLayout_5;
    QFrame *displayMode;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lbTargetCount;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *lbOnlineTargetCount;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *cmbDisplayMode;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QComboBox *cmbCategory;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QTableWidget *tbPluginStatus;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_T;
    QMenu *menu_S;
    QMenu *menu_H;

    void setupUi(QMainWindow *MainDlgClass)
    {
        if (MainDlgClass->objectName().isEmpty())
            MainDlgClass->setObjectName(QString::fromUtf8("MainDlgClass"));
        MainDlgClass->resize(1375, 830);
        MainDlgClass->setStyleSheet(QString::fromUtf8(""));
        actStart = new QAction(MainDlgClass);
        actStart->setObjectName(QString::fromUtf8("actStart"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("image/toolbar/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8("image/toolbar/start_disabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actStart->setIcon(icon);
        actStop = new QAction(MainDlgClass);
        actStop->setObjectName(QString::fromUtf8("actStop"));
        actStop->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("image/toolbar/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("image/toolbar/stop_disable.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actStop->setIcon(icon1);
        actExit = new QAction(MainDlgClass);
        actExit->setObjectName(QString::fromUtf8("actExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("image/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actExit->setIcon(icon2);
        actConfig = new QAction(MainDlgClass);
        actConfig->setObjectName(QString::fromUtf8("actConfig"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("image/toolbar/config.png"), QSize(), QIcon::Normal, QIcon::Off);
        actConfig->setIcon(icon3);
        actScreenMon = new QAction(MainDlgClass);
        actScreenMon->setObjectName(QString::fromUtf8("actScreenMon"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("image/pcname.png"), QSize(), QIcon::Normal, QIcon::Off);
        actScreenMon->setIcon(icon4);
        actLog = new QAction(MainDlgClass);
        actLog->setObjectName(QString::fromUtf8("actLog"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("image/updownlog.png"), QSize(), QIcon::Normal, QIcon::Off);
        actLog->setIcon(icon5);
        actAlias = new QAction(MainDlgClass);
        actAlias->setObjectName(QString::fromUtf8("actAlias"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("image/toolbar/alias.png"), QSize(), QIcon::Normal, QIcon::Off);
        actAlias->setIcon(icon6);
        actDelSelf = new QAction(MainDlgClass);
        actDelSelf->setObjectName(QString::fromUtf8("actDelSelf"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("image/destroy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actDelSelf->setIcon(icon7);
        actClean = new QAction(MainDlgClass);
        actClean->setObjectName(QString::fromUtf8("actClean"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("image/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actClean->setIcon(icon8);
        actCreate = new QAction(MainDlgClass);
        actCreate->setObjectName(QString::fromUtf8("actCreate"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("image/toolbar/target.png"), QSize(), QIcon::Normal, QIcon::Off);
        actCreate->setIcon(icon9);
        actHelp = new QAction(MainDlgClass);
        actHelp->setObjectName(QString::fromUtf8("actHelp"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("image/unknown.png"), QSize(), QIcon::Normal, QIcon::Off);
        actHelp->setIcon(icon10);
        actAbout = new QAction(MainDlgClass);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        actUserActionMonitor = new QAction(MainDlgClass);
        actUserActionMonitor->setObjectName(QString::fromUtf8("actUserActionMonitor"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("image/useraction.png"), QSize(), QIcon::Normal, QIcon::Off);
        actUserActionMonitor->setIcon(icon11);
        actUsbMonitor = new QAction(MainDlgClass);
        actUsbMonitor->setObjectName(QString::fromUtf8("actUsbMonitor"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("image/usbplugrecord.png"), QSize(), QIcon::Normal, QIcon::Off);
        actUsbMonitor->setIcon(icon12);
        actCleanDatabase = new QAction(MainDlgClass);
        actCleanDatabase->setObjectName(QString::fromUtf8("actCleanDatabase"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("image/toolbar/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actCleanDatabase->setIcon(icon13);
        actCreateDaemon = new QAction(MainDlgClass);
        actCreateDaemon->setObjectName(QString::fromUtf8("actCreateDaemon"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("image/toolbar/daemon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actCreateDaemon->setIcon(icon14);
        actPolicy = new QAction(MainDlgClass);
        actPolicy->setObjectName(QString::fromUtf8("actPolicy"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("image/toolbar/policy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actPolicy->setIcon(icon15);
        actMigrateDaemon = new QAction(MainDlgClass);
        actMigrateDaemon->setObjectName(QString::fromUtf8("actMigrateDaemon"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("image/toolbar/migrate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actMigrateDaemon->setIcon(icon16);
        actFlowControl = new QAction(MainDlgClass);
        actFlowControl->setObjectName(QString::fromUtf8("actFlowControl"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8("image/toolbar/flow.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon17.addFile(QString::fromUtf8("image/toolbar/flow_disable.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actFlowControl->setIcon(icon17);
        actFavorite = new QAction(MainDlgClass);
        actFavorite->setObjectName(QString::fromUtf8("actFavorite"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8("image/toolbar/star.png"), QSize(), QIcon::Normal, QIcon::Off);
        actFavorite->setIcon(icon18);
        actQueryDaemonAddress = new QAction(MainDlgClass);
        actQueryDaemonAddress->setObjectName(QString::fromUtf8("actQueryDaemonAddress"));
        centralWidget = new QWidget(MainDlgClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(centralWidget);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-top-width:0px;\n"
"}"));

        verticalLayout_3->addWidget(label_8);

        trTarget = new QTreeWidget(centralWidget);
        trTarget->setObjectName(QString::fromUtf8("trTarget"));
        trTarget->setMaximumSize(QSize(200, 16777215));
        trTarget->setStyleSheet(QString::fromUtf8("/* QHeaderView::section {\n"
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
"	background-color:rgb(247,249,255);\n"
"	color:black;\n"
"}\n"
"QHeaderView::section \n"
"{\n"
"	background-color:rgb(247,249,255);\n"
"	color:black;\n"
"	min-height:30px;\n"
"	border-width:0px;\n"
"	border-style:solid;\n"
"	padding-left:5px;\n"
"	border-color:#cccccc;\n"
"	border-bottom-width:1px;\n"
"}\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#trTarget{\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:0px;\n"
"	bo"
                        "rder-top-width:0px;\n"
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
" QScrollBar::a"
                        "dd-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:horizontal {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        trTarget->setFrameShape(QFrame::NoFrame);
        trTarget->setFrameShadow(QFrame::Plain);
        trTarget->setLineWidth(0);
        trTarget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        trTarget->setIconSize(QSize(24, 24));
        trTarget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        trTarget->setIndentation(0);
        trTarget->setSortingEnabled(true);
        trTarget->header()->setCascadingSectionResizes(true);
        trTarget->header()->setDefaultSectionSize(50);
        trTarget->header()->setHighlightSections(false);
        trTarget->header()->setStretchLastSection(true);

        verticalLayout_3->addWidget(trTarget);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame_target_info = new QFrame(centralWidget);
        frame_target_info->setObjectName(QString::fromUtf8("frame_target_info"));
        verticalLayout_2 = new QVBoxLayout(frame_target_info);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(frame_target_info);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(263, 30));
        label_4->setMaximumSize(QSize(263, 16777215));
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:0px;\n"
"	border-top-width:0px;\n"
"}"));

        verticalLayout_2->addWidget(label_4);

        tbBasicInfo = new QTableWidget(frame_target_info);
        if (tbBasicInfo->columnCount() < 2)
            tbBasicInfo->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbBasicInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbBasicInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tbBasicInfo->rowCount() < 5)
            tbBasicInfo->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbBasicInfo->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbBasicInfo->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbBasicInfo->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbBasicInfo->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbBasicInfo->setVerticalHeaderItem(4, __qtablewidgetitem6);
        tbBasicInfo->setObjectName(QString::fromUtf8("tbBasicInfo"));
        tbBasicInfo->setMinimumSize(QSize(263, 0));
        tbBasicInfo->setMaximumSize(QSize(263, 16777215));
        tbBasicInfo->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	text-align:center left;\n"
" }\n"
"QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbBasicInfo{\n"
"	border:1px solid #aaaaaa;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image:none;\n"
"}"));
        tbBasicInfo->setFrameShape(QFrame::NoFrame);
        tbBasicInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbBasicInfo->setSelectionMode(QAbstractItemView::SingleSelection);
        tbBasicInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbBasicInfo->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbBasicInfo->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbBasicInfo->setSortingEnabled(false);
        tbBasicInfo->horizontalHeader()->setVisible(false);
        tbBasicInfo->horizontalHeader()->setHighlightSections(false);
        tbBasicInfo->horizontalHeader()->setStretchLastSection(true);
        tbBasicInfo->verticalHeader()->setVisible(false);
        tbBasicInfo->verticalHeader()->setDefaultSectionSize(25);
        tbBasicInfo->verticalHeader()->setHighlightSections(false);

        verticalLayout_2->addWidget(tbBasicInfo);


        verticalLayout_4->addWidget(frame_target_info);

        logFrame = new QFrame(centralWidget);
        logFrame->setObjectName(QString::fromUtf8("logFrame"));
        verticalLayout = new QVBoxLayout(logFrame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_9 = new QLabel(logFrame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-left-width:0px;\n"
"}"));

        verticalLayout->addWidget(label_9);

        basic_info = new QFrame(logFrame);
        basic_info->setObjectName(QString::fromUtf8("basic_info"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(basic_info->sizePolicy().hasHeightForWidth());
        basic_info->setSizePolicy(sizePolicy);
        basic_info->setMinimumSize(QSize(0, 300));
        basic_info->setStyleSheet(QString::fromUtf8("QFrame#basic_info\n"
"{\n"
"background-color:white;\n"
"}"));
        basic_info->setFrameShape(QFrame::StyledPanel);
        basic_info->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(basic_info);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_6 = new QSpacerItem(82, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        label_10 = new QLabel(basic_info);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_13->addWidget(label_10);

        horizontalSpacer_7 = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_7);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_001 = new QLabel(basic_info);
        label_001->setObjectName(QString::fromUtf8("label_001"));

        horizontalLayout_3->addWidget(label_001);

        label_001_content = new QLabel(basic_info);
        label_001_content->setObjectName(QString::fromUtf8("label_001_content"));

        horizontalLayout_3->addWidget(label_001_content);


        verticalLayout_7->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_002 = new QLabel(basic_info);
        label_002->setObjectName(QString::fromUtf8("label_002"));

        horizontalLayout_4->addWidget(label_002);

        label_002_content = new QLabel(basic_info);
        label_002_content->setObjectName(QString::fromUtf8("label_002_content"));

        horizontalLayout_4->addWidget(label_002_content);


        verticalLayout_7->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_003 = new QLabel(basic_info);
        label_003->setObjectName(QString::fromUtf8("label_003"));

        horizontalLayout_5->addWidget(label_003);

        label_003_content = new QLabel(basic_info);
        label_003_content->setObjectName(QString::fromUtf8("label_003_content"));

        horizontalLayout_5->addWidget(label_003_content);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_004 = new QLabel(basic_info);
        label_004->setObjectName(QString::fromUtf8("label_004"));

        horizontalLayout_6->addWidget(label_004);

        label_004_content = new QLabel(basic_info);
        label_004_content->setObjectName(QString::fromUtf8("label_004_content"));

        horizontalLayout_6->addWidget(label_004_content);


        verticalLayout_7->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_005 = new QLabel(basic_info);
        label_005->setObjectName(QString::fromUtf8("label_005"));

        horizontalLayout_7->addWidget(label_005);

        label_005_content = new QLabel(basic_info);
        label_005_content->setObjectName(QString::fromUtf8("label_005_content"));

        horizontalLayout_7->addWidget(label_005_content);


        verticalLayout_7->addLayout(horizontalLayout_7);


        horizontalLayout_13->addLayout(verticalLayout_7);

        horizontalSpacer_8 = new QSpacerItem(82, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_8);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_006 = new QLabel(basic_info);
        label_006->setObjectName(QString::fromUtf8("label_006"));

        horizontalLayout_8->addWidget(label_006);

        label_006_content = new QLabel(basic_info);
        label_006_content->setObjectName(QString::fromUtf8("label_006_content"));

        horizontalLayout_8->addWidget(label_006_content);


        verticalLayout_8->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_007 = new QLabel(basic_info);
        label_007->setObjectName(QString::fromUtf8("label_007"));

        horizontalLayout_9->addWidget(label_007);

        label_007_content = new QLabel(basic_info);
        label_007_content->setObjectName(QString::fromUtf8("label_007_content"));

        horizontalLayout_9->addWidget(label_007_content);


        verticalLayout_8->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_008 = new QLabel(basic_info);
        label_008->setObjectName(QString::fromUtf8("label_008"));

        horizontalLayout_10->addWidget(label_008);

        label_008_content = new QLabel(basic_info);
        label_008_content->setObjectName(QString::fromUtf8("label_008_content"));

        horizontalLayout_10->addWidget(label_008_content);


        verticalLayout_8->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_009 = new QLabel(basic_info);
        label_009->setObjectName(QString::fromUtf8("label_009"));

        horizontalLayout_11->addWidget(label_009);

        label_009_content = new QLabel(basic_info);
        label_009_content->setObjectName(QString::fromUtf8("label_009_content"));

        horizontalLayout_11->addWidget(label_009_content);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_010 = new QLabel(basic_info);
        label_010->setObjectName(QString::fromUtf8("label_010"));

        horizontalLayout_12->addWidget(label_010);

        label_010_content = new QLabel(basic_info);
        label_010_content->setObjectName(QString::fromUtf8("label_010_content"));

        horizontalLayout_12->addWidget(label_010_content);


        verticalLayout_8->addLayout(horizontalLayout_12);


        horizontalLayout_13->addLayout(verticalLayout_8);

        horizontalSpacer_9 = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_9);


        verticalLayout->addWidget(basic_info);

        label_7 = new QLabel(logFrame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-left-width:0px;\n"
"}"));

        verticalLayout->addWidget(label_7);

        edtLog = new QTextEdit(logFrame);
        edtLog->setObjectName(QString::fromUtf8("edtLog"));
        edtLog->setMaximumSize(QSize(16777215, 300));
        edtLog->setFrameShape(QFrame::NoFrame);
        edtLog->setReadOnly(true);

        verticalLayout->addWidget(edtLog);


        verticalLayout_4->addWidget(logFrame);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_6->addLayout(horizontalLayout_2);

        pluginStatus = new QFrame(centralWidget);
        pluginStatus->setObjectName(QString::fromUtf8("pluginStatus"));
        verticalLayout_5 = new QVBoxLayout(pluginStatus);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        displayMode = new QFrame(pluginStatus);
        displayMode->setObjectName(QString::fromUtf8("displayMode"));
        displayMode->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}\n"
"\n"
"QFrame#frame\n"
"{\n"
"	border:1px solid #cccccc;\n"
"	background-color:rgb(247,249,255);\n"
"	color:black;\n"
"}"));
        displayMode->setFrameShape(QFrame::StyledPanel);
        displayMode->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(displayMode);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 5);
        label_3 = new QLabel(displayMode);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));
        label_3->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        lbTargetCount = new QLabel(displayMode);
        lbTargetCount->setObjectName(QString::fromUtf8("lbTargetCount"));
        lbTargetCount->setMinimumSize(QSize(50, 25));
        lbTargetCount->setMaximumSize(QSize(16777215, 25));
        lbTargetCount->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(lbTargetCount);

        label_5 = new QLabel(displayMode);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 25));
        label_5->setMaximumSize(QSize(16777215, 25));
        label_5->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_5);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        lbOnlineTargetCount = new QLabel(displayMode);
        lbOnlineTargetCount->setObjectName(QString::fromUtf8("lbOnlineTargetCount"));
        lbOnlineTargetCount->setMinimumSize(QSize(50, 25));
        lbOnlineTargetCount->setMaximumSize(QSize(16777215, 25));
        lbOnlineTargetCount->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color:red;\n"
"}"));

        horizontalLayout->addWidget(lbOnlineTargetCount);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_2 = new QLabel(displayMode);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_2);

        cmbDisplayMode = new QComboBox(displayMode);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8("image/allfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbDisplayMode->addItem(icon19, QString());
        cmbDisplayMode->addItem(icon19, QString());
        cmbDisplayMode->addItem(icon19, QString());
        QIcon icon20;
        icon20.addFile(QString::fromUtf8("image/star.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbDisplayMode->addItem(icon20, QString());
        cmbDisplayMode->setObjectName(QString::fromUtf8("cmbDisplayMode"));
        cmbDisplayMode->setMinimumSize(QSize(150, 25));
        cmbDisplayMode->setMaximumSize(QSize(16777215, 25));
        cmbDisplayMode->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"	background-color:rgb(247,249,255);;\n"
"	border:0px solid rgb(46,52,52);\n"
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
"	width:8px;\n"
"	image: url(image/arrow.png);\n"
" }\n"
"\n"
" QComboBox QAbstractItemView\n"
"{\n"
"	border:1px solid #eef0ff;\n"
"}"));
        cmbDisplayMode->setIconSize(QSize(20, 20));
        cmbDisplayMode->setFrame(true);

        horizontalLayout->addWidget(cmbDisplayMode);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(displayMode);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        cmbCategory = new QComboBox(displayMode);
        QIcon icon21;
        icon21.addFile(QString::fromUtf8("image/group.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbCategory->addItem(icon21, QString());
        QIcon icon22;
        icon22.addFile(QString::fromUtf8("image/windows_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbCategory->addItem(icon22, QString());
        QIcon icon23;
        icon23.addFile(QString::fromUtf8("image/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        cmbCategory->addItem(icon23, QString());
        cmbCategory->setObjectName(QString::fromUtf8("cmbCategory"));
        cmbCategory->setMinimumSize(QSize(150, 25));
        cmbCategory->setMaximumSize(QSize(16777215, 25));
        cmbCategory->setStyleSheet(QString::fromUtf8("QComboBox\n"
"{\n"
"	background-color:rgb(247,249,255);\n"
"	border:0px solid rgb(46,52,52);\n"
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
"	width:8px;\n"
"	image: url(image/arrow.png);\n"
" }\n"
"\n"
" QComboBox QAbstractItemView\n"
"{\n"
"	border:1px solid #eef0ff;\n"
"}"));
        cmbCategory->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(cmbCategory);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_5->addWidget(displayMode);

        label_6 = new QLabel(pluginStatus);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(263, 31));
        label_6->setMaximumSize(QSize(263, 16777215));
        label_6->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:0px;\n"
"}"));

        verticalLayout_5->addWidget(label_6);

        tbPluginStatus = new QTableWidget(pluginStatus);
        if (tbPluginStatus->columnCount() < 4)
            tbPluginStatus->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbPluginStatus->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbPluginStatus->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbPluginStatus->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbPluginStatus->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        if (tbPluginStatus->rowCount() < 5)
            tbPluginStatus->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbPluginStatus->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbPluginStatus->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbPluginStatus->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbPluginStatus->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbPluginStatus->setVerticalHeaderItem(4, __qtablewidgetitem15);
        tbPluginStatus->setObjectName(QString::fromUtf8("tbPluginStatus"));
        tbPluginStatus->setMinimumSize(QSize(263, 0));
        tbPluginStatus->setMaximumSize(QSize(263, 16777215));
        tbPluginStatus->setStyleSheet(QString::fromUtf8("QHeaderView \n"
"{\n"
"	background-color:#777777;\n"
"	color:#cccccc;\n"
"}\n"
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
"QFrame#tbPluginStatus{\n"
"	border:1px solid #aaaaaa;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image:none;\n"
"}"));
        tbPluginStatus->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbPluginStatus->setSelectionMode(QAbstractItemView::SingleSelection);
        tbPluginStatus->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbPluginStatus->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbPluginStatus->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbPluginStatus->setSortingEnabled(false);
        tbPluginStatus->horizontalHeader()->setHighlightSections(false);
        tbPluginStatus->horizontalHeader()->setStretchLastSection(true);
        tbPluginStatus->verticalHeader()->setVisible(false);
        tbPluginStatus->verticalHeader()->setDefaultSectionSize(25);
        tbPluginStatus->verticalHeader()->setHighlightSections(false);

        verticalLayout_5->addWidget(tbPluginStatus);


        verticalLayout_6->addWidget(pluginStatus);

        MainDlgClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainDlgClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        mainToolBar->setFloatable(false);
        MainDlgClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainDlgClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainDlgClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainDlgClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1375, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu_T = new QMenu(menuBar);
        menu_T->setObjectName(QString::fromUtf8("menu_T"));
        menu_S = new QMenu(menuBar);
        menu_S->setObjectName(QString::fromUtf8("menu_S"));
        menu_H = new QMenu(menuBar);
        menu_H->setObjectName(QString::fromUtf8("menu_H"));
        MainDlgClass->setMenuBar(menuBar);

        mainToolBar->addAction(actStart);
        mainToolBar->addAction(actStop);
        mainToolBar->addAction(actPolicy);
        mainToolBar->addAction(actAlias);
        mainToolBar->addAction(actCreate);
        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_T->menuAction());
        menuBar->addAction(menu_S->menuAction());
        menuBar->addAction(menu_H->menuAction());
        menu_F->addAction(actStart);
        menu_F->addAction(actStop);
        menu_T->addAction(actPolicy);
        menu_T->addAction(actFavorite);
        menu_T->addAction(actFlowControl);
        menu_S->addAction(actCreate);
        menu_S->addAction(actCreateDaemon);
        menu_S->addAction(actMigrateDaemon);
        menu_S->addAction(actCleanDatabase);
        menu_S->addSeparator();
        menu_S->addAction(actQueryDaemonAddress);
        menu_H->addAction(actAbout);

        retranslateUi(MainDlgClass);

        QMetaObject::connectSlotsByName(MainDlgClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainDlgClass)
    {
        MainDlgClass->setWindowTitle(QApplication::translate("MainDlgClass", "T9000 \347\273\274\345\220\210\346\216\247\345\210\266\345\271\263\345\217\260", 0, QApplication::UnicodeUTF8));
        actStart->setText(QApplication::translate("MainDlgClass", "\350\277\236\346\216\245\344\270\255\350\275\254", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actStart->setToolTip(QApplication::translate("MainDlgClass", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actStart->setShortcut(QApplication::translate("MainDlgClass", "F1", 0, QApplication::UnicodeUTF8));
        actStop->setText(QApplication::translate("MainDlgClass", "\346\226\255\345\274\200\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actStop->setToolTip(QApplication::translate("MainDlgClass", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actStop->setShortcut(QApplication::translate("MainDlgClass", "F2", 0, QApplication::UnicodeUTF8));
        actExit->setText(QApplication::translate("MainDlgClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actExit->setToolTip(QApplication::translate("MainDlgClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actExit->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actConfig->setText(QApplication::translate("MainDlgClass", "\345\205\250\345\261\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actConfig->setToolTip(QApplication::translate("MainDlgClass", "\345\205\250\345\261\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actConfig->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+1", 0, QApplication::UnicodeUTF8));
        actScreenMon->setText(QApplication::translate("MainDlgClass", "\345\261\217\345\271\225\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actScreenMon->setToolTip(QApplication::translate("MainDlgClass", "\345\261\217\345\271\225\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actScreenMon->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+4", 0, QApplication::UnicodeUTF8));
        actLog->setText(QApplication::translate("MainDlgClass", "\346\227\245\345\277\227\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        actLog->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+5", 0, QApplication::UnicodeUTF8));
        actAlias->setText(QApplication::translate("MainDlgClass", "\350\256\276\347\275\256\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        actDelSelf->setText(QApplication::translate("MainDlgClass", "\350\207\252\346\257\201", 0, QApplication::UnicodeUTF8));
        actClean->setText(QApplication::translate("MainDlgClass", "\345\210\240\351\231\244\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        actCreate->setText(QApplication::translate("MainDlgClass", "\347\224\237\346\210\220\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actCreate->setToolTip(QApplication::translate("MainDlgClass", "\347\224\237\346\210\220\347\233\256\346\240\207\347\253\257", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actCreate->setShortcut(QApplication::translate("MainDlgClass", "Alt+T", 0, QApplication::UnicodeUTF8));
        actHelp->setText(QApplication::translate("MainDlgClass", "\344\275\277\347\224\250\346\214\207\345\215\227", 0, QApplication::UnicodeUTF8));
        actHelp->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+?", 0, QApplication::UnicodeUTF8));
        actAbout->setText(QApplication::translate("MainDlgClass", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        actUserActionMonitor->setText(QApplication::translate("MainDlgClass", "\350\241\214\344\270\272\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actUserActionMonitor->setToolTip(QApplication::translate("MainDlgClass", "\347\224\250\346\210\267\350\241\214\344\270\272\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actUserActionMonitor->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+2", 0, QApplication::UnicodeUTF8));
        actUsbMonitor->setText(QApplication::translate("MainDlgClass", "USB\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actUsbMonitor->setToolTip(QApplication::translate("MainDlgClass", "USB \350\256\276\345\244\207\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actUsbMonitor->setShortcut(QApplication::translate("MainDlgClass", "Ctrl+3", 0, QApplication::UnicodeUTF8));
        actCleanDatabase->setText(QApplication::translate("MainDlgClass", "\346\270\205\351\231\244\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actCleanDatabase->setToolTip(QApplication::translate("MainDlgClass", "\346\270\205\351\231\244\346\225\260\346\215\256\345\272\223\344\270\255\346\211\200\346\234\211\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actCreateDaemon->setText(QApplication::translate("MainDlgClass", "\347\224\237\346\210\220\344\270\255\350\275\254", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actCreateDaemon->setToolTip(QApplication::translate("MainDlgClass", "\347\224\237\346\210\220\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actCreateDaemon->setShortcut(QApplication::translate("MainDlgClass", "Alt+D", 0, QApplication::UnicodeUTF8));
        actPolicy->setText(QApplication::translate("MainDlgClass", "\346\217\222\344\273\266\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actPolicy->setToolTip(QApplication::translate("MainDlgClass", "\344\277\256\346\224\271\346\217\222\344\273\266\347\255\226\347\225\245", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actMigrateDaemon->setText(QApplication::translate("MainDlgClass", "\350\277\201\347\247\273\344\270\255\350\275\254", 0, QApplication::UnicodeUTF8));
        actFlowControl->setText(QApplication::translate("MainDlgClass", "\346\265\201\351\207\217\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        actFavorite->setText(QApplication::translate("MainDlgClass", "\346\224\266\350\227\217\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actFavorite->setToolTip(QApplication::translate("MainDlgClass", "\345\260\206\347\233\256\346\240\207\345\212\240\345\205\245\346\224\266\350\227\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actQueryDaemonAddress->setText(QApplication::translate("MainDlgClass", "\346\237\245\350\257\242\344\270\255\350\275\254\345\233\236\350\277\236\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actQueryDaemonAddress->setToolTip(QApplication::translate("MainDlgClass", "\346\237\245\350\257\242\344\270\255\350\275\254\345\233\236\350\277\236\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("MainDlgClass", "\347\233\256\346\240\207\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trTarget->headerItem();
        ___qtreewidgetitem->setText(11, QApplication::translate("MainDlgClass", "_", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(10, QApplication::translate("MainDlgClass", "\350\257\255\350\250\200\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(9, QApplication::translate("MainDlgClass", "\347\211\251\347\220\206\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(8, QApplication::translate("MainDlgClass", "\347\275\221\347\273\234\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(7, QApplication::translate("MainDlgClass", "\346\225\260\346\215\256\346\265\201\351\207\217", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(6, QApplication::translate("MainDlgClass", "\346\211\200\345\234\250\345\234\260", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(5, QApplication::translate("MainDlgClass", "\345\206\205\351\203\250IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(4, QApplication::translate("MainDlgClass", "\345\244\226\351\203\250IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(3, QApplication::translate("MainDlgClass", "\346\223\215\344\275\234\347\263\273\347\273\237\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainDlgClass", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainDlgClass", "\347\233\256\346\240\207\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainDlgClass", "\347\233\256\346\240\207ID", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainDlgClass", "\347\233\256\346\240\207\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbBasicInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainDlgClass", "\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbBasicInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainDlgClass", "\345\206\205\345\256\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbBasicInfo->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbBasicInfo->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("MainDlgClass", "New Row", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbBasicInfo->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbBasicInfo->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbBasicInfo->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainDlgClass", "\350\257\246\347\273\206\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_001->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_001_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_002->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_002_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_003->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_003_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_004->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_004_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_005->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_005_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_006->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_006_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_007->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_007_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_008->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_008_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_009->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_009_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_010->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_010_content->setText(QApplication::translate("MainDlgClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainDlgClass", "\350\277\220\350\241\214\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainDlgClass", "\347\233\256\346\240\207\346\200\273\346\225\260 : ", 0, QApplication::UnicodeUTF8));
        lbTargetCount->setText(QApplication::translate("MainDlgClass", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainDlgClass", "\345\234\250\347\272\277\347\233\256\346\240\207\346\225\260 : ", 0, QApplication::UnicodeUTF8));
        lbOnlineTargetCount->setText(QApplication::translate("MainDlgClass", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainDlgClass", "\346\230\276\347\244\272\346\226\271\345\274\217 : ", 0, QApplication::UnicodeUTF8));
        cmbDisplayMode->setItemText(0, QApplication::translate("MainDlgClass", "\346\230\276\347\244\272\346\211\200\346\234\211\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        cmbDisplayMode->setItemText(1, QApplication::translate("MainDlgClass", "\345\217\252\346\230\276\347\244\272\345\234\250\347\272\277\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        cmbDisplayMode->setItemText(2, QApplication::translate("MainDlgClass", "\345\217\252\346\230\276\347\244\272\347\246\273\347\272\277\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        cmbDisplayMode->setItemText(3, QApplication::translate("MainDlgClass", "\345\217\252\346\230\276\347\244\272\346\224\266\350\227\217\347\232\204\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));

        label->setText(QApplication::translate("MainDlgClass", "\345\210\206\347\273\204\346\226\271\345\274\217 : ", 0, QApplication::UnicodeUTF8));
        cmbCategory->setItemText(0, QApplication::translate("MainDlgClass", "\351\273\230\350\256\244\345\210\206\347\273\204", 0, QApplication::UnicodeUTF8));
        cmbCategory->setItemText(1, QApplication::translate("MainDlgClass", "\346\214\211\345\271\263\345\217\260\345\210\206\347\273\204", 0, QApplication::UnicodeUTF8));
        cmbCategory->setItemText(2, QApplication::translate("MainDlgClass", "\346\214\211\346\211\200\345\234\250\345\234\260\345\210\206\347\273\204", 0, QApplication::UnicodeUTF8));

        label_6->setText(QApplication::translate("MainDlgClass", "\346\217\222\344\273\266\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbPluginStatus->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("MainDlgClass", "  ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbPluginStatus->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("MainDlgClass", "  \346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbPluginStatus->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("MainDlgClass", "  \347\211\210\346\234\254\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbPluginStatus->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("MainDlgClass", "  \347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbPluginStatus->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbPluginStatus->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbPluginStatus->verticalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbPluginStatus->verticalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tbPluginStatus->verticalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("MainDlgClass", "\346\226\260\345\273\272\350\241\214", 0, QApplication::UnicodeUTF8));
        menu_F->setTitle(QApplication::translate("MainDlgClass", "\345\274\200\345\247\213 (F)", 0, QApplication::UnicodeUTF8));
        menu_T->setTitle(QApplication::translate("MainDlgClass", "\347\233\256\346\240\207 (T)", 0, QApplication::UnicodeUTF8));
        menu_S->setTitle(QApplication::translate("MainDlgClass", "\351\205\215\347\275\256 (S)", 0, QApplication::UnicodeUTF8));
        menu_H->setTitle(QApplication::translate("MainDlgClass", "\345\270\256\345\212\251 (H)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainDlgClass: public Ui_MainDlgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDLG_H
