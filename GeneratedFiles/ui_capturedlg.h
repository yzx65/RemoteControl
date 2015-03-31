/********************************************************************************
** Form generated from reading UI file 'capturedlg.ui'
**
** Created: Tue Mar 31 15:29:23 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTUREDLG_H
#define UI_CAPTUREDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <piccontainer.h>

QT_BEGIN_NAMESPACE

class Ui_CaptureDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame_63;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_setting;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *lbCaptureWindow;
    QToolButton *btnModifyPolicy;
    QFrame *frm1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbProcess;
    QSpacerItem *horizontalSpacer;
    QLineEdit *edtProcList;
    QFrame *frm2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbKeyword;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtKeyWord;
    QTreeWidget *trScreenshot;
    QTableWidget *tbScreenshot;
    QVBoxLayout *verticalLayout_147;
    PicContainer *screenView;
    QFrame *frame123;
    QHBoxLayout *horizontalLayout_219;
    QPushButton *btnCaptureScreen;

    void setupUi(QWidget *CaptureDlg)
    {
        if (CaptureDlg->objectName().isEmpty())
            CaptureDlg->setObjectName(QString::fromUtf8("CaptureDlg"));
        CaptureDlg->resize(952, 579);
        horizontalLayout = new QHBoxLayout(CaptureDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_63 = new QFrame(CaptureDlg);
        frame_63->setObjectName(QString::fromUtf8("frame_63"));
        frame_63->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(frame_63);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame_setting = new QFrame(frame_63);
        frame_setting->setObjectName(QString::fromUtf8("frame_setting"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_setting->sizePolicy().hasHeightForWidth());
        frame_setting->setSizePolicy(sizePolicy);
        frame_setting->setMinimumSize(QSize(0, 40));
        frame_setting->setMaximumSize(QSize(200, 16777215));
        frame_setting->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}\n"
"\n"
"QFrame#frame\n"
"{\n"
"	background-color:white;\n"
"	border:0px solid #cccccc;\n"
"	border-right-width:1px;\n"
"}"));
        frame_setting->setFrameShape(QFrame::StyledPanel);
        frame_setting->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_setting);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        frame_2 = new QFrame(frame_setting);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame_2);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setMaximumSize(QSize(80, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        lbCaptureWindow = new QLabel(frame_2);
        lbCaptureWindow->setObjectName(QString::fromUtf8("lbCaptureWindow"));

        horizontalLayout_4->addWidget(lbCaptureWindow);

        btnModifyPolicy = new QToolButton(frame_2);
        btnModifyPolicy->setObjectName(QString::fromUtf8("btnModifyPolicy"));
        btnModifyPolicy->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	border:none;\n"
"	font-family:\"Microsoft Yahei\";\n"
"	color:rgb(0, 0, 255);\n"
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

        horizontalLayout_4->addWidget(btnModifyPolicy);


        verticalLayout->addWidget(frame_2);

        frm1 = new QFrame(frame_setting);
        frm1->setObjectName(QString::fromUtf8("frm1"));
        horizontalLayout_3 = new QHBoxLayout(frm1);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lbProcess = new QLabel(frm1);
        lbProcess->setObjectName(QString::fromUtf8("lbProcess"));
        lbProcess->setMinimumSize(QSize(80, 0));
        lbProcess->setMaximumSize(QSize(80, 16777215));
        lbProcess->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(lbProcess);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        edtProcList = new QLineEdit(frm1);
        edtProcList->setObjectName(QString::fromUtf8("edtProcList"));
        edtProcList->setReadOnly(true);

        horizontalLayout_3->addWidget(edtProcList);


        verticalLayout->addWidget(frm1);

        frm2 = new QFrame(frame_setting);
        frm2->setObjectName(QString::fromUtf8("frm2"));
        horizontalLayout_2 = new QHBoxLayout(frm2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbKeyword = new QLabel(frm2);
        lbKeyword->setObjectName(QString::fromUtf8("lbKeyword"));
        lbKeyword->setMinimumSize(QSize(80, 0));
        lbKeyword->setMaximumSize(QSize(80, 16777215));
        lbKeyword->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lbKeyword);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        edtKeyWord = new QLineEdit(frm2);
        edtKeyWord->setObjectName(QString::fromUtf8("edtKeyWord"));
        edtKeyWord->setReadOnly(true);

        horizontalLayout_2->addWidget(edtKeyWord);


        verticalLayout->addWidget(frm2);


        verticalLayout_2->addWidget(frame_setting);

        trScreenshot = new QTreeWidget(frame_63);
        new QTreeWidgetItem(trScreenshot);
        trScreenshot->setObjectName(QString::fromUtf8("trScreenshot"));
        trScreenshot->setMinimumSize(QSize(200, 0));
        trScreenshot->setMaximumSize(QSize(200, 16777215));
        trScreenshot->setStyleSheet(QString::fromUtf8(" QWidget\n"
" {\n"
"	border:0px solid #cccccc;\n"
"	border-right-width:1px;\n"
"	border-bottom-width:1px;\n"
"	border-left-width:1px;\n"
"	background-color:rgb(240,240,240);\n"
" }"));
        trScreenshot->setFrameShape(QFrame::NoFrame);
        trScreenshot->setAlternatingRowColors(true);
        trScreenshot->setIconSize(QSize(24, 24));
        trScreenshot->setIndentation(20);
        trScreenshot->setRootIsDecorated(true);
        trScreenshot->header()->setVisible(false);

        verticalLayout_2->addWidget(trScreenshot);

        tbScreenshot = new QTableWidget(frame_63);
        if (tbScreenshot->columnCount() < 2)
            tbScreenshot->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbScreenshot->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbScreenshot->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbScreenshot->setObjectName(QString::fromUtf8("tbScreenshot"));
        tbScreenshot->setMinimumSize(QSize(200, 0));
        tbScreenshot->setMaximumSize(QSize(200, 16777215));
        tbScreenshot->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbScreenshot{\n"
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
"QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vert"
                        "ical {\n"
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
        tbScreenshot->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbScreenshot->setSelectionMode(QAbstractItemView::SingleSelection);
        tbScreenshot->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbScreenshot->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbScreenshot->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tbScreenshot->setShowGrid(false);
        tbScreenshot->horizontalHeader()->setHighlightSections(false);
        tbScreenshot->horizontalHeader()->setMinimumSectionSize(20);
        tbScreenshot->horizontalHeader()->setStretchLastSection(true);
        tbScreenshot->verticalHeader()->setVisible(false);
        tbScreenshot->verticalHeader()->setDefaultSectionSize(20);
        tbScreenshot->verticalHeader()->setHighlightSections(false);
        tbScreenshot->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_2->addWidget(tbScreenshot);


        horizontalLayout->addWidget(frame_63);

        verticalLayout_147 = new QVBoxLayout();
        verticalLayout_147->setSpacing(0);
        verticalLayout_147->setObjectName(QString::fromUtf8("verticalLayout_147"));
        verticalLayout_147->setContentsMargins(-1, -1, -1, 0);
        screenView = new PicContainer(CaptureDlg);
        screenView->setObjectName(QString::fromUtf8("screenView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(screenView->sizePolicy().hasHeightForWidth());
        screenView->setSizePolicy(sizePolicy1);

        verticalLayout_147->addWidget(screenView);

        frame123 = new QFrame(CaptureDlg);
        frame123->setObjectName(QString::fromUtf8("frame123"));
        frame123->setStyleSheet(QString::fromUtf8("QFrame#frame123\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        horizontalLayout_219 = new QHBoxLayout(frame123);
        horizontalLayout_219->setSpacing(6);
        horizontalLayout_219->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_219->setObjectName(QString::fromUtf8("horizontalLayout_219"));
        btnCaptureScreen = new QPushButton(frame123);
        btnCaptureScreen->setObjectName(QString::fromUtf8("btnCaptureScreen"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnCaptureScreen->sizePolicy().hasHeightForWidth());
        btnCaptureScreen->setSizePolicy(sizePolicy2);
        btnCaptureScreen->setMinimumSize(QSize(101, 38));
        btnCaptureScreen->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	border:0px solid #aaaaaa;\n"
"	color:white;\n"
"	padding-left:5px;\n"
"	background-color:transparent;\n"
"	text-align:center;\n"
"	background-color:rgb(46,52,52);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color:rgb(128,188,255);\n"
"	margin:1px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/capture.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCaptureScreen->setIcon(icon);
        btnCaptureScreen->setIconSize(QSize(24, 24));

        horizontalLayout_219->addWidget(btnCaptureScreen);


        verticalLayout_147->addWidget(frame123);


        horizontalLayout->addLayout(verticalLayout_147);


        retranslateUi(CaptureDlg);

        QMetaObject::connectSlotsByName(CaptureDlg);
    } // setupUi

    void retranslateUi(QWidget *CaptureDlg)
    {
        CaptureDlg->setWindowTitle(QApplication::translate("CaptureDlg", "CaptureDlg", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CaptureDlg", "\346\210\252\345\217\226\347\233\256\346\240\207\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        lbCaptureWindow->setText(QApplication::translate("CaptureDlg", "TextLabel", 0, QApplication::UnicodeUTF8));
        btnModifyPolicy->setText(QApplication::translate("CaptureDlg", "\344\277\256\346\224\271", 0, QApplication::UnicodeUTF8));
        lbProcess->setText(QApplication::translate("CaptureDlg", "\350\277\233\347\250\213\345\220\215\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        lbKeyword->setText(QApplication::translate("CaptureDlg", "\345\205\263\351\224\256\350\257\215\345\214\271\351\205\215", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trScreenshot->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("CaptureDlg", "1", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = trScreenshot->isSortingEnabled();
        trScreenshot->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = trScreenshot->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("CaptureDlg", "\346\240\271\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        trScreenshot->setSortingEnabled(__sortingEnabled);

        QTableWidgetItem *___qtablewidgetitem = tbScreenshot->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CaptureDlg", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbScreenshot->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CaptureDlg", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        btnCaptureScreen->setText(QApplication::translate("CaptureDlg", "   \345\205\250\345\261\217\346\210\252\345\233\276     ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CaptureDlg: public Ui_CaptureDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTUREDLG_H
