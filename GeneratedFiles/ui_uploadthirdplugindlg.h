/********************************************************************************
** Form generated from reading UI file 'uploadthirdplugindlg.ui'
**
** Created: Thu Sep 10 21:18:34 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADTHIRDPLUGINDLG_H
#define UI_UPLOADTHIRDPLUGINDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UploadThirdPluginDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *edtPluginName;
    QFrame *frame1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtPluginPath;
    QPushButton *btnGetPath;
    QFrame *frameSplit;
    QFrame *frameFunc1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtInitFunction;
    QFrame *frameFunc2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *edtUnInitFunction;
    QFrame *frameDataDir;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *edtDataDir;
    QFrame *frameInterval;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QSpinBox *spnInterval;
    QLabel *label_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_8;
    QFrame *frame2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnAdvance;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;

    void setupUi(QDialog *UploadThirdPluginDlg)
    {
        if (UploadThirdPluginDlg->objectName().isEmpty())
            UploadThirdPluginDlg->setObjectName(QString::fromUtf8("UploadThirdPluginDlg"));
        UploadThirdPluginDlg->resize(418, 270);
        UploadThirdPluginDlg->setMinimumSize(QSize(413, 0));
        UploadThirdPluginDlg->setMaximumSize(QSize(418, 16777215));
        UploadThirdPluginDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(UploadThirdPluginDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 9);
        frame = new QFrame(UploadThirdPluginDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        horizontalLayout_6 = new QHBoxLayout(frame);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 5, 0);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(70, 25));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_5);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        edtPluginName = new QLineEdit(frame);
        edtPluginName->setObjectName(QString::fromUtf8("edtPluginName"));
        edtPluginName->setMinimumSize(QSize(0, 25));

        horizontalLayout_6->addWidget(edtPluginName);


        verticalLayout->addWidget(frame);

        frame1 = new QFrame(UploadThirdPluginDlg);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        horizontalLayout = new QHBoxLayout(frame1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 5, 0);
        label = new QLabel(frame1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(70, 25));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        edtPluginPath = new QLineEdit(frame1);
        edtPluginPath->setObjectName(QString::fromUtf8("edtPluginPath"));
        edtPluginPath->setMinimumSize(QSize(0, 25));
        edtPluginPath->setReadOnly(true);

        horizontalLayout->addWidget(edtPluginPath);

        btnGetPath = new QPushButton(frame1);
        btnGetPath->setObjectName(QString::fromUtf8("btnGetPath"));
        btnGetPath->setMinimumSize(QSize(0, 25));
        btnGetPath->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(btnGetPath);


        verticalLayout->addWidget(frame1);

        frameSplit = new QFrame(UploadThirdPluginDlg);
        frameSplit->setObjectName(QString::fromUtf8("frameSplit"));
        frameSplit->setFrameShape(QFrame::HLine);
        frameSplit->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frameSplit);

        frameFunc1 = new QFrame(UploadThirdPluginDlg);
        frameFunc1->setObjectName(QString::fromUtf8("frameFunc1"));
        horizontalLayout_2 = new QHBoxLayout(frameFunc1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 5, 0);
        label_2 = new QLabel(frameFunc1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(70, 25));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edtInitFunction = new QLineEdit(frameFunc1);
        edtInitFunction->setObjectName(QString::fromUtf8("edtInitFunction"));
        edtInitFunction->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(edtInitFunction);


        verticalLayout->addWidget(frameFunc1);

        frameFunc2 = new QFrame(UploadThirdPluginDlg);
        frameFunc2->setObjectName(QString::fromUtf8("frameFunc2"));
        horizontalLayout_3 = new QHBoxLayout(frameFunc2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 5, 0);
        label_3 = new QLabel(frameFunc2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(70, 25));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        edtUnInitFunction = new QLineEdit(frameFunc2);
        edtUnInitFunction->setObjectName(QString::fromUtf8("edtUnInitFunction"));
        edtUnInitFunction->setMinimumSize(QSize(0, 25));

        horizontalLayout_3->addWidget(edtUnInitFunction);


        verticalLayout->addWidget(frameFunc2);

        frameDataDir = new QFrame(UploadThirdPluginDlg);
        frameDataDir->setObjectName(QString::fromUtf8("frameDataDir"));
        horizontalLayout_4 = new QHBoxLayout(frameDataDir);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 5, 0);
        label_4 = new QLabel(frameDataDir);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(70, 25));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        edtDataDir = new QLineEdit(frameDataDir);
        edtDataDir->setObjectName(QString::fromUtf8("edtDataDir"));
        edtDataDir->setMinimumSize(QSize(0, 25));

        horizontalLayout_4->addWidget(edtDataDir);


        verticalLayout->addWidget(frameDataDir);

        frameInterval = new QFrame(UploadThirdPluginDlg);
        frameInterval->setObjectName(QString::fromUtf8("frameInterval"));
        horizontalLayout_7 = new QHBoxLayout(frameInterval);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 5, 0);
        label_6 = new QLabel(frameInterval);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(70, 25));
        label_6->setMaximumSize(QSize(16777215, 25));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_6);

        horizontalSpacer_7 = new QSpacerItem(21, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        spnInterval = new QSpinBox(frameInterval);
        spnInterval->setObjectName(QString::fromUtf8("spnInterval"));
        spnInterval->setMinimumSize(QSize(60, 25));
        spnInterval->setMaximumSize(QSize(16777215, 25));
        spnInterval->setMinimum(1);
        spnInterval->setMaximum(9999);
        spnInterval->setValue(20);

        horizontalLayout_7->addWidget(spnInterval);

        label_7 = new QLabel(frameInterval);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 25));
        label_7->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(label_7);

        label_8 = new QLabel(frameInterval);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 25));
        label_8->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(label_8);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout->addWidget(frameInterval);

        frame2 = new QFrame(UploadThirdPluginDlg);
        frame2->setObjectName(QString::fromUtf8("frame2"));
        frame2->setFrameShape(QFrame::HLine);
        frame2->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        btnAdvance = new QPushButton(UploadThirdPluginDlg);
        btnAdvance->setObjectName(QString::fromUtf8("btnAdvance"));
        btnAdvance->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(btnAdvance);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btnOK = new QPushButton(UploadThirdPluginDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(btnOK);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(UploadThirdPluginDlg);

        QMetaObject::connectSlotsByName(UploadThirdPluginDlg);
    } // setupUi

    void retranslateUi(QDialog *UploadThirdPluginDlg)
    {
        UploadThirdPluginDlg->setWindowTitle(QApplication::translate("UploadThirdPluginDlg", "\344\270\212\344\274\240\347\254\254\344\270\211\346\226\271\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UploadThirdPluginDlg", "\344\272\247\345\223\201\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UploadThirdPluginDlg", "\346\226\207\344\273\266\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        btnGetPath->setText(QApplication::translate("UploadThirdPluginDlg", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UploadThirdPluginDlg", "\345\210\235\345\247\213\345\214\226\345\207\275\346\225\260", 0, QApplication::UnicodeUTF8));
        edtInitFunction->setText(QString());
        label_3->setText(QApplication::translate("UploadThirdPluginDlg", "\345\215\270\350\275\275\345\207\275\346\225\260", 0, QApplication::UnicodeUTF8));
        edtUnInitFunction->setText(QString());
        label_4->setText(QApplication::translate("UploadThirdPluginDlg", "\346\217\222\344\273\266\346\225\260\346\215\256\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        edtDataDir->setText(QString());
        label_6->setText(QApplication::translate("UploadThirdPluginDlg", "\346\237\245\350\257\242\345\221\250\346\234\237", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("UploadThirdPluginDlg", "\347\247\222", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("UploadThirdPluginDlg", "    ( \346\257\217\351\232\224\346\214\207\345\256\232\346\227\266\351\227\264\346\237\245\350\257\242\344\270\200\346\254\241\346\225\260\346\215\256\347\233\256\345\275\225 )", 0, QApplication::UnicodeUTF8));
        btnAdvance->setText(QApplication::translate("UploadThirdPluginDlg", "\351\253\230\347\272\247\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("UploadThirdPluginDlg", "\344\270\212\344\274\240", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UploadThirdPluginDlg: public Ui_UploadThirdPluginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADTHIRDPLUGINDLG_H
