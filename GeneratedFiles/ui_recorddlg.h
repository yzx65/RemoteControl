/********************************************************************************
** Form generated from reading UI file 'recorddlg.ui'
**
** Created: Thu Sep 10 21:18:34 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDDLG_H
#define UI_RECORDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RecordDlg
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTreeWidget *trRecordList;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chkOpen;
    QSpinBox *spnStopInterval;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSetting;
    QFrame *bottom_bar;
    QHBoxLayout *horizontalLayout;
    QLabel *lbStatus;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStopRecord;

    void setupUi(QFrame *RecordDlg)
    {
        if (RecordDlg->objectName().isEmpty())
            RecordDlg->setObjectName(QString::fromUtf8("RecordDlg"));
        RecordDlg->resize(702, 359);
        verticalLayout_2 = new QVBoxLayout(RecordDlg);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        frame = new QFrame(RecordDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	font-size:13px;\n"
"	background-color:rgb(247,249,255);;\n"
"	color:black;\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	border:0px solid #cccccc;\n"
"	border-bottom-width:1px;\n"
"	border-top-width:0px;\n"
"}"));

        verticalLayout->addWidget(label);

        trRecordList = new QTreeWidget(frame);
        trRecordList->setObjectName(QString::fromUtf8("trRecordList"));
        trRecordList->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	/*border-right-width:0xp;*/\n"
"	font-size:13px;\n"
"}\n"
"\n"
"QTreeWidget::item\n"
"{\n"
"	min-height:30px;\n"
"	padding-left:10px;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
" QTreeWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
" }\n"
"\n"
"  QTreeWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }"));
        trRecordList->setFrameShape(QFrame::NoFrame);
        trRecordList->setIndentation(0);
        trRecordList->header()->setVisible(false);
        trRecordList->header()->setDefaultSectionSize(250);

        verticalLayout->addWidget(trRecordList);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chkOpen = new QCheckBox(frame_2);
        chkOpen->setObjectName(QString::fromUtf8("chkOpen"));

        horizontalLayout_2->addWidget(chkOpen);

        spnStopInterval = new QSpinBox(frame_2);
        spnStopInterval->setObjectName(QString::fromUtf8("spnStopInterval"));
        spnStopInterval->setMaximum(9999);
        spnStopInterval->setValue(10);

        horizontalLayout_2->addWidget(spnStopInterval);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnSetting = new QPushButton(frame_2);
        btnSetting->setObjectName(QString::fromUtf8("btnSetting"));

        horizontalLayout_2->addWidget(btnSetting);


        verticalLayout->addWidget(frame_2);


        verticalLayout_2->addWidget(frame);

        bottom_bar = new QFrame(RecordDlg);
        bottom_bar->setObjectName(QString::fromUtf8("bottom_bar"));
        bottom_bar->setStyleSheet(QString::fromUtf8("QFrame#bottom_bar\n"
"{\n"
"	border:0px solid #cccccc;\n"
"	border-top-width:1px;\n"
"	border-bottom-width:1px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(bottom_bar);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbStatus = new QLabel(bottom_bar);
        lbStatus->setObjectName(QString::fromUtf8("lbStatus"));

        horizontalLayout->addWidget(lbStatus);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnStopRecord = new QPushButton(bottom_bar);
        btnStopRecord->setObjectName(QString::fromUtf8("btnStopRecord"));

        horizontalLayout->addWidget(btnStopRecord);


        verticalLayout_2->addWidget(bottom_bar);


        retranslateUi(RecordDlg);

        QMetaObject::connectSlotsByName(RecordDlg);
    } // setupUi

    void retranslateUi(QFrame *RecordDlg)
    {
        RecordDlg->setWindowTitle(QApplication::translate("RecordDlg", "RecordDlg", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RecordDlg", "\345\275\225\351\237\263\346\226\207\344\273\266\345\210\227\350\241\250\357\274\214\345\217\214\345\207\273\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = trRecordList->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("RecordDlg", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        chkOpen->setText(QApplication::translate("RecordDlg", "\346\211\223\345\274\200\347\216\257\345\242\203\351\237\263\347\233\221\346\216\247\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RecordDlg", "\345\210\206\351\222\237\345\220\216\350\207\252\345\212\250\345\201\234\346\255\242\345\275\225\351\237\263", 0, QApplication::UnicodeUTF8));
        btnSetting->setText(QApplication::translate("RecordDlg", "\345\217\221\351\200\201\346\214\207\344\273\244", 0, QApplication::UnicodeUTF8));
        lbStatus->setText(QApplication::translate("RecordDlg", "\346\255\243\345\234\250\346\222\255\346\224\276\345\275\225\351\237\263 ...", 0, QApplication::UnicodeUTF8));
        btnStopRecord->setText(QApplication::translate("RecordDlg", "\345\201\234\346\255\242\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RecordDlg: public Ui_RecordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDDLG_H
