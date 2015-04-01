/********************************************************************************
** Form generated from reading UI file 'policydlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLICYDLG_H
#define UI_POLICYDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PolicyDlg
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_8;
    QCheckBox *chkFileOp;
    QCheckBox *chkProcessOp;
    QCheckBox *chkKeyboardOp;
    QCheckBox *chkExecuteOp;
    QCheckBox *chkClipboardOp;
    QGroupBox *grpPassword;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *chkEA_PASSWORD;
    QCheckBox *chkKeyword;
    QLineEdit *edtKeyword;
    QGroupBox *grpDeleteFile;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_14;
    QLineEdit *edtDeleteFileExt;
    QGroupBox *grpHttps;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *chkHttpsSend;
    QCheckBox *chkHttpsReceive;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *grpUsb;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *chkUsbPlug;
    QCheckBox *chkUsbDir;
    QCheckBox *chkUsbFileRetrieve;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_15;
    QLineEdit *edtUsbExt;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_16;
    QSpinBox *spnUsbFileSize;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_13;
    QCheckBox *chkScreenManual_2;
    QCheckBox *chkSmartCapture;
    QHBoxLayout *horizontalLayout_15;
    QLabel *lbProcess;
    QLineEdit *edtProcName;
    QHBoxLayout *horizontalLayout_16;
    QLabel *lbKeyword;
    QLineEdit *edtWindowTitle;
    QHBoxLayout *horizontalLayout_17;
    QLabel *lbInterval;
    QSpinBox *spnInterval;
    QLabel *lbSecond;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *PolicyDlg)
    {
        if (PolicyDlg->objectName().isEmpty())
            PolicyDlg->setObjectName(QString::fromUtf8("PolicyDlg"));
        PolicyDlg->resize(400, 407);
        verticalLayout = new QVBoxLayout(PolicyDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(PolicyDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tab_5->setStyleSheet(QString::fromUtf8("QWidget#tab_3\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        verticalLayout_9 = new QVBoxLayout(tab_5);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox_9 = new QGroupBox(tab_5);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        gridLayout_8 = new QGridLayout(groupBox_9);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        chkFileOp = new QCheckBox(groupBox_9);
        chkFileOp->setObjectName(QString::fromUtf8("chkFileOp"));
        chkFileOp->setChecked(true);

        gridLayout_8->addWidget(chkFileOp, 0, 0, 1, 1);

        chkProcessOp = new QCheckBox(groupBox_9);
        chkProcessOp->setObjectName(QString::fromUtf8("chkProcessOp"));

        gridLayout_8->addWidget(chkProcessOp, 0, 1, 1, 1);

        chkKeyboardOp = new QCheckBox(groupBox_9);
        chkKeyboardOp->setObjectName(QString::fromUtf8("chkKeyboardOp"));
        chkKeyboardOp->setChecked(true);

        gridLayout_8->addWidget(chkKeyboardOp, 1, 0, 1, 1);

        chkExecuteOp = new QCheckBox(groupBox_9);
        chkExecuteOp->setObjectName(QString::fromUtf8("chkExecuteOp"));

        gridLayout_8->addWidget(chkExecuteOp, 1, 1, 1, 1);

        chkClipboardOp = new QCheckBox(groupBox_9);
        chkClipboardOp->setObjectName(QString::fromUtf8("chkClipboardOp"));
        chkClipboardOp->setChecked(true);

        gridLayout_8->addWidget(chkClipboardOp, 2, 0, 1, 1);


        verticalLayout_9->addWidget(groupBox_9);

        grpPassword = new QGroupBox(tab_5);
        grpPassword->setObjectName(QString::fromUtf8("grpPassword"));
        grpPassword->setCheckable(true);
        verticalLayout_10 = new QVBoxLayout(grpPassword);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        chkEA_PASSWORD = new QCheckBox(grpPassword);
        chkEA_PASSWORD->setObjectName(QString::fromUtf8("chkEA_PASSWORD"));
        chkEA_PASSWORD->setChecked(true);

        verticalLayout_10->addWidget(chkEA_PASSWORD);

        chkKeyword = new QCheckBox(grpPassword);
        chkKeyword->setObjectName(QString::fromUtf8("chkKeyword"));
        chkKeyword->setChecked(true);

        verticalLayout_10->addWidget(chkKeyword);

        edtKeyword = new QLineEdit(grpPassword);
        edtKeyword->setObjectName(QString::fromUtf8("edtKeyword"));

        verticalLayout_10->addWidget(edtKeyword);


        verticalLayout_9->addWidget(grpPassword);

        grpDeleteFile = new QGroupBox(tab_5);
        grpDeleteFile->setObjectName(QString::fromUtf8("grpDeleteFile"));
        grpDeleteFile->setCheckable(true);
        horizontalLayout_11 = new QHBoxLayout(grpDeleteFile);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_14 = new QLabel(grpDeleteFile);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_11->addWidget(label_14);

        edtDeleteFileExt = new QLineEdit(grpDeleteFile);
        edtDeleteFileExt->setObjectName(QString::fromUtf8("edtDeleteFileExt"));

        horizontalLayout_11->addWidget(edtDeleteFileExt);


        verticalLayout_9->addWidget(grpDeleteFile);

        grpHttps = new QGroupBox(tab_5);
        grpHttps->setObjectName(QString::fromUtf8("grpHttps"));
        grpHttps->setCheckable(true);
        horizontalLayout_12 = new QHBoxLayout(grpHttps);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        chkHttpsSend = new QCheckBox(grpHttps);
        chkHttpsSend->setObjectName(QString::fromUtf8("chkHttpsSend"));
        chkHttpsSend->setChecked(true);

        horizontalLayout_12->addWidget(chkHttpsSend);

        chkHttpsReceive = new QCheckBox(grpHttps);
        chkHttpsReceive->setObjectName(QString::fromUtf8("chkHttpsReceive"));

        horizontalLayout_12->addWidget(chkHttpsReceive);


        verticalLayout_9->addWidget(grpHttps);

        verticalSpacer_5 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_5);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        tab_6->setStyleSheet(QString::fromUtf8("QWidget#tab_2\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        verticalLayout_11 = new QVBoxLayout(tab_6);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        grpUsb = new QGroupBox(tab_6);
        grpUsb->setObjectName(QString::fromUtf8("grpUsb"));
        verticalLayout_12 = new QVBoxLayout(grpUsb);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        chkUsbPlug = new QCheckBox(grpUsb);
        chkUsbPlug->setObjectName(QString::fromUtf8("chkUsbPlug"));
        chkUsbPlug->setChecked(true);

        verticalLayout_12->addWidget(chkUsbPlug);

        chkUsbDir = new QCheckBox(grpUsb);
        chkUsbDir->setObjectName(QString::fromUtf8("chkUsbDir"));
        chkUsbDir->setChecked(true);

        verticalLayout_12->addWidget(chkUsbDir);

        chkUsbFileRetrieve = new QCheckBox(grpUsb);
        chkUsbFileRetrieve->setObjectName(QString::fromUtf8("chkUsbFileRetrieve"));
        chkUsbFileRetrieve->setChecked(true);

        verticalLayout_12->addWidget(chkUsbFileRetrieve);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_15 = new QLabel(grpUsb);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(96, 0));

        horizontalLayout_13->addWidget(label_15);

        edtUsbExt = new QLineEdit(grpUsb);
        edtUsbExt->setObjectName(QString::fromUtf8("edtUsbExt"));

        horizontalLayout_13->addWidget(edtUsbExt);


        verticalLayout_12->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_16 = new QLabel(grpUsb);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_14->addWidget(label_16);

        spnUsbFileSize = new QSpinBox(grpUsb);
        spnUsbFileSize->setObjectName(QString::fromUtf8("spnUsbFileSize"));
        spnUsbFileSize->setValue(50);

        horizontalLayout_14->addWidget(spnUsbFileSize);

        label_17 = new QLabel(grpUsb);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_14->addWidget(label_17);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);


        verticalLayout_12->addLayout(horizontalLayout_14);


        verticalLayout_11->addWidget(grpUsb);

        groupBox_10 = new QGroupBox(tab_6);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout_13 = new QVBoxLayout(groupBox_10);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        chkScreenManual_2 = new QCheckBox(groupBox_10);
        chkScreenManual_2->setObjectName(QString::fromUtf8("chkScreenManual_2"));
        chkScreenManual_2->setEnabled(false);
        chkScreenManual_2->setChecked(true);

        verticalLayout_13->addWidget(chkScreenManual_2);

        chkSmartCapture = new QCheckBox(groupBox_10);
        chkSmartCapture->setObjectName(QString::fromUtf8("chkSmartCapture"));
        chkSmartCapture->setChecked(true);

        verticalLayout_13->addWidget(chkSmartCapture);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        lbProcess = new QLabel(groupBox_10);
        lbProcess->setObjectName(QString::fromUtf8("lbProcess"));
        lbProcess->setMinimumSize(QSize(72, 0));

        horizontalLayout_15->addWidget(lbProcess);

        edtProcName = new QLineEdit(groupBox_10);
        edtProcName->setObjectName(QString::fromUtf8("edtProcName"));

        horizontalLayout_15->addWidget(edtProcName);


        verticalLayout_13->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        lbKeyword = new QLabel(groupBox_10);
        lbKeyword->setObjectName(QString::fromUtf8("lbKeyword"));
        lbKeyword->setMinimumSize(QSize(72, 0));

        horizontalLayout_16->addWidget(lbKeyword);

        edtWindowTitle = new QLineEdit(groupBox_10);
        edtWindowTitle->setObjectName(QString::fromUtf8("edtWindowTitle"));

        horizontalLayout_16->addWidget(edtWindowTitle);


        verticalLayout_13->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        lbInterval = new QLabel(groupBox_10);
        lbInterval->setObjectName(QString::fromUtf8("lbInterval"));

        horizontalLayout_17->addWidget(lbInterval);

        spnInterval = new QSpinBox(groupBox_10);
        spnInterval->setObjectName(QString::fromUtf8("spnInterval"));
        spnInterval->setMinimum(20);
        spnInterval->setValue(20);

        horizontalLayout_17->addWidget(spnInterval);

        lbSecond = new QLabel(groupBox_10);
        lbSecond->setObjectName(QString::fromUtf8("lbSecond"));

        horizontalLayout_17->addWidget(lbSecond);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_5);


        verticalLayout_13->addLayout(horizontalLayout_17);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_6);


        verticalLayout_11->addWidget(groupBox_10);

        tabWidget->addTab(tab_6, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(PolicyDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        horizontalLayout->addWidget(btnOk);

        btnCancel = new QPushButton(PolicyDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PolicyDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PolicyDlg);
    } // setupUi

    void retranslateUi(QDialog *PolicyDlg)
    {
        PolicyDlg->setWindowTitle(QApplication::translate("PolicyDlg", "\346\217\222\344\273\266\347\255\226\347\225\245\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("PolicyDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkFileOp->setText(QApplication::translate("PolicyDlg", "\347\224\250\346\210\267\346\226\207\344\273\266\346\223\215\344\275\234\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkProcessOp->setText(QApplication::translate("PolicyDlg", "\350\277\233\347\250\213\346\226\207\344\273\266\350\256\277\351\227\256\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkKeyboardOp->setText(QApplication::translate("PolicyDlg", "\351\224\256\347\233\230\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkExecuteOp->setText(QApplication::translate("PolicyDlg", "\350\277\233\347\250\213\346\211\247\350\241\214\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkClipboardOp->setText(QApplication::translate("PolicyDlg", "\345\211\252\350\264\264\346\235\277\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        grpPassword->setTitle(QApplication::translate("PolicyDlg", "Win32\347\250\213\345\272\217\"\345\257\206\347\240\201\347\252\227\345\217\243\"\350\207\252\345\212\250\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        chkEA_PASSWORD->setText(QApplication::translate("PolicyDlg", "\347\274\226\350\276\221\346\241\206EA_PASSWORD\345\261\236\346\200\247\345\214\271\351\205\215", 0, QApplication::UnicodeUTF8));
        chkKeyword->setText(QApplication::translate("PolicyDlg", "\347\252\227\345\217\243\346\240\207\351\242\230\345\205\263\351\224\256\345\255\227\345\214\271\351\205\215[\346\224\257\346\214\201\345\244\232\345\233\275\350\257\255\350\250\200]", 0, QApplication::UnicodeUTF8));
        edtKeyword->setText(QApplication::translate("PolicyDlg", "\345\257\206\347\240\201;\345\217\243\344\273\244;Password;", 0, QApplication::UnicodeUTF8));
        grpDeleteFile->setTitle(QApplication::translate("PolicyDlg", "\345\210\240\351\231\244\346\226\207\344\273\266\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("PolicyDlg", "\346\211\251\345\261\225\345\220\215\350\277\207\346\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        edtDeleteFileExt->setText(QApplication::translate("PolicyDlg", "*.doc;*.ppt;*.xls;*.docx;*.pptx;*.xlsx;", 0, QApplication::UnicodeUTF8));
        grpHttps->setTitle(QApplication::translate("PolicyDlg", "https\346\212\245\346\226\207\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        chkHttpsSend->setText(QApplication::translate("PolicyDlg", "\347\233\221\346\216\247\345\217\221\351\200\201\346\212\245\346\226\207", 0, QApplication::UnicodeUTF8));
        chkHttpsReceive->setText(QApplication::translate("PolicyDlg", "\347\233\221\346\216\247\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("PolicyDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        grpUsb->setTitle(QApplication::translate("PolicyDlg", "USB\346\226\207\344\273\266\345\257\206\345\217\226\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkUsbPlug->setText(QApplication::translate("PolicyDlg", "USB\350\256\276\345\244\207\346\217\222\346\213\224\350\241\214\344\270\272\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        chkUsbDir->setText(QApplication::translate("PolicyDlg", "USB\347\233\256\345\275\225\345\210\227\350\241\250\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        chkUsbFileRetrieve->setText(QApplication::translate("PolicyDlg", "USB\346\226\207\344\273\266\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("PolicyDlg", "\346\226\207\344\273\266\346\211\251\345\261\225\345\220\215\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        edtUsbExt->setText(QApplication::translate("PolicyDlg", "*.doc;*.ppt;*.xls;*.docx;*.pptx;*.xlsx;", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("PolicyDlg", "\350\216\267\345\217\226\346\226\207\344\273\266\346\234\200\345\244\247\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("PolicyDlg", "MB", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("PolicyDlg", "\345\261\217\345\271\225\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkScreenManual_2->setText(QApplication::translate("PolicyDlg", "\346\211\213\345\267\245\346\210\252\345\217\226\347\233\256\346\240\207\345\261\217\345\271\225", 0, QApplication::UnicodeUTF8));
        chkSmartCapture->setText(QApplication::translate("PolicyDlg", "\346\231\272\350\203\275\346\210\252\345\217\226\347\233\256\346\240\207\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        lbProcess->setText(QApplication::translate("PolicyDlg", "\350\277\233\347\250\213\345\220\215\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        edtProcName->setText(QApplication::translate("PolicyDlg", "notepad;", 0, QApplication::UnicodeUTF8));
        lbKeyword->setText(QApplication::translate("PolicyDlg", "\347\252\227\345\217\243\345\205\263\351\224\256\345\255\227", 0, QApplication::UnicodeUTF8));
        edtWindowTitle->setText(QString());
        lbInterval->setText(QApplication::translate("PolicyDlg", "\347\252\227\345\217\243\346\210\252\345\217\226\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        lbSecond->setText(QApplication::translate("PolicyDlg", "\347\247\222", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("PolicyDlg", "USB\345\217\212\345\261\217\345\271\225\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("PolicyDlg", "\346\233\264\346\226\260", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("PolicyDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PolicyDlg: public Ui_PolicyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLICYDLG_H
