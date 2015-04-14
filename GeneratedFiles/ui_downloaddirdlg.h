/********************************************************************************
** Form generated from reading UI file 'downloaddirdlg.ui'
**
** Created: Tue Apr 14 09:44:29 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADDIRDLG_H
#define UI_DOWNLOADDIRDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
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

class Ui_DownloadDirDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *edtDir;
    QFrame *frmLevel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpinBox *spnLevel;
    QFrame *frame1;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkAllLevel;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;

    void setupUi(QDialog *DownloadDirDlg)
    {
        if (DownloadDirDlg->objectName().isEmpty())
            DownloadDirDlg->setObjectName(QString::fromUtf8("DownloadDirDlg"));
        DownloadDirDlg->resize(300, 132);
        DownloadDirDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(DownloadDirDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(DownloadDirDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(60, 25));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_2->addWidget(label);

        edtDir = new QLineEdit(frame);
        edtDir->setObjectName(QString::fromUtf8("edtDir"));
        edtDir->setMinimumSize(QSize(216, 25));
        edtDir->setReadOnly(true);

        horizontalLayout_2->addWidget(edtDir);


        verticalLayout->addWidget(frame);

        frmLevel = new QFrame(DownloadDirDlg);
        frmLevel->setObjectName(QString::fromUtf8("frmLevel"));
        frmLevel->setMinimumSize(QSize(282, 0));
        frmLevel->setMaximumSize(QSize(282, 16777215));
        horizontalLayout_3 = new QHBoxLayout(frmLevel);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(frmLevel);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(60, 25));
        label_2->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(label_2);

        spnLevel = new QSpinBox(frmLevel);
        spnLevel->setObjectName(QString::fromUtf8("spnLevel"));
        spnLevel->setMinimumSize(QSize(100, 25));
        spnLevel->setMinimum(1);

        horizontalLayout_3->addWidget(spnLevel);


        verticalLayout->addWidget(frmLevel);

        frame1 = new QFrame(DownloadDirDlg);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        frame1->setFrameShape(QFrame::HLine);
        frame1->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkAllLevel = new QCheckBox(DownloadDirDlg);
        chkAllLevel->setObjectName(QString::fromUtf8("chkAllLevel"));
        chkAllLevel->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(chkAllLevel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(DownloadDirDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DownloadDirDlg);

        QMetaObject::connectSlotsByName(DownloadDirDlg);
    } // setupUi

    void retranslateUi(QDialog *DownloadDirDlg)
    {
        DownloadDirDlg->setWindowTitle(QApplication::translate("DownloadDirDlg", "\347\233\256\345\275\225\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DownloadDirDlg", "\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DownloadDirDlg", "\347\233\256\345\275\225\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        chkAllLevel->setText(QApplication::translate("DownloadDirDlg", "\344\270\213\350\275\275\346\211\200\346\234\211\345\261\202\346\254\241\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("DownloadDirDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DownloadDirDlg: public Ui_DownloadDirDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADDIRDLG_H
