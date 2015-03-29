/********************************************************************************
** Form generated from reading UI file 'mapinfodlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPINFODLG_H
#define UI_MAPINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapInfoDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *map;
    QHBoxLayout *horizontalLayout_11;
    QSplitter *spltMap;
    QTableWidget *tbLocationHistory;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_21;
    QFrame *frame_getlocation;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_15;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_12;
    QToolButton *btnGetLocation;
    QFrame *mapContainer;

    void setupUi(QWidget *MapInfoDlg)
    {
        if (MapInfoDlg->objectName().isEmpty())
            MapInfoDlg->setObjectName(QString::fromUtf8("MapInfoDlg"));
        MapInfoDlg->resize(970, 587);
        horizontalLayout = new QHBoxLayout(MapInfoDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        map = new QFrame(MapInfoDlg);
        map->setObjectName(QString::fromUtf8("map"));
        map->setStyleSheet(QString::fromUtf8("QFrame#map\n"
"{	\n"
" background-color:white;\n"
"border:1px solid #aaaaaa;\n"
" border-top-width:0px;\n"
"}"));
        map->setFrameShape(QFrame::StyledPanel);
        map->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(map);
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        spltMap = new QSplitter(map);
        spltMap->setObjectName(QString::fromUtf8("spltMap"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spltMap->sizePolicy().hasHeightForWidth());
        spltMap->setSizePolicy(sizePolicy);
        spltMap->setOrientation(Qt::Horizontal);
        spltMap->setHandleWidth(1);
        tbLocationHistory = new QTableWidget(spltMap);
        if (tbLocationHistory->columnCount() < 2)
            tbLocationHistory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbLocationHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbLocationHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbLocationHistory->setObjectName(QString::fromUtf8("tbLocationHistory"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbLocationHistory->sizePolicy().hasHeightForWidth());
        tbLocationHistory->setSizePolicy(sizePolicy1);
        tbLocationHistory->setMinimumSize(QSize(270, 0));
        tbLocationHistory->setMaximumSize(QSize(9999, 16777215));
        tbLocationHistory->setStyleSheet(QString::fromUtf8("\n"
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
"QFrame#tbLocationHistory{\n"
"	border:1px solid #aaaaaa;\n"
"	border-bottom-width:0px;\n"
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
"QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transpar"
                        "ent;\n"
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
        tbLocationHistory->setFrameShape(QFrame::NoFrame);
        tbLocationHistory->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tbLocationHistory->setSelectionMode(QAbstractItemView::SingleSelection);
        tbLocationHistory->setSelectionBehavior(QAbstractItemView::SelectRows);
        tbLocationHistory->setShowGrid(false);
        spltMap->addWidget(tbLocationHistory);
        tbLocationHistory->horizontalHeader()->setDefaultSectionSize(130);
        tbLocationHistory->horizontalHeader()->setHighlightSections(false);
        tbLocationHistory->horizontalHeader()->setMinimumSectionSize(130);
        tbLocationHistory->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tbLocationHistory->horizontalHeader()->setStretchLastSection(true);
        tbLocationHistory->verticalHeader()->setDefaultSectionSize(20);
        tbLocationHistory->verticalHeader()->setHighlightSections(false);
        tbLocationHistory->verticalHeader()->setMinimumSectionSize(20);
        layoutWidget = new QWidget(spltMap);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_21 = new QVBoxLayout(layoutWidget);
        verticalLayout_21->setSpacing(0);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(0, 0, 0, 0);
        frame_getlocation = new QFrame(layoutWidget);
        frame_getlocation->setObjectName(QString::fromUtf8("frame_getlocation"));
        frame_getlocation->setStyleSheet(QString::fromUtf8("QFrame#frame_getlocation\n"
"{\n"
"	background-color:rgb(240,240,240);\n"
"}\n"
"\n"
"QFrame#frame_getlocation\n"
"{\n"
"	border:0px solid #aaaaaa;\n"
"	border-bottom-width:1px;\n"
"}"));
        horizontalLayout_8 = new QHBoxLayout(frame_getlocation);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 6, 6, 6);
        label_15 = new QLabel(frame_getlocation);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMaximumSize(QSize(24, 24));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/image/location.png")));
        label_15->setScaledContents(true);

        horizontalLayout_8->addWidget(label_15);

        label_14 = new QLabel(frame_getlocation);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));

        horizontalLayout_8->addWidget(label_14);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        btnGetLocation = new QToolButton(frame_getlocation);
        btnGetLocation->setObjectName(QString::fromUtf8("btnGetLocation"));
        btnGetLocation->setMinimumSize(QSize(101, 38));
        btnGetLocation->setMaximumSize(QSize(101, 38));
        btnGetLocation->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}\n"
"QToolButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QToolButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/location.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnGetLocation->setIcon(icon);
        btnGetLocation->setIconSize(QSize(24, 24));
        btnGetLocation->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_8->addWidget(btnGetLocation);


        verticalLayout_21->addWidget(frame_getlocation);

        mapContainer = new QFrame(layoutWidget);
        mapContainer->setObjectName(QString::fromUtf8("mapContainer"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mapContainer->sizePolicy().hasHeightForWidth());
        mapContainer->setSizePolicy(sizePolicy2);
        mapContainer->setStyleSheet(QString::fromUtf8("QFrame#mapContainer\n"
"{\n"
"	padding:-10px;\n"
"}"));
        mapContainer->setFrameShape(QFrame::StyledPanel);
        mapContainer->setFrameShadow(QFrame::Raised);

        verticalLayout_21->addWidget(mapContainer);

        spltMap->addWidget(layoutWidget);

        horizontalLayout_11->addWidget(spltMap);


        horizontalLayout->addWidget(map);


        retranslateUi(MapInfoDlg);

        QMetaObject::connectSlotsByName(MapInfoDlg);
    } // setupUi

    void retranslateUi(QWidget *MapInfoDlg)
    {
        MapInfoDlg->setWindowTitle(QApplication::translate("MapInfoDlg", "MapInfoDlg", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbLocationHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MapInfoDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbLocationHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MapInfoDlg", "\346\211\200\345\234\250\345\234\260", 0, QApplication::UnicodeUTF8));
        label_15->setText(QString());
        label_14->setText(QApplication::translate("MapInfoDlg", "  \345\234\260\345\233\276\350\257\246\347\273\206\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        btnGetLocation->setText(QApplication::translate("MapInfoDlg", "\350\216\267\345\217\226\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapInfoDlg: public Ui_MapInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPINFODLG_H
