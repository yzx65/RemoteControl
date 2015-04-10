/********************************************************************************
** Form generated from reading UI file 'targetdlg.ui'
**
** Created: Fri Apr 10 09:05:14 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGETDLG_H
#define UI_TARGETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TargetDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame_tool_bar;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbStatusBar;
    QComboBox *cmbLocalDir;
    QTabWidget *tabMain;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_71;
    QTreeWidget *trMissionStatus;
    QFrame *frame_7;
    QVBoxLayout *verticalLayout_37;
    QFrame *toolbar;
    QHBoxLayout *horizontalLayout_60;
    QToolButton *btnContinue;
    QToolButton *btnPause;
    QToolButton *btnCancel;
    QSpacerItem *horizontalSpacer_27;
    QLabel *lbMissionStatus;
    QStackedWidget *stkMissionStatus;
    QWidget *page_11;
    QVBoxLayout *verticalLayout_40;
    QTableWidget *tbUploadFileList;
    QWidget *page_12;
    QVBoxLayout *verticalLayout_41;
    QTableWidget *tbDownloadFileList;
    QWidget *page_13;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_38;
    QTableWidget *tbDirCommand;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_40;
    QTableWidget *tbFileCommand;
    QWidget *page_14;
    QVBoxLayout *verticalLayout_39;
    QTableWidget *tbDirInfoList;
    QWidget *page_17;
    QVBoxLayout *verticalLayout_30;
    QTableWidget *tbUploadPluginList;
    QWidget *page_10;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *tbPluginData;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_16;
    QFrame *frmFileCtrl;
    QWidget *tab_8;
    QHBoxLayout *horizontalLayout_28;
    QFrame *frmRemoteCmd;
    QWidget *tab_5;
    QHBoxLayout *horizontalLayout_19;
    QFrame *frmAdvanceMonitor;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_78;
    QFrame *frmUserAction;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_223;
    QFrame *frmCapture;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_5;
    QFrame *frmRecord;
    QWidget *tab_9;
    QHBoxLayout *horizontalLayout_20;
    QFrame *frmMultiMedia;
    QWidget *tab_11;
    QHBoxLayout *horizontalLayout_34;
    QFrame *frmAppInfo;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_20;
    QFrame *frmMapInfo;
    QWidget *tab_10;
    QHBoxLayout *horizontalLayout_33;
    QVBoxLayout *verticalLayout_28;
    QFrame *frmThirdPlugin;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_23;
    QFrame *frmLog;

    void setupUi(QWidget *TargetDlg)
    {
        if (TargetDlg->objectName().isEmpty())
            TargetDlg->setObjectName(QString::fromUtf8("TargetDlg"));
        TargetDlg->resize(807, 605);
        TargetDlg->setStyleSheet(QString::fromUtf8("QWidget#TargetDlg\n"
"{\n"
"	background:rgb(88,115,201);\n"
"}"));
        horizontalLayout = new QHBoxLayout(TargetDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_tool_bar = new QFrame(TargetDlg);
        frame_tool_bar->setObjectName(QString::fromUtf8("frame_tool_bar"));
        frame_tool_bar->setMinimumSize(QSize(0, 100));
        frame_tool_bar->setFrameShape(QFrame::StyledPanel);
        frame_tool_bar->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_tool_bar);

        frame_4 = new QFrame(TargetDlg);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setStyleSheet(QString::fromUtf8("QFrame#frame_4\n"
"{\n"
"	background-color:rgb(240,240,240);\n"
"}"));
        frame_4->setFrameShape(QFrame::NoFrame);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_4->setLineWidth(0);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lbStatusBar = new QLabel(frame_4);
        lbStatusBar->setObjectName(QString::fromUtf8("lbStatusBar"));
        lbStatusBar->setMinimumSize(QSize(0, 0));
        lbStatusBar->setMaximumSize(QSize(100, 16777215));
        lbStatusBar->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));

        horizontalLayout_3->addWidget(lbStatusBar);

        cmbLocalDir = new QComboBox(frame_4);
        cmbLocalDir->setObjectName(QString::fromUtf8("cmbLocalDir"));
        cmbLocalDir->setMinimumSize(QSize(0, 0));
        cmbLocalDir->setMaximumSize(QSize(191, 16777215));
        cmbLocalDir->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"     border: 0px solid gray;\n"
"     padding: 1px 18px 1px 3px;\n"
"     min-width: 170px;\n"
"	background-color:rgba(200, 200, 200, 80);\n"
"	font-family:\"Microsoft Yahei\";\n"
" }\n"
"\n"
"QComboBox:hover{\n"
"	background-color:rgba(100, 100, 255, 80);\n"
"}\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"     border-width: 0px;\n"
" }"));
        cmbLocalDir->setFrame(true);

        horizontalLayout_3->addWidget(cmbLocalDir);


        horizontalLayout->addWidget(frame_4);

        tabMain = new QTabWidget(TargetDlg);
        tabMain->setObjectName(QString::fromUtf8("tabMain"));
        tabMain->setMinimumSize(QSize(0, 30));
        tabMain->setStyleSheet(QString::fromUtf8(""));
        tabMain->setIconSize(QSize(24, 24));
        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_71 = new QHBoxLayout(widget);
        horizontalLayout_71->setSpacing(1);
        horizontalLayout_71->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_71->setObjectName(QString::fromUtf8("horizontalLayout_71"));
        trMissionStatus = new QTreeWidget(widget);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/uploadfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/downfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/dirdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/dirfilelist.png"), QSize(), QIcon::Normal, QIcon::Off);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem1->setIcon(0, icon1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem2->setIcon(0, icon2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem3->setIcon(0, icon3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem4->setIcon(0, icon);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(trMissionStatus);
        __qtreewidgetitem5->setIcon(0, icon4);
        trMissionStatus->setObjectName(QString::fromUtf8("trMissionStatus"));
        trMissionStatus->setMinimumSize(QSize(200, 0));
        trMissionStatus->setMaximumSize(QSize(200, 16777215));
        trMissionStatus->setContextMenuPolicy(Qt::CustomContextMenu);
        trMissionStatus->setStyleSheet(QString::fromUtf8(" QWidget\n"
" {\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-right-width:1px;\n"
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
        trMissionStatus->setIndentation(0);
        trMissionStatus->setRootIsDecorated(false);
        trMissionStatus->header()->setVisible(false);

        horizontalLayout_71->addWidget(trMissionStatus);

        frame_7 = new QFrame(widget);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setStyleSheet(QString::fromUtf8("QWidget#frame_7\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout_37 = new QVBoxLayout(frame_7);
        verticalLayout_37->setSpacing(0);
        verticalLayout_37->setContentsMargins(0, 0, 0, 0);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        toolbar = new QFrame(frame_7);
        toolbar->setObjectName(QString::fromUtf8("toolbar"));
        toolbar->setStyleSheet(QString::fromUtf8("QFrame#toolbar\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));
        horizontalLayout_60 = new QHBoxLayout(toolbar);
        horizontalLayout_60->setSpacing(10);
        horizontalLayout_60->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_60->setObjectName(QString::fromUtf8("horizontalLayout_60"));
        horizontalLayout_60->setContentsMargins(9, 5, 9, 5);
        btnContinue = new QToolButton(toolbar);
        btnContinue->setObjectName(QString::fromUtf8("btnContinue"));
        btnContinue->setEnabled(true);
        btnContinue->setMinimumSize(QSize(30, 30));
        btnContinue->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	padding-left:5px;\n"
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
        icon5.addFile(QString::fromUtf8(":/image/continue.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnContinue->setIcon(icon5);
        btnContinue->setIconSize(QSize(16, 16));
        btnContinue->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnContinue->setAutoRaise(true);

        horizontalLayout_60->addWidget(btnContinue);

        btnPause = new QToolButton(toolbar);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setEnabled(true);
        btnPause->setMinimumSize(QSize(30, 30));
        btnPause->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	padding-left:5px;\n"
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
        icon6.addFile(QString::fromUtf8(":/image/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPause->setIcon(icon6);
        btnPause->setIconSize(QSize(16, 16));
        btnPause->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnPause->setAutoRaise(true);

        horizontalLayout_60->addWidget(btnPause);

        btnCancel = new QToolButton(toolbar);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setEnabled(true);
        btnCancel->setMinimumSize(QSize(30, 30));
        btnCancel->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	padding-left:5px;\n"
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
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon7);
        btnCancel->setIconSize(QSize(16, 16));
        btnCancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btnCancel->setAutoRaise(true);

        horizontalLayout_60->addWidget(btnCancel);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_60->addItem(horizontalSpacer_27);


        verticalLayout_37->addWidget(toolbar);

        lbMissionStatus = new QLabel(frame_7);
        lbMissionStatus->setObjectName(QString::fromUtf8("lbMissionStatus"));
        lbMissionStatus->setMinimumSize(QSize(0, 35));
        lbMissionStatus->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	color:#333333;\n"
"	padding-left:20px;\n"
"}"));
        lbMissionStatus->setFrameShape(QFrame::NoFrame);
        lbMissionStatus->setFrameShadow(QFrame::Plain);

        verticalLayout_37->addWidget(lbMissionStatus);

        stkMissionStatus = new QStackedWidget(frame_7);
        stkMissionStatus->setObjectName(QString::fromUtf8("stkMissionStatus"));
        stkMissionStatus->setStyleSheet(QString::fromUtf8("QWidget#stkMissionStatus\n"
"{\n"
"	background-color:white;\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));
        page_11 = new QWidget();
        page_11->setObjectName(QString::fromUtf8("page_11"));
        verticalLayout_40 = new QVBoxLayout(page_11);
        verticalLayout_40->setSpacing(0);
        verticalLayout_40->setContentsMargins(0, 0, 0, 0);
        verticalLayout_40->setObjectName(QString::fromUtf8("verticalLayout_40"));
        tbUploadFileList = new QTableWidget(page_11);
        if (tbUploadFileList->columnCount() < 9)
            tbUploadFileList->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbUploadFileList->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tbUploadFileList->setObjectName(QString::fromUtf8("tbUploadFileList"));
        tbUploadFileList->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\n"
"	border:none;\n"
"	border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\n"
"	border-bottom: 0px solid #eeeeee;\n"
"	height:25px;\n"
"	color:#333333;\n"
"	font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	font-style:bold;\n"
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
"QFrame#tbUploadFileList{\n"
"	border:0px solid #cccccc;\n"
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
        tbUploadFileList->setFrameShape(QFrame::NoFrame);
        tbUploadFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUploadFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUploadFileList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbUploadFileList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbUploadFileList->setShowGrid(false);
        tbUploadFileList->setGridStyle(Qt::NoPen);
        tbUploadFileList->setSortingEnabled(false);
        tbUploadFileList->horizontalHeader()->setHighlightSections(false);
        tbUploadFileList->horizontalHeader()->setMinimumSectionSize(20);
        tbUploadFileList->horizontalHeader()->setStretchLastSection(true);
        tbUploadFileList->verticalHeader()->setVisible(false);
        tbUploadFileList->verticalHeader()->setDefaultSectionSize(20);
        tbUploadFileList->verticalHeader()->setHighlightSections(false);
        tbUploadFileList->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_40->addWidget(tbUploadFileList);

        stkMissionStatus->addWidget(page_11);
        page_12 = new QWidget();
        page_12->setObjectName(QString::fromUtf8("page_12"));
        verticalLayout_41 = new QVBoxLayout(page_12);
        verticalLayout_41->setSpacing(0);
        verticalLayout_41->setContentsMargins(0, 0, 0, 0);
        verticalLayout_41->setObjectName(QString::fromUtf8("verticalLayout_41"));
        tbDownloadFileList = new QTableWidget(page_12);
        if (tbDownloadFileList->columnCount() < 8)
            tbDownloadFileList->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tbDownloadFileList->setHorizontalHeaderItem(7, __qtablewidgetitem16);
        tbDownloadFileList->setObjectName(QString::fromUtf8("tbDownloadFileList"));
        tbDownloadFileList->setContextMenuPolicy(Qt::CustomContextMenu);
        tbDownloadFileList->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbDownloadFileList{\n"
"	border:0px solid #cccccc;\n"
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
" QScrollBar::hand"
                        "le:vertical {\n"
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
        tbDownloadFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbDownloadFileList->setSelectionMode(QAbstractItemView::SingleSelection);
        tbDownloadFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbDownloadFileList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDownloadFileList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDownloadFileList->setShowGrid(false);
        tbDownloadFileList->setGridStyle(Qt::NoPen);
        tbDownloadFileList->setSortingEnabled(false);
        tbDownloadFileList->horizontalHeader()->setHighlightSections(false);
        tbDownloadFileList->horizontalHeader()->setMinimumSectionSize(20);
        tbDownloadFileList->horizontalHeader()->setStretchLastSection(true);
        tbDownloadFileList->verticalHeader()->setVisible(false);
        tbDownloadFileList->verticalHeader()->setDefaultSectionSize(20);
        tbDownloadFileList->verticalHeader()->setHighlightSections(false);
        tbDownloadFileList->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_41->addWidget(tbDownloadFileList);

        stkMissionStatus->addWidget(page_12);
        page_13 = new QWidget();
        page_13->setObjectName(QString::fromUtf8("page_13"));
        verticalLayout_4 = new QVBoxLayout(page_13);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_38 = new QLabel(page_13);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_38->sizePolicy().hasHeightForWidth());
        label_38->setSizePolicy(sizePolicy1);
        label_38->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));

        verticalLayout_3->addWidget(label_38);

        tbDirCommand = new QTableWidget(page_13);
        if (tbDirCommand->columnCount() < 10)
            tbDirCommand->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(4, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(5, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(6, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(7, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(8, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tbDirCommand->setHorizontalHeaderItem(9, __qtablewidgetitem26);
        tbDirCommand->setObjectName(QString::fromUtf8("tbDirCommand"));
        tbDirCommand->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbDirCommand{\n"
"	border:1px solid #cccccc;\n"
"	border-top-width:0px;\n"
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
        tbDirCommand->setFrameShape(QFrame::NoFrame);
        tbDirCommand->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbDirCommand->setSelectionMode(QAbstractItemView::SingleSelection);
        tbDirCommand->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbDirCommand->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDirCommand->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDirCommand->setShowGrid(false);
        tbDirCommand->setGridStyle(Qt::NoPen);
        tbDirCommand->setSortingEnabled(false);
        tbDirCommand->horizontalHeader()->setHighlightSections(false);
        tbDirCommand->horizontalHeader()->setMinimumSectionSize(20);
        tbDirCommand->horizontalHeader()->setStretchLastSection(true);
        tbDirCommand->verticalHeader()->setVisible(false);
        tbDirCommand->verticalHeader()->setDefaultSectionSize(20);
        tbDirCommand->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_3->addWidget(tbDirCommand);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_40 = new QLabel(page_13);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        sizePolicy1.setHeightForWidth(label_40->sizePolicy().hasHeightForWidth());
        label_40->setSizePolicy(sizePolicy1);
        label_40->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:1px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-left-width:1px;\n"
"}"));

        verticalLayout_2->addWidget(label_40);

        tbFileCommand = new QTableWidget(page_13);
        if (tbFileCommand->columnCount() < 8)
            tbFileCommand->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(0, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(1, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(2, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(3, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(4, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(5, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(6, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tbFileCommand->setHorizontalHeaderItem(7, __qtablewidgetitem34);
        tbFileCommand->setObjectName(QString::fromUtf8("tbFileCommand"));
        tbFileCommand->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbFileCommand{\n"
"	border:1px solid #cccccc;\n"
"	border-top-width:0px;\n"
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
" }"
                        "\n"
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
        tbFileCommand->setFrameShape(QFrame::NoFrame);
        tbFileCommand->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbFileCommand->setSelectionMode(QAbstractItemView::SingleSelection);
        tbFileCommand->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbFileCommand->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbFileCommand->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbFileCommand->setShowGrid(false);
        tbFileCommand->setGridStyle(Qt::NoPen);
        tbFileCommand->setSortingEnabled(false);
        tbFileCommand->horizontalHeader()->setHighlightSections(false);
        tbFileCommand->horizontalHeader()->setMinimumSectionSize(20);
        tbFileCommand->horizontalHeader()->setStretchLastSection(true);
        tbFileCommand->verticalHeader()->setVisible(false);
        tbFileCommand->verticalHeader()->setDefaultSectionSize(20);
        tbFileCommand->verticalHeader()->setHighlightSections(false);
        tbFileCommand->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_2->addWidget(tbFileCommand);


        verticalLayout_4->addLayout(verticalLayout_2);

        stkMissionStatus->addWidget(page_13);
        page_14 = new QWidget();
        page_14->setObjectName(QString::fromUtf8("page_14"));
        verticalLayout_39 = new QVBoxLayout(page_14);
        verticalLayout_39->setSpacing(0);
        verticalLayout_39->setContentsMargins(0, 0, 0, 0);
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        tbDirInfoList = new QTableWidget(page_14);
        if (tbDirInfoList->columnCount() < 8)
            tbDirInfoList->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(0, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(1, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(2, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(3, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(4, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(5, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(6, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tbDirInfoList->setHorizontalHeaderItem(7, __qtablewidgetitem42);
        tbDirInfoList->setObjectName(QString::fromUtf8("tbDirInfoList"));
        tbDirInfoList->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbDirInfoList{\n"
"	border:0px solid #cccccc;\n"
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
" QScrollBar::handle:ve"
                        "rtical {\n"
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
        tbDirInfoList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbDirInfoList->setSelectionMode(QAbstractItemView::SingleSelection);
        tbDirInfoList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbDirInfoList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDirInfoList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbDirInfoList->setShowGrid(false);
        tbDirInfoList->setGridStyle(Qt::NoPen);
        tbDirInfoList->setSortingEnabled(false);
        tbDirInfoList->horizontalHeader()->setHighlightSections(false);
        tbDirInfoList->horizontalHeader()->setMinimumSectionSize(20);
        tbDirInfoList->horizontalHeader()->setStretchLastSection(true);
        tbDirInfoList->verticalHeader()->setVisible(false);
        tbDirInfoList->verticalHeader()->setDefaultSectionSize(20);
        tbDirInfoList->verticalHeader()->setHighlightSections(false);
        tbDirInfoList->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_39->addWidget(tbDirInfoList);

        stkMissionStatus->addWidget(page_14);
        page_17 = new QWidget();
        page_17->setObjectName(QString::fromUtf8("page_17"));
        verticalLayout_30 = new QVBoxLayout(page_17);
        verticalLayout_30->setSpacing(0);
        verticalLayout_30->setContentsMargins(0, 0, 0, 0);
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        tbUploadPluginList = new QTableWidget(page_17);
        if (tbUploadPluginList->columnCount() < 7)
            tbUploadPluginList->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(0, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(1, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(2, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(3, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(4, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(5, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tbUploadPluginList->setHorizontalHeaderItem(6, __qtablewidgetitem49);
        tbUploadPluginList->setObjectName(QString::fromUtf8("tbUploadPluginList"));
        tbUploadPluginList->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbUploadPluginList{\n"
"	border:0px solid #cccccc;\n"
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
" QScrollBar::hand"
                        "le:vertical {\n"
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
        tbUploadPluginList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbUploadPluginList->setSelectionMode(QAbstractItemView::SingleSelection);
        tbUploadPluginList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbUploadPluginList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbUploadPluginList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbUploadPluginList->setShowGrid(false);
        tbUploadPluginList->setGridStyle(Qt::NoPen);
        tbUploadPluginList->setSortingEnabled(false);
        tbUploadPluginList->horizontalHeader()->setHighlightSections(false);
        tbUploadPluginList->horizontalHeader()->setMinimumSectionSize(20);
        tbUploadPluginList->horizontalHeader()->setStretchLastSection(true);
        tbUploadPluginList->verticalHeader()->setVisible(false);
        tbUploadPluginList->verticalHeader()->setDefaultSectionSize(20);
        tbUploadPluginList->verticalHeader()->setHighlightSections(false);
        tbUploadPluginList->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_30->addWidget(tbUploadPluginList);

        stkMissionStatus->addWidget(page_17);
        page_10 = new QWidget();
        page_10->setObjectName(QString::fromUtf8("page_10"));
        verticalLayout_10 = new QVBoxLayout(page_10);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        tbPluginData = new QTableWidget(page_10);
        if (tbPluginData->columnCount() < 9)
            tbPluginData->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(0, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(2, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(3, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(4, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(5, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(6, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(7, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tbPluginData->setHorizontalHeaderItem(8, __qtablewidgetitem58);
        tbPluginData->setObjectName(QString::fromUtf8("tbPluginData"));
        tbPluginData->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbPluginData{\n"
"	border:0px solid #cccccc;\n"
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
" QScrollBar::handle:ver"
                        "tical {\n"
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
        tbPluginData->setFrameShape(QFrame::StyledPanel);
        tbPluginData->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbPluginData->setSelectionMode(QAbstractItemView::SingleSelection);
        tbPluginData->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbPluginData->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbPluginData->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbPluginData->setShowGrid(false);
        tbPluginData->setGridStyle(Qt::NoPen);
        tbPluginData->setSortingEnabled(false);
        tbPluginData->horizontalHeader()->setHighlightSections(false);
        tbPluginData->horizontalHeader()->setMinimumSectionSize(20);
        tbPluginData->horizontalHeader()->setStretchLastSection(true);
        tbPluginData->verticalHeader()->setVisible(false);
        tbPluginData->verticalHeader()->setDefaultSectionSize(20);
        tbPluginData->verticalHeader()->setHighlightSections(false);
        tbPluginData->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_10->addWidget(tbPluginData);

        stkMissionStatus->addWidget(page_10);

        verticalLayout_37->addWidget(stkMissionStatus);


        horizontalLayout_71->addWidget(frame_7);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/FORWARD 2.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(widget, icon8, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_16 = new QHBoxLayout(tab);
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        frmFileCtrl = new QFrame(tab);
        frmFileCtrl->setObjectName(QString::fromUtf8("frmFileCtrl"));
        frmFileCtrl->setFrameShape(QFrame::StyledPanel);
        frmFileCtrl->setFrameShadow(QFrame::Raised);

        horizontalLayout_16->addWidget(frmFileCtrl);

        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/EMPTY BLANK.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab, icon9, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QString::fromUtf8("tab_8"));
        tab_8->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border-style:solid;\n"
"	border-width:1px;\n"
"	border-color:#aaaaaa;\n"
"}"));
        horizontalLayout_28 = new QHBoxLayout(tab_8);
        horizontalLayout_28->setSpacing(0);
        horizontalLayout_28->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        frmRemoteCmd = new QFrame(tab_8);
        frmRemoteCmd->setObjectName(QString::fromUtf8("frmRemoteCmd"));
        frmRemoteCmd->setMinimumSize(QSize(500, 0));
        frmRemoteCmd->setStyleSheet(QString::fromUtf8("QFrame#frame_5\n"
"{\n"
"	border-style:solid;\n"
"	border-width:0px;\n"
"	border-bottom-width:1px;\n"
"	border-color:#aaaaaa;\n"
"	background-color:#aaaaaa;\n"
"}"));
        frmRemoteCmd->setFrameShape(QFrame::StyledPanel);
        frmRemoteCmd->setFrameShadow(QFrame::Raised);

        horizontalLayout_28->addWidget(frmRemoteCmd);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/cmd.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_8, icon10, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        horizontalLayout_19 = new QHBoxLayout(tab_5);
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        frmAdvanceMonitor = new QFrame(tab_5);
        frmAdvanceMonitor->setObjectName(QString::fromUtf8("frmAdvanceMonitor"));
        frmAdvanceMonitor->setFrameShape(QFrame::StyledPanel);
        frmAdvanceMonitor->setFrameShadow(QFrame::Raised);

        horizontalLayout_19->addWidget(frmAdvanceMonitor);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/MINIMIZE.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_5, icon11, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_78 = new QHBoxLayout(tab_2);
        horizontalLayout_78->setSpacing(1);
        horizontalLayout_78->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_78->setObjectName(QString::fromUtf8("horizontalLayout_78"));
        frmUserAction = new QFrame(tab_2);
        frmUserAction->setObjectName(QString::fromUtf8("frmUserAction"));
        frmUserAction->setFrameShape(QFrame::StyledPanel);
        frmUserAction->setFrameShadow(QFrame::Raised);

        horizontalLayout_78->addWidget(frmUserAction);

        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/CURSOR.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_2, icon12, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setStyleSheet(QString::fromUtf8("QWidget#tab_3\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        horizontalLayout_223 = new QHBoxLayout(tab_3);
        horizontalLayout_223->setSpacing(6);
        horizontalLayout_223->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_223->setObjectName(QString::fromUtf8("horizontalLayout_223"));
        horizontalLayout_223->setContentsMargins(0, 0, 9, 0);
        frmCapture = new QFrame(tab_3);
        frmCapture->setObjectName(QString::fromUtf8("frmCapture"));
        frmCapture->setFrameShape(QFrame::StyledPanel);
        frmCapture->setFrameShadow(QFrame::Raised);

        horizontalLayout_223->addWidget(frmCapture);

        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/image/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_3, icon13, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_5 = new QVBoxLayout(tab_6);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frmRecord = new QFrame(tab_6);
        frmRecord->setObjectName(QString::fromUtf8("frmRecord"));
        frmRecord->setFrameShape(QFrame::StyledPanel);
        frmRecord->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(frmRecord);

        tabMain->addTab(tab_6, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QString::fromUtf8("tab_9"));
        horizontalLayout_20 = new QHBoxLayout(tab_9);
        horizontalLayout_20->setSpacing(0);
        horizontalLayout_20->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        frmMultiMedia = new QFrame(tab_9);
        frmMultiMedia->setObjectName(QString::fromUtf8("frmMultiMedia"));
        frmMultiMedia->setStyleSheet(QString::fromUtf8("QFrame#frmMultiMedia\n"
"{\n"
"	border:0px solid #aaaaaa;\n"
"	border-bottom-width:1px;\n"
"}"));
        frmMultiMedia->setFrameShape(QFrame::StyledPanel);
        frmMultiMedia->setFrameShadow(QFrame::Raised);

        horizontalLayout_20->addWidget(frmMultiMedia);

        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/image/VIDEO CAMERA.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_9, icon14, QString());
        tab_11 = new QWidget();
        tab_11->setObjectName(QString::fromUtf8("tab_11"));
        horizontalLayout_34 = new QHBoxLayout(tab_11);
        horizontalLayout_34->setSpacing(0);
        horizontalLayout_34->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        frmAppInfo = new QFrame(tab_11);
        frmAppInfo->setObjectName(QString::fromUtf8("frmAppInfo"));
        frmAppInfo->setStyleSheet(QString::fromUtf8("QFrame#frmAppInfo\n"
"{\n"
"	border:0px solid #aaaaaa;\n"
"	border-bottom-width:1px;\n"
"}"));
        frmAppInfo->setFrameShape(QFrame::StyledPanel);
        frmAppInfo->setFrameShadow(QFrame::Raised);

        horizontalLayout_34->addWidget(frmAppInfo);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/image/CHAT.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_11, icon15, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        verticalLayout_20 = new QVBoxLayout(tab_7);
        verticalLayout_20->setSpacing(0);
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        frmMapInfo = new QFrame(tab_7);
        frmMapInfo->setObjectName(QString::fromUtf8("frmMapInfo"));
        frmMapInfo->setFrameShape(QFrame::StyledPanel);
        frmMapInfo->setFrameShadow(QFrame::Raised);

        verticalLayout_20->addWidget(frmMapInfo);

        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/image/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_7, icon16, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QString::fromUtf8("tab_10"));
        horizontalLayout_33 = new QHBoxLayout(tab_10);
        horizontalLayout_33->setSpacing(0);
        horizontalLayout_33->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        verticalLayout_28 = new QVBoxLayout();
        verticalLayout_28->setSpacing(0);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        frmThirdPlugin = new QFrame(tab_10);
        frmThirdPlugin->setObjectName(QString::fromUtf8("frmThirdPlugin"));
        frmThirdPlugin->setStyleSheet(QString::fromUtf8("QFrame#frmThirdPlugin\n"
"{\n"
"	border:0px solid #aaaaaa;\n"
"	border-bottom-width:1px;\n"
"}"));
        frmThirdPlugin->setFrameShape(QFrame::StyledPanel);
        frmThirdPlugin->setFrameShadow(QFrame::Raised);

        verticalLayout_28->addWidget(frmThirdPlugin);


        horizontalLayout_33->addLayout(verticalLayout_28);

        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/image/SETTINGS.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_10, icon17, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        horizontalLayout_23 = new QHBoxLayout(tab_4);
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        frmLog = new QFrame(tab_4);
        frmLog->setObjectName(QString::fromUtf8("frmLog"));
        frmLog->setFrameShape(QFrame::StyledPanel);
        frmLog->setFrameShadow(QFrame::Raised);

        horizontalLayout_23->addWidget(frmLog);

        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/image/STATISTICS.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabMain->addTab(tab_4, icon18, QString());

        horizontalLayout->addWidget(tabMain);


        retranslateUi(TargetDlg);

        tabMain->setCurrentIndex(0);
        stkMissionStatus->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TargetDlg);
    } // setupUi

    void retranslateUi(QWidget *TargetDlg)
    {
        TargetDlg->setWindowTitle(QApplication::translate("TargetDlg", "\347\233\256\346\240\207", 0, QApplication::UnicodeUTF8));
        lbStatusBar->setText(QApplication::translate("TargetDlg", "  \345\207\206\345\244\207\345\260\261\347\273\252", 0, QApplication::UnicodeUTF8));
        cmbLocalDir->clear();
        cmbLocalDir->insertItems(0, QStringList()
         << QApplication::translate("TargetDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TargetDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TargetDlg", "New Item", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("TargetDlg", "New Item", 0, QApplication::UnicodeUTF8)
        );
        QTreeWidgetItem *___qtreewidgetitem = trMissionStatus->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("TargetDlg", "\346\226\207\344\273\266\346\223\215\344\275\234\346\214\207\344\273\244", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trMissionStatus->isSortingEnabled();
        trMissionStatus->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trMissionStatus->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("TargetDlg", "\346\226\207\344\273\266\344\270\212\344\274\240", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = trMissionStatus->topLevelItem(1);
        ___qtreewidgetitem2->setText(0, QApplication::translate("TargetDlg", "\346\226\207\344\273\266\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = trMissionStatus->topLevelItem(2);
        ___qtreewidgetitem3->setText(0, QApplication::translate("TargetDlg", "\347\233\256\345\275\225\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = trMissionStatus->topLevelItem(3);
        ___qtreewidgetitem4->setText(0, QApplication::translate("TargetDlg", "\345\244\232\345\261\202\347\233\256\345\275\225\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = trMissionStatus->topLevelItem(4);
        ___qtreewidgetitem5->setText(0, QApplication::translate("TargetDlg", "\346\217\222\344\273\266\345\215\207\347\272\247\344\270\212\344\274\240", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = trMissionStatus->topLevelItem(5);
        ___qtreewidgetitem6->setText(0, QApplication::translate("TargetDlg", "\346\217\222\344\273\266\346\225\260\346\215\256\345\233\236\344\274\240", 0, QApplication::UnicodeUTF8));
        trMissionStatus->setSortingEnabled(__sortingEnabled);

        btnContinue->setText(QString());
        btnPause->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnCancel->setToolTip(QApplication::translate("TargetDlg", "\345\217\226\346\266\210\345\271\266\345\210\240\351\231\244\346\214\207\344\273\244", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnCancel->setText(QString());
        lbMissionStatus->setText(QApplication::translate("TargetDlg", "\346\226\207\344\273\266\344\274\240\350\276\223\346\214\207\344\273\244", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbUploadFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbUploadFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TargetDlg", "\346\214\207\344\273\244ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbUploadFileList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TargetDlg", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbUploadFileList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("TargetDlg", "\346\234\254\345\234\260\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbUploadFileList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("TargetDlg", "\347\233\256\346\240\207\347\253\257\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbUploadFileList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("TargetDlg", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbUploadFileList->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbUploadFileList->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbUploadFileList->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbDownloadFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbDownloadFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QApplication::translate("TargetDlg", "\346\214\207\344\273\244ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tbDownloadFileList->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QApplication::translate("TargetDlg", "\347\233\256\346\240\207\347\253\257\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tbDownloadFileList->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QApplication::translate("TargetDlg", "\346\234\254\345\234\260\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tbDownloadFileList->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QApplication::translate("TargetDlg", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tbDownloadFileList->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tbDownloadFileList->horizontalHeaderItem(6);
        ___qtablewidgetitem15->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem16 = tbDownloadFileList->horizontalHeaderItem(7);
        ___qtablewidgetitem16->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("TargetDlg", "\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tbDirCommand->horizontalHeaderItem(0);
        ___qtablewidgetitem17->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tbDirCommand->horizontalHeaderItem(1);
        ___qtablewidgetitem18->setText(QApplication::translate("TargetDlg", "\346\214\207\344\273\244ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tbDirCommand->horizontalHeaderItem(2);
        ___qtablewidgetitem19->setText(QApplication::translate("TargetDlg", "\347\233\256\346\240\207\347\253\257\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tbDirCommand->horizontalHeaderItem(3);
        ___qtablewidgetitem20->setText(QApplication::translate("TargetDlg", "\347\233\256\345\275\225\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tbDirCommand->horizontalHeaderItem(4);
        ___qtablewidgetitem21->setText(QApplication::translate("TargetDlg", "\350\277\233\350\241\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tbDirCommand->horizontalHeaderItem(5);
        ___qtablewidgetitem22->setText(QApplication::translate("TargetDlg", "\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tbDirCommand->horizontalHeaderItem(6);
        ___qtablewidgetitem23->setText(QApplication::translate("TargetDlg", "\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tbDirCommand->horizontalHeaderItem(7);
        ___qtablewidgetitem24->setText(QApplication::translate("TargetDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tbDirCommand->horizontalHeaderItem(8);
        ___qtablewidgetitem25->setText(QApplication::translate("TargetDlg", "\345\207\272\351\224\231", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tbDirCommand->horizontalHeaderItem(9);
        ___qtablewidgetitem26->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("TargetDlg", "\347\233\256\345\275\225\344\270\255\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tbFileCommand->horizontalHeaderItem(0);
        ___qtablewidgetitem27->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tbFileCommand->horizontalHeaderItem(1);
        ___qtablewidgetitem28->setText(QApplication::translate("TargetDlg", "\346\214\207\344\273\244ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tbFileCommand->horizontalHeaderItem(2);
        ___qtablewidgetitem29->setText(QApplication::translate("TargetDlg", "\347\233\256\346\240\207\347\253\257\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tbFileCommand->horizontalHeaderItem(3);
        ___qtablewidgetitem30->setText(QApplication::translate("TargetDlg", "\346\234\254\345\234\260\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tbFileCommand->horizontalHeaderItem(4);
        ___qtablewidgetitem31->setText(QApplication::translate("TargetDlg", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tbFileCommand->horizontalHeaderItem(5);
        ___qtablewidgetitem32->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tbFileCommand->horizontalHeaderItem(6);
        ___qtablewidgetitem33->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tbFileCommand->horizontalHeaderItem(7);
        ___qtablewidgetitem34->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tbDirInfoList->horizontalHeaderItem(0);
        ___qtablewidgetitem35->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tbDirInfoList->horizontalHeaderItem(1);
        ___qtablewidgetitem36->setText(QApplication::translate("TargetDlg", "\346\214\207\344\273\244ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tbDirInfoList->horizontalHeaderItem(2);
        ___qtablewidgetitem37->setText(QApplication::translate("TargetDlg", "\347\233\256\346\240\207\347\253\257\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tbDirInfoList->horizontalHeaderItem(3);
        ___qtablewidgetitem38->setText(QApplication::translate("TargetDlg", "\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = tbDirInfoList->horizontalHeaderItem(4);
        ___qtablewidgetitem39->setText(QApplication::translate("TargetDlg", "\346\225\260\346\215\256\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = tbDirInfoList->horizontalHeaderItem(5);
        ___qtablewidgetitem40->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = tbDirInfoList->horizontalHeaderItem(6);
        ___qtablewidgetitem41->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = tbDirInfoList->horizontalHeaderItem(7);
        ___qtablewidgetitem42->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = tbUploadPluginList->horizontalHeaderItem(0);
        ___qtablewidgetitem43->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = tbUploadPluginList->horizontalHeaderItem(1);
        ___qtablewidgetitem44->setText(QApplication::translate("TargetDlg", "\344\273\273\345\212\241ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = tbUploadPluginList->horizontalHeaderItem(2);
        ___qtablewidgetitem45->setText(QApplication::translate("TargetDlg", "\346\217\222\344\273\266ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = tbUploadPluginList->horizontalHeaderItem(3);
        ___qtablewidgetitem46->setText(QApplication::translate("TargetDlg", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem47 = tbUploadPluginList->horizontalHeaderItem(4);
        ___qtablewidgetitem47->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem48 = tbUploadPluginList->horizontalHeaderItem(5);
        ___qtablewidgetitem48->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem49 = tbUploadPluginList->horizontalHeaderItem(6);
        ___qtablewidgetitem49->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem50 = tbPluginData->horizontalHeaderItem(0);
        ___qtablewidgetitem50->setText(QApplication::translate("TargetDlg", "\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem51 = tbPluginData->horizontalHeaderItem(1);
        ___qtablewidgetitem51->setText(QApplication::translate("TargetDlg", "\344\273\273\345\212\241ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem52 = tbPluginData->horizontalHeaderItem(2);
        ___qtablewidgetitem52->setText(QApplication::translate("TargetDlg", "\346\217\222\344\273\266ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem53 = tbPluginData->horizontalHeaderItem(3);
        ___qtablewidgetitem53->setText(QApplication::translate("TargetDlg", "\346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem54 = tbPluginData->horizontalHeaderItem(4);
        ___qtablewidgetitem54->setText(QApplication::translate("TargetDlg", "\350\277\234\347\253\257\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem55 = tbPluginData->horizontalHeaderItem(5);
        ___qtablewidgetitem55->setText(QApplication::translate("TargetDlg", "\346\200\273\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem56 = tbPluginData->horizontalHeaderItem(6);
        ___qtablewidgetitem56->setText(QApplication::translate("TargetDlg", "\344\270\255\350\275\254\347\274\223\345\255\230", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem57 = tbPluginData->horizontalHeaderItem(7);
        ___qtablewidgetitem57->setText(QApplication::translate("TargetDlg", "\345\267\262\345\256\214\346\210\220", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem58 = tbPluginData->horizontalHeaderItem(8);
        ___qtablewidgetitem58->setText(QApplication::translate("TargetDlg", "\345\244\207\346\263\250", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(widget), QApplication::translate("TargetDlg", "\344\273\273\345\212\241\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab), QApplication::translate("TargetDlg", "\346\226\207\344\273\266\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_8), QApplication::translate("TargetDlg", "\350\277\234\347\250\213\346\216\247\345\210\266\345\217\260", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_5), QApplication::translate("TargetDlg", "\351\253\230\347\272\247\346\226\207\344\273\266\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_2), QApplication::translate("TargetDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_3), QApplication::translate("TargetDlg", "\345\261\217\345\271\225\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_6), QApplication::translate("TargetDlg", "\345\275\225\351\237\263\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_9), QApplication::translate("TargetDlg", "\351\237\263\350\247\206\351\242\221\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_11), QApplication::translate("TargetDlg", "\345\215\263\346\227\266\351\200\232\350\256\257\345\217\226\350\257\201", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_7), QApplication::translate("TargetDlg", "\345\234\260\345\233\276\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_10), QApplication::translate("TargetDlg", "\345\244\226\351\203\250\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        tabMain->setTabText(tabMain->indexOf(tab_4), QApplication::translate("TargetDlg", "\346\227\245\345\277\227\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TargetDlg: public Ui_TargetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGETDLG_H
