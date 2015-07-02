/********************************************************************************
** Form generated from reading UI file 'filectrldlg.ui'
**
** Created: Tue Jun 30 23:21:58 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECTRLDLG_H
#define UI_FILECTRLDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "customtree.h"

QT_BEGIN_NAMESPACE

class Ui_FileCtrlDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    CustomTree *trFileCtrl;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbFileCtrl;
    QStackedWidget *stkFileCtrl;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmbAddress;
    QToolButton *btnGoto;
    QToolButton *btnFavorite;
    QToolButton *btnUp;
    QToolButton *btnRefresh;
    QToolButton *btnDelete;
    QToolButton *btnRun;
    QToolButton *btnAnalysis;
    QToolButton *btnMonitor;
    QToolButton *btnSearch;
    QTableWidget *tbFileList;
    QFrame *frame_download_bar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnUpload;
    QPushButton *btnDownload;
    QPushButton *btnDownloadDir;
    QPushButton *btnGetDirList;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_11;
    QFrame *frame1;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *edtSearchPath;
    QPushButton *btnStartSearch;
    QHBoxLayout *horizontalLayout_15;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_9;
    QCheckBox *chkSearchSubDir;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *chkFileName;
    QLineEdit *edtFileName;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *chkFileType;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *chkTxt;
    QCheckBox *chkDoc;
    QCheckBox *chkPdf;
    QCheckBox *chkXls;
    QCheckBox *chkPpt;
    QCheckBox *chkRar;
    QCheckBox *chkOtherExt;
    QLineEdit *edtFileType;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *chkFileSize;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_10;
    QRadioButton *rdSmall;
    QRadioButton *rdMiddle;
    QRadioButton *rdLarge;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QRadioButton *rdSetFileSizeArrange;
    QLineEdit *edtFileSizeFrom;
    QLabel *label_6;
    QLabel *label_8;
    QLineEdit *edtFileSizeTo;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *chkFileTime;
    QLabel *label_9;
    QDateEdit *dateFrom;
    QLabel *label_10;
    QDateEdit *dateTo;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer;
    QTableWidget *tbSearchResult;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *btnStartDownload;
    QPushButton *btnReturnFileList;

    void setupUi(QWidget *FileCtrlDlg)
    {
        if (FileCtrlDlg->objectName().isEmpty())
            FileCtrlDlg->setObjectName(QString::fromUtf8("FileCtrlDlg"));
        FileCtrlDlg->resize(890, 554);
        horizontalLayout_3 = new QHBoxLayout(FileCtrlDlg);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        trFileCtrl = new CustomTree(FileCtrlDlg);
        QIcon icon;
        icon.addFile(QString::fromUtf8("image/disklist.png"), QSize(), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(trFileCtrl);
        __qtreewidgetitem->setIcon(0, icon);
        trFileCtrl->setObjectName(QString::fromUtf8("trFileCtrl"));
        trFileCtrl->setMinimumSize(QSize(200, 0));
        trFileCtrl->setMaximumSize(QSize(200, 16777215));
        trFileCtrl->setStyleSheet(QString::fromUtf8(" QWidget\n"
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
" }\n"
"\n"
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
        trFileCtrl->setFrameShape(QFrame::NoFrame);
        trFileCtrl->setFrameShadow(QFrame::Sunken);
        trFileCtrl->setLineWidth(0);
        trFileCtrl->setIndentation(0);
        trFileCtrl->setRootIsDecorated(false);
        trFileCtrl->header()->setVisible(false);
        trFileCtrl->header()->setStretchLastSection(true);

        horizontalLayout_3->addWidget(trFileCtrl);

        frame_3 = new QFrame(FileCtrlDlg);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMaximumSize(QSize(9999, 16777215));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Plain);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        lbFileCtrl = new QLabel(frame_3);
        lbFileCtrl->setObjectName(QString::fromUtf8("lbFileCtrl"));
        lbFileCtrl->setMinimumSize(QSize(0, 35));
        lbFileCtrl->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color: #dddddd;\n"
"	padding-left:20px;\n"
"}"));

        verticalLayout_3->addWidget(lbFileCtrl);

        stkFileCtrl = new QStackedWidget(frame_3);
        stkFileCtrl->setObjectName(QString::fromUtf8("stkFileCtrl"));
        stkFileCtrl->setStyleSheet(QString::fromUtf8("QWidget#stkFileCtrl\n"
"{\n"
"	background-color:white;\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}\n"
"\n"
"QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(page);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 5, -1, 5);
        cmbAddress = new QComboBox(frame);
        cmbAddress->setObjectName(QString::fromUtf8("cmbAddress"));
        cmbAddress->setMinimumSize(QSize(20, 24));
        cmbAddress->setMaximumSize(QSize(9999, 16777215));
        cmbAddress->setStyleSheet(QString::fromUtf8(""));
        cmbAddress->setEditable(true);

        horizontalLayout->addWidget(cmbAddress);

        btnGoto = new QToolButton(frame);
        btnGoto->setObjectName(QString::fromUtf8("btnGoto"));
        btnGoto->setMinimumSize(QSize(60, 24));
        btnGoto->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color:#cccccc;\n"
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

        horizontalLayout->addWidget(btnGoto);

        btnFavorite = new QToolButton(frame);
        btnFavorite->setObjectName(QString::fromUtf8("btnFavorite"));
        btnFavorite->setMinimumSize(QSize(30, 30));
        btnFavorite->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("image/star.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnFavorite->setIcon(icon1);
        btnFavorite->setIconSize(QSize(24, 24));
        btnFavorite->setAutoRaise(true);

        horizontalLayout->addWidget(btnFavorite);

        btnUp = new QToolButton(frame);
        btnUp->setObjectName(QString::fromUtf8("btnUp"));
        btnUp->setMinimumSize(QSize(30, 30));
        btnUp->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("image/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUp->setIcon(icon2);
        btnUp->setIconSize(QSize(24, 24));
        btnUp->setAutoRaise(true);

        horizontalLayout->addWidget(btnUp);

        btnRefresh = new QToolButton(frame);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));
        btnRefresh->setMinimumSize(QSize(30, 30));
        btnRefresh->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("image/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRefresh->setIcon(icon3);
        btnRefresh->setIconSize(QSize(24, 24));
        btnRefresh->setAutoRaise(true);

        horizontalLayout->addWidget(btnRefresh);

        btnDelete = new QToolButton(frame);
        btnDelete->setObjectName(QString::fromUtf8("btnDelete"));
        btnDelete->setEnabled(false);
        btnDelete->setMinimumSize(QSize(30, 30));
        btnDelete->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("image/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDelete->setIcon(icon4);
        btnDelete->setIconSize(QSize(24, 24));
        btnDelete->setAutoRaise(true);

        horizontalLayout->addWidget(btnDelete);

        btnRun = new QToolButton(frame);
        btnRun->setObjectName(QString::fromUtf8("btnRun"));
        btnRun->setMinimumSize(QSize(30, 30));
        btnRun->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        icon5.addFile(QString::fromUtf8("image/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRun->setIcon(icon5);
        btnRun->setIconSize(QSize(24, 24));
        btnRun->setAutoRaise(true);

        horizontalLayout->addWidget(btnRun);

        btnAnalysis = new QToolButton(frame);
        btnAnalysis->setObjectName(QString::fromUtf8("btnAnalysis"));
        btnAnalysis->setMinimumSize(QSize(30, 30));
        btnAnalysis->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        icon6.addFile(QString::fromUtf8("image/analysis.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAnalysis->setIcon(icon6);
        btnAnalysis->setIconSize(QSize(24, 24));
        btnAnalysis->setAutoRaise(true);

        horizontalLayout->addWidget(btnAnalysis);

        btnMonitor = new QToolButton(frame);
        btnMonitor->setObjectName(QString::fromUtf8("btnMonitor"));
        btnMonitor->setMinimumSize(QSize(30, 30));
        btnMonitor->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        icon7.addFile(QString::fromUtf8("image/monitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMonitor->setIcon(icon7);
        btnMonitor->setIconSize(QSize(24, 24));
        btnMonitor->setAutoRaise(true);

        horizontalLayout->addWidget(btnMonitor);

        btnSearch = new QToolButton(frame);
        btnSearch->setObjectName(QString::fromUtf8("btnSearch"));
        btnSearch->setMinimumSize(QSize(30, 30));
        btnSearch->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
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
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("image/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSearch->setIcon(icon8);
        btnSearch->setIconSize(QSize(24, 24));
        btnSearch->setAutoRaise(true);

        horizontalLayout->addWidget(btnSearch);


        verticalLayout_2->addWidget(frame);

        tbFileList = new QTableWidget(page);
        if (tbFileList->columnCount() < 6)
            tbFileList->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tbFileList->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tbFileList->setObjectName(QString::fromUtf8("tbFileList"));
        tbFileList->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
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
"QTableWidget QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbFileList{\n"
"	border:0px solid #cccccc;\n"
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
"\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent"
                        ";\n"
"     width: 10px;\n"
" }\n"
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
        tbFileList->setFrameShape(QFrame::NoFrame);
        tbFileList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbFileList->setSelectionMode(QAbstractItemView::SingleSelection);
        tbFileList->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbFileList->setShowGrid(false);
        tbFileList->setSortingEnabled(false);
        tbFileList->horizontalHeader()->setHighlightSections(false);
        tbFileList->horizontalHeader()->setStretchLastSection(true);
        tbFileList->verticalHeader()->setVisible(false);
        tbFileList->verticalHeader()->setDefaultSectionSize(20);
        tbFileList->verticalHeader()->setHighlightSections(false);
        tbFileList->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tbFileList->verticalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(tbFileList);

        frame_download_bar = new QFrame(page);
        frame_download_bar->setObjectName(QString::fromUtf8("frame_download_bar"));
        frame_download_bar->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(frame_download_bar);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        btnUpload = new QPushButton(frame_download_bar);
        btnUpload->setObjectName(QString::fromUtf8("btnUpload"));
        btnUpload->setMinimumSize(QSize(70, 30));
        btnUpload->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("image/uploadfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnUpload->setIcon(icon9);

        horizontalLayout_2->addWidget(btnUpload);

        btnDownload = new QPushButton(frame_download_bar);
        btnDownload->setObjectName(QString::fromUtf8("btnDownload"));
        btnDownload->setEnabled(false);
        btnDownload->setMinimumSize(QSize(70, 30));
        btnDownload->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("image/downfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDownload->setIcon(icon10);

        horizontalLayout_2->addWidget(btnDownload);

        btnDownloadDir = new QPushButton(frame_download_bar);
        btnDownloadDir->setObjectName(QString::fromUtf8("btnDownloadDir"));
        btnDownloadDir->setMinimumSize(QSize(100, 30));
        btnDownloadDir->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("image/dirdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDownloadDir->setIcon(icon11);

        horizontalLayout_2->addWidget(btnDownloadDir);

        btnGetDirList = new QPushButton(frame_download_bar);
        btnGetDirList->setObjectName(QString::fromUtf8("btnGetDirList"));
        btnGetDirList->setMinimumSize(QSize(100, 30));
        btnGetDirList->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("image/dirfilelist.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnGetDirList->setIcon(icon12);

        horizontalLayout_2->addWidget(btnGetDirList);


        verticalLayout_2->addWidget(frame_download_bar);

        stkFileCtrl->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_11 = new QVBoxLayout(page_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        frame1 = new QFrame(page_2);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        horizontalLayout_5 = new QHBoxLayout(frame1);
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 0, -1);
        edtSearchPath = new QLineEdit(frame1);
        edtSearchPath->setObjectName(QString::fromUtf8("edtSearchPath"));
        edtSearchPath->setMinimumSize(QSize(0, 30));
        edtSearchPath->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border:1px solid #bbbbbb;\n"
"}"));

        horizontalLayout_5->addWidget(edtSearchPath);

        btnStartSearch = new QPushButton(frame1);
        btnStartSearch->setObjectName(QString::fromUtf8("btnStartSearch"));
        btnStartSearch->setMinimumSize(QSize(80, 30));
        btnStartSearch->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_5->addWidget(btnStartSearch);


        verticalLayout_11->addWidget(frame1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        frame_2 = new QFrame(page_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        verticalLayout_9 = new QVBoxLayout(frame_2);
        verticalLayout_9->setSpacing(15);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(15, -1, 0, -1);
        chkSearchSubDir = new QCheckBox(frame_2);
        chkSearchSubDir->setObjectName(QString::fromUtf8("chkSearchSubDir"));
        chkSearchSubDir->setChecked(true);

        verticalLayout_9->addWidget(chkSearchSubDir);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        chkFileName = new QCheckBox(frame_2);
        chkFileName->setObjectName(QString::fromUtf8("chkFileName"));
        chkFileName->setMinimumSize(QSize(120, 0));
        chkFileName->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_6->addWidget(chkFileName);

        edtFileName = new QLineEdit(frame_2);
        edtFileName->setObjectName(QString::fromUtf8("edtFileName"));

        horizontalLayout_6->addWidget(edtFileName);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_9->addLayout(horizontalLayout_6);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        chkFileType = new QCheckBox(frame_2);
        chkFileType->setObjectName(QString::fromUtf8("chkFileType"));
        chkFileType->setMinimumSize(QSize(120, 0));
        chkFileType->setMaximumSize(QSize(120, 16777215));

        verticalLayout_5->addWidget(chkFileType);


        horizontalLayout_9->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(10);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        chkTxt = new QCheckBox(frame_2);
        chkTxt->setObjectName(QString::fromUtf8("chkTxt"));

        horizontalLayout_7->addWidget(chkTxt);

        chkDoc = new QCheckBox(frame_2);
        chkDoc->setObjectName(QString::fromUtf8("chkDoc"));

        horizontalLayout_7->addWidget(chkDoc);

        chkPdf = new QCheckBox(frame_2);
        chkPdf->setObjectName(QString::fromUtf8("chkPdf"));

        horizontalLayout_7->addWidget(chkPdf);

        chkXls = new QCheckBox(frame_2);
        chkXls->setObjectName(QString::fromUtf8("chkXls"));

        horizontalLayout_7->addWidget(chkXls);

        chkPpt = new QCheckBox(frame_2);
        chkPpt->setObjectName(QString::fromUtf8("chkPpt"));

        horizontalLayout_7->addWidget(chkPpt);

        chkRar = new QCheckBox(frame_2);
        chkRar->setObjectName(QString::fromUtf8("chkRar"));

        horizontalLayout_7->addWidget(chkRar);

        chkOtherExt = new QCheckBox(frame_2);
        chkOtherExt->setObjectName(QString::fromUtf8("chkOtherExt"));

        horizontalLayout_7->addWidget(chkOtherExt);

        edtFileType = new QLineEdit(frame_2);
        edtFileType->setObjectName(QString::fromUtf8("edtFileType"));

        horizontalLayout_7->addWidget(edtFileType);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_7);


        horizontalLayout_9->addLayout(verticalLayout_6);


        verticalLayout_9->addLayout(horizontalLayout_9);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        chkFileSize = new QCheckBox(frame_2);
        chkFileSize->setObjectName(QString::fromUtf8("chkFileSize"));
        chkFileSize->setMinimumSize(QSize(120, 0));
        chkFileSize->setMaximumSize(QSize(120, 16777215));

        verticalLayout_7->addWidget(chkFileSize);


        horizontalLayout_12->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        rdSmall = new QRadioButton(frame_2);
        rdSmall->setObjectName(QString::fromUtf8("rdSmall"));
        rdSmall->setChecked(true);

        horizontalLayout_10->addWidget(rdSmall);

        rdMiddle = new QRadioButton(frame_2);
        rdMiddle->setObjectName(QString::fromUtf8("rdMiddle"));

        horizontalLayout_10->addWidget(rdMiddle);

        rdLarge = new QRadioButton(frame_2);
        rdLarge->setObjectName(QString::fromUtf8("rdLarge"));

        horizontalLayout_10->addWidget(rdLarge);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);


        verticalLayout_8->addLayout(horizontalLayout_10);


        horizontalLayout_12->addLayout(verticalLayout_8);


        verticalLayout_9->addLayout(horizontalLayout_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(135, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        rdSetFileSizeArrange = new QRadioButton(frame_2);
        rdSetFileSizeArrange->setObjectName(QString::fromUtf8("rdSetFileSizeArrange"));

        horizontalLayout_4->addWidget(rdSetFileSizeArrange);

        edtFileSizeFrom = new QLineEdit(frame_2);
        edtFileSizeFrom->setObjectName(QString::fromUtf8("edtFileSizeFrom"));
        edtFileSizeFrom->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(edtFileSizeFrom);

        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        label_8 = new QLabel(frame_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_4->addWidget(label_8);

        edtFileSizeTo = new QLineEdit(frame_2);
        edtFileSizeTo->setObjectName(QString::fromUtf8("edtFileSizeTo"));
        edtFileSizeTo->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_4->addWidget(edtFileSizeTo);

        label_13 = new QLabel(frame_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_4->addWidget(label_13);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_9->addLayout(horizontalLayout_4);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        chkFileTime = new QCheckBox(frame_2);
        chkFileTime->setObjectName(QString::fromUtf8("chkFileTime"));
        chkFileTime->setMinimumSize(QSize(120, 0));
        chkFileTime->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_13->addWidget(chkFileTime);

        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_13->addWidget(label_9);

        dateFrom = new QDateEdit(frame_2);
        dateFrom->setObjectName(QString::fromUtf8("dateFrom"));
        dateFrom->setCalendarPopup(true);

        horizontalLayout_13->addWidget(dateFrom);

        label_10 = new QLabel(frame_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_13->addWidget(label_10);

        dateTo = new QDateEdit(frame_2);
        dateTo->setObjectName(QString::fromUtf8("dateTo"));
        dateTo->setCalendarPopup(true);

        horizontalLayout_13->addWidget(dateTo);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_8);


        verticalLayout_9->addLayout(horizontalLayout_13);


        horizontalLayout_15->addWidget(frame_2);


        verticalLayout_11->addLayout(horizontalLayout_15);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_11->addItem(verticalSpacer);

        tbSearchResult = new QTableWidget(page_2);
        if (tbSearchResult->columnCount() < 5)
            tbSearchResult->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tbSearchResult->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tbSearchResult->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tbSearchResult->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tbSearchResult->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tbSearchResult->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        tbSearchResult->setObjectName(QString::fromUtf8("tbSearchResult"));
        tbSearchResult->setStyleSheet(QString::fromUtf8("\n"
"QHeaderView::section {\n"
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
"QTableWidget QHeaderView::section:hover {\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\n"
" }\n"
"\n"
"QTableWidget:item\n"
"{\n"
"	padding-left:10px;\n"
"}\n"
"\n"
"QFrame#tbSearchResult{\n"
"	border:1px solid #cccccc;\n"
"}\n"
"\n"
" QHeaderView::down-arrow {\n"
"     image: none;\n"
" }\n"
"\n"
" QHeaderView::up-arrow {\n"
"     image: none;\n"
" } \n"
"\n"
" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;"
                        "\n"
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
        tbSearchResult->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbSearchResult->setSelectionMode(QAbstractItemView::MultiSelection);
        tbSearchResult->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbSearchResult->setShowGrid(false);
        tbSearchResult->setSortingEnabled(false);
        tbSearchResult->horizontalHeader()->setHighlightSections(false);
        tbSearchResult->horizontalHeader()->setStretchLastSection(true);
        tbSearchResult->verticalHeader()->setVisible(false);
        tbSearchResult->verticalHeader()->setDefaultSectionSize(20);
        tbSearchResult->verticalHeader()->setHighlightSections(false);
        tbSearchResult->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_11->addWidget(tbSearchResult);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);

        btnStartDownload = new QPushButton(page_2);
        btnStartDownload->setObjectName(QString::fromUtf8("btnStartDownload"));
        btnStartDownload->setMinimumSize(QSize(80, 30));
        btnStartDownload->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_14->addWidget(btnStartDownload);

        btnReturnFileList = new QPushButton(page_2);
        btnReturnFileList->setObjectName(QString::fromUtf8("btnReturnFileList"));
        btnReturnFileList->setMinimumSize(QSize(80, 30));
        btnReturnFileList->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_14->addWidget(btnReturnFileList);


        verticalLayout_11->addLayout(horizontalLayout_14);

        stkFileCtrl->addWidget(page_2);

        verticalLayout_3->addWidget(stkFileCtrl);


        horizontalLayout_3->addWidget(frame_3);


        retranslateUi(FileCtrlDlg);

        stkFileCtrl->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FileCtrlDlg);
    } // setupUi

    void retranslateUi(QWidget *FileCtrlDlg)
    {
        FileCtrlDlg->setWindowTitle(QApplication::translate("FileCtrlDlg", "FileCtrlDlg", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trFileCtrl->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("FileCtrlDlg", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trFileCtrl->isSortingEnabled();
        trFileCtrl->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trFileCtrl->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("FileCtrlDlg", "/", 0, QApplication::UnicodeUTF8));
        trFileCtrl->setSortingEnabled(__sortingEnabled);

        lbFileCtrl->setText(QApplication::translate("FileCtrlDlg", "\346\226\207\344\273\266\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        btnGoto->setText(QApplication::translate("FileCtrlDlg", "\350\275\254\345\210\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnFavorite->setToolTip(QApplication::translate("FileCtrlDlg", "\346\267\273\345\212\240\345\210\260\346\224\266\350\227\217\345\244\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnFavorite->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnUp->setToolTip(QApplication::translate("FileCtrlDlg", "\345\220\221\344\270\212", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnUp->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnRefresh->setToolTip(QApplication::translate("FileCtrlDlg", "\345\210\267\346\226\260", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnRefresh->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("FileCtrlDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnRun->setToolTip(QApplication::translate("FileCtrlDlg", "\350\277\220\350\241\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnRun->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnAnalysis->setToolTip(QApplication::translate("FileCtrlDlg", "\346\231\272\350\203\275\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnAnalysis->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnMonitor->setToolTip(QApplication::translate("FileCtrlDlg", "\346\267\273\345\212\240\347\233\221\350\247\206", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnMonitor->setText(QApplication::translate("FileCtrlDlg", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        btnSearch->setToolTip(QApplication::translate("FileCtrlDlg", "\346\220\234\347\264\242\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btnSearch->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tbFileList->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("FileCtrlDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbFileList->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("FileCtrlDlg", "\344\277\256\346\224\271\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tbFileList->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("FileCtrlDlg", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tbFileList->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("FileCtrlDlg", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tbFileList->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("FileCtrlDlg", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tbFileList->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("FileCtrlDlg", "\351\253\230\347\272\247\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        btnUpload->setText(QApplication::translate("FileCtrlDlg", "\344\270\212\344\274\240", 0, QApplication::UnicodeUTF8));
        btnDownload->setText(QApplication::translate("FileCtrlDlg", "\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        btnDownloadDir->setText(QApplication::translate("FileCtrlDlg", "\347\233\256\345\275\225\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        btnGetDirList->setText(QApplication::translate("FileCtrlDlg", "\347\233\256\345\275\225\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        edtSearchPath->setPlaceholderText(QApplication::translate("FileCtrlDlg", "\350\276\223\345\205\245\351\234\200\350\246\201\346\220\234\347\264\242\347\232\204\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        btnStartSearch->setText(QApplication::translate("FileCtrlDlg", "\345\274\200\345\247\213\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        chkSearchSubDir->setText(QApplication::translate("FileCtrlDlg", "\346\220\234\347\264\242\345\255\220\346\226\207\344\273\266\345\244\271", 0, QApplication::UnicodeUTF8));
        chkFileName->setText(QApplication::translate("FileCtrlDlg", "\346\226\207\344\273\266\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        edtFileName->setPlaceholderText(QApplication::translate("FileCtrlDlg", "\350\276\223\345\205\245\345\205\250\351\203\250\346\210\226\351\203\250\345\210\206\346\226\207\344\273\266\345\220\215...", 0, QApplication::UnicodeUTF8));
        chkFileType->setText(QApplication::translate("FileCtrlDlg", "\346\226\207\344\273\266\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        chkTxt->setText(QApplication::translate("FileCtrlDlg", ".txt", 0, QApplication::UnicodeUTF8));
        chkDoc->setText(QApplication::translate("FileCtrlDlg", ".doc", 0, QApplication::UnicodeUTF8));
        chkPdf->setText(QApplication::translate("FileCtrlDlg", ".pdf", 0, QApplication::UnicodeUTF8));
        chkXls->setText(QApplication::translate("FileCtrlDlg", ".xls", 0, QApplication::UnicodeUTF8));
        chkPpt->setText(QApplication::translate("FileCtrlDlg", ".ppt", 0, QApplication::UnicodeUTF8));
        chkRar->setText(QApplication::translate("FileCtrlDlg", ".rar", 0, QApplication::UnicodeUTF8));
        chkOtherExt->setText(QApplication::translate("FileCtrlDlg", "\345\205\266\344\273\226", 0, QApplication::UnicodeUTF8));
        edtFileType->setText(QString());
        edtFileType->setPlaceholderText(QApplication::translate("FileCtrlDlg", ".img;.plist;", 0, QApplication::UnicodeUTF8));
        chkFileSize->setText(QApplication::translate("FileCtrlDlg", "\346\226\207\344\273\266\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        rdSmall->setText(QApplication::translate("FileCtrlDlg", "\345\260\217\357\274\210\345\260\217\344\272\216100k\357\274\211", 0, QApplication::UnicodeUTF8));
        rdMiddle->setText(QApplication::translate("FileCtrlDlg", "\344\270\255\357\274\210\345\260\217\344\272\2161M\357\274\211", 0, QApplication::UnicodeUTF8));
        rdLarge->setText(QApplication::translate("FileCtrlDlg", "\345\244\247\357\274\210\345\244\247\344\272\2161M\357\274\211", 0, QApplication::UnicodeUTF8));
        rdSetFileSizeArrange->setText(QApplication::translate("FileCtrlDlg", "\346\214\207\345\256\232\345\244\247\345\260\217\350\214\203\345\233\264   ", 0, QApplication::UnicodeUTF8));
        edtFileSizeFrom->setText(QApplication::translate("FileCtrlDlg", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FileCtrlDlg", " KB ", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("FileCtrlDlg", " -  ", 0, QApplication::UnicodeUTF8));
        edtFileSizeTo->setText(QApplication::translate("FileCtrlDlg", "100", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("FileCtrlDlg", " KB ", 0, QApplication::UnicodeUTF8));
        chkFileTime->setText(QApplication::translate("FileCtrlDlg", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("FileCtrlDlg", "\344\273\216", 0, QApplication::UnicodeUTF8));
        dateFrom->setDisplayFormat(QApplication::translate("FileCtrlDlg", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("FileCtrlDlg", "\345\210\260", 0, QApplication::UnicodeUTF8));
        dateTo->setDisplayFormat(QApplication::translate("FileCtrlDlg", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tbSearchResult->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("FileCtrlDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tbSearchResult->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("FileCtrlDlg", "\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tbSearchResult->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("FileCtrlDlg", "\345\244\247\345\260\217 (KB)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tbSearchResult->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("FileCtrlDlg", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tbSearchResult->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("FileCtrlDlg", "\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        btnStartDownload->setText(QApplication::translate("FileCtrlDlg", "\346\226\207\344\273\266\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        btnReturnFileList->setText(QApplication::translate("FileCtrlDlg", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FileCtrlDlg: public Ui_FileCtrlDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECTRLDLG_H
