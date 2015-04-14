/********************************************************************************
** Form generated from reading UI file 'mapinfodlg.ui'
**
** Created: Tue Apr 14 09:44:29 2015
**      by: Qt User Interface Compiler version 4.8.4
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
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapInfoDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *map;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_21;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QFrame *mapContainer;
    QPushButton *btnGetLocation;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QTableWidget *tbLocationHistory;

    void setupUi(QWidget *MapInfoDlg)
    {
        if (MapInfoDlg->objectName().isEmpty())
            MapInfoDlg->setObjectName(QString::fromUtf8("MapInfoDlg"));
        MapInfoDlg->resize(970, 587);
        MapInfoDlg->setStyleSheet(QString::fromUtf8("QFrame#MapInfoDlg\n"
"{\n"
"	background-color:#cccccc;\n"
"}"));
        horizontalLayout = new QHBoxLayout(MapInfoDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        map = new QFrame(MapInfoDlg);
        map->setObjectName(QString::fromUtf8("map"));
        map->setStyleSheet(QString::fromUtf8("QFrame#map\n"
"{	\n"
" background-color:#cccccc;\n"
"border:1px solid #aaaaaa;\n"
" border-top-width:0px;\n"
"}"));
        map->setFrameShape(QFrame::StyledPanel);
        map->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(map);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(0);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_21->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout_21);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mapContainer = new QFrame(map);
        mapContainer->setObjectName(QString::fromUtf8("mapContainer"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapContainer->sizePolicy().hasHeightForWidth());
        mapContainer->setSizePolicy(sizePolicy);
        mapContainer->setMinimumSize(QSize(500, 300));
        mapContainer->setStyleSheet(QString::fromUtf8("QFrame#mapContainer\n"
"{\n"
"	padding:-10px;\n"
"	border:1px solid white;\n"
"	background-color:white;\n"
"}"));
        mapContainer->setFrameShape(QFrame::StyledPanel);
        mapContainer->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(mapContainer);

        btnGetLocation = new QPushButton(map);
        btnGetLocation->setObjectName(QString::fromUtf8("btnGetLocation"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnGetLocation->sizePolicy().hasHeightForWidth());
        btnGetLocation->setSizePolicy(sizePolicy1);
        btnGetLocation->setMinimumSize(QSize(101, 38));
        btnGetLocation->setMaximumSize(QSize(9999, 38));
        btnGetLocation->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
        icon.addFile(QString::fromUtf8(":/image/location.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnGetLocation->setIcon(icon);
        btnGetLocation->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(btnGetLocation);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        tbLocationHistory = new QTableWidget(map);
        if (tbLocationHistory->columnCount() < 2)
            tbLocationHistory->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbLocationHistory->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbLocationHistory->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbLocationHistory->setObjectName(QString::fromUtf8("tbLocationHistory"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbLocationHistory->sizePolicy().hasHeightForWidth());
        tbLocationHistory->setSizePolicy(sizePolicy2);
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
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-top-width:1px;\n"
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
        tbLocationHistory->horizontalHeader()->setDefaultSectionSize(130);
        tbLocationHistory->horizontalHeader()->setHighlightSections(false);
        tbLocationHistory->horizontalHeader()->setMinimumSectionSize(130);
        tbLocationHistory->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tbLocationHistory->horizontalHeader()->setStretchLastSection(true);
        tbLocationHistory->verticalHeader()->setDefaultSectionSize(20);
        tbLocationHistory->verticalHeader()->setHighlightSections(false);
        tbLocationHistory->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout_2->addWidget(tbLocationHistory);


        horizontalLayout->addWidget(map);


        retranslateUi(MapInfoDlg);

        QMetaObject::connectSlotsByName(MapInfoDlg);
    } // setupUi

    void retranslateUi(QWidget *MapInfoDlg)
    {
        MapInfoDlg->setWindowTitle(QApplication::translate("MapInfoDlg", "MapInfoDlg", 0, QApplication::UnicodeUTF8));
        btnGetLocation->setText(QApplication::translate("MapInfoDlg", "\350\216\267\345\217\226\344\275\215\347\275\256", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tbLocationHistory->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MapInfoDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tbLocationHistory->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MapInfoDlg", "\346\211\200\345\234\250\345\234\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MapInfoDlg: public Ui_MapInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPINFODLG_H
