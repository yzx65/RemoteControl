/********************************************************************************
** Form generated from reading UI file 'aboutdlg.ui'
**
** Created: Sun Jun 7 19:02:08 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutDlg
{
public:
    QVBoxLayout *verticalLayout_6;
    QFrame *title;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *lbTitle;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QTabWidget *tabwideget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QTreeWidget *trWindows;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *trMac;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *trIOS;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_5;
    QTreeWidget *trAndroid;
    QFrame *frame1;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnOK;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *AboutDlg)
    {
        if (AboutDlg->objectName().isEmpty())
            AboutDlg->setObjectName(QString::fromUtf8("AboutDlg"));
        AboutDlg->resize(446, 349);
        AboutDlg->setMinimumSize(QSize(446, 0));
        AboutDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}\n"
"QWidget#AboutDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(AboutDlg);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, -1);
        title = new QFrame(AboutDlg);
        title->setObjectName(QString::fromUtf8("title"));
        title->setStyleSheet(QString::fromUtf8("QFrame#title\n"
"{\n"
"	background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,stop:0 rgba(244, 244, 255, 255), stop:1 rgba(172, 197, 224, 80));\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(title);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 15, 6, 15);
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_3 = new QLabel(title);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(32, 32));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/image/icon.png")));
        label_3->setScaledContents(true);

        horizontalLayout_2->addWidget(label_3);

        lbTitle = new QLabel(title);
        lbTitle->setObjectName(QString::fromUtf8("lbTitle"));
        lbTitle->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-size:15px;\n"
"}"));

        horizontalLayout_2->addWidget(lbTitle);


        verticalLayout_6->addWidget(title);

        frame = new QFrame(AboutDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(16777215, 60));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout_6->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label = new QLabel(AboutDlg);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_7->addWidget(label);

        tabwideget = new QTabWidget(AboutDlg);
        tabwideget->setObjectName(QString::fromUtf8("tabwideget"));
        tabwideget->setMinimumSize(QSize(300, 0));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        trWindows = new QTreeWidget(tab);
        trWindows->setObjectName(QString::fromUtf8("trWindows"));

        verticalLayout->addWidget(trWindows);

        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/windows_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabwideget->addTab(tab, icon, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        trMac = new QTreeWidget(tab_2);
        trMac->setObjectName(QString::fromUtf8("trMac"));

        verticalLayout_3->addWidget(trMac);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/mac_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabwideget->addTab(tab_2, icon1, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_4 = new QVBoxLayout(tab_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        trIOS = new QTreeWidget(tab_3);
        trIOS->setObjectName(QString::fromUtf8("trIOS"));

        verticalLayout_4->addWidget(trIOS);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/iphone_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabwideget->addTab(tab_3, icon2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_5 = new QVBoxLayout(tab_4);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        trAndroid = new QTreeWidget(tab_4);
        trAndroid->setObjectName(QString::fromUtf8("trAndroid"));

        verticalLayout_5->addWidget(trAndroid);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/android_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabwideget->addTab(tab_4, icon3, QString());

        verticalLayout_7->addWidget(tabwideget);


        horizontalLayout->addLayout(verticalLayout_7);

        frame1 = new QFrame(AboutDlg);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        verticalLayout_2 = new QVBoxLayout(frame1);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, -1, -1, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btnOK = new QPushButton(frame1);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));

        verticalLayout_2->addWidget(btnOK);


        horizontalLayout->addWidget(frame1);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_3);


        retranslateUi(AboutDlg);

        tabwideget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AboutDlg);
    } // setupUi

    void retranslateUi(QDialog *AboutDlg)
    {
        AboutDlg->setWindowTitle(QApplication::translate("AboutDlg", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        lbTitle->setText(QApplication::translate("AboutDlg", "\346\213\223\347\225\214\351\253\230\347\272\247\350\277\234\347\250\213\344\277\241\346\201\257\350\216\267\345\217\226\345\271\263\345\217\260\350\275\257\344\273\266 V1.0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AboutDlg", "\347\211\210\346\235\203\346\211\200\346\234\211 : \345\215\227\344\272\254\346\213\223\347\225\214\344\277\241\346\201\257\346\212\200\346\234\257\346\234\211\351\231\220\345\205\254\345\217\270", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AboutDlg", "\346\217\222\344\273\266\347\211\210\346\234\254\344\277\241\346\201\257\357\274\232", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trWindows->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        tabwideget->setTabText(tabwideget->indexOf(tab), QApplication::translate("AboutDlg", "Windows", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem1 = trMac->headerItem();
        ___qtreewidgetitem1->setText(1, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem1->setText(0, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        tabwideget->setTabText(tabwideget->indexOf(tab_2), QApplication::translate("AboutDlg", "Mac", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = trIOS->headerItem();
        ___qtreewidgetitem2->setText(1, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem2->setText(0, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        tabwideget->setTabText(tabwideget->indexOf(tab_3), QApplication::translate("AboutDlg", "IOS", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = trAndroid->headerItem();
        ___qtreewidgetitem3->setText(1, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\347\211\210\346\234\254", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem3->setText(0, QApplication::translate("AboutDlg", "\346\217\222\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        tabwideget->setTabText(tabwideget->indexOf(tab_4), QApplication::translate("AboutDlg", "Android", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("AboutDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutDlg: public Ui_AboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
