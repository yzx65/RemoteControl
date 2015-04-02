/********************************************************************************
** Form generated from reading UI file 'recorddlg.ui'
**
** Created: Thu Apr 2 16:13:20 2015
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
    QTreeWidget *treeWidget_2;
    QFrame *bottom_bar;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QSpinBox *spinBox;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

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

        treeWidget_2 = new QTreeWidget(frame);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
        treeWidget_2->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(treeWidget_2);


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
        label_2 = new QLabel(bottom_bar);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(bottom_bar);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(bottom_bar);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        horizontalLayout->addWidget(checkBox_2);

        spinBox = new QSpinBox(bottom_bar);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setValue(10);

        horizontalLayout->addWidget(spinBox);

        label_3 = new QLabel(bottom_bar);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        pushButton = new QPushButton(bottom_bar);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(bottom_bar);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addWidget(bottom_bar);


        retranslateUi(RecordDlg);

        QMetaObject::connectSlotsByName(RecordDlg);
    } // setupUi

    void retranslateUi(QFrame *RecordDlg)
    {
        RecordDlg->setWindowTitle(QApplication::translate("RecordDlg", "RecordDlg", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RecordDlg", "\345\275\225\351\237\263\346\226\207\344\273\266\345\210\227\350\241\250\357\274\214\345\217\214\345\207\273\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_2->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("RecordDlg", "\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("RecordDlg", "\346\226\207\344\273\266\345\220\215", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("RecordDlg", "\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RecordDlg", "\346\255\243\345\234\250\346\222\255\346\224\276\345\275\225\351\237\263 ...", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("RecordDlg", "\345\256\236\346\227\266\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QString());
        label_3->setText(QApplication::translate("RecordDlg", "\345\210\206\351\222\237\345\220\216\350\207\252\345\212\250\345\201\234\346\255\242\345\275\225\351\237\263", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("RecordDlg", "\345\274\200\345\247\213\345\275\225\351\237\263", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("RecordDlg", "\345\201\234\346\255\242\345\275\225\351\237\263", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RecordDlg: public Ui_RecordDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDDLG_H
