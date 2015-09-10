/********************************************************************************
** Form generated from reading UI file 'uploadfiledlg.ui'
**
** Created: Thu Sep 10 21:18:34 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOADFILEDLG_H
#define UI_UPLOADFILEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UploadFileDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *edtLocalFile;
    QToolButton *btnBrowse;
    QLabel *label_2;
    QLineEdit *edtRemotePath;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;

    void setupUi(QDialog *UploadFileDlg)
    {
        if (UploadFileDlg->objectName().isEmpty())
            UploadFileDlg->setObjectName(QString::fromUtf8("UploadFileDlg"));
        UploadFileDlg->resize(329, 125);
        UploadFileDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(UploadFileDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, -1, 5);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(6);
        label = new QLabel(UploadFileDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(60, 0));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        edtLocalFile = new QLineEdit(UploadFileDlg);
        edtLocalFile->setObjectName(QString::fromUtf8("edtLocalFile"));
        edtLocalFile->setMinimumSize(QSize(0, 25));
        edtLocalFile->setReadOnly(true);

        gridLayout->addWidget(edtLocalFile, 0, 2, 1, 1);

        btnBrowse = new QToolButton(UploadFileDlg);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setMinimumSize(QSize(35, 25));

        gridLayout->addWidget(btnBrowse, 0, 4, 1, 1);

        label_2 = new QLabel(UploadFileDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edtRemotePath = new QLineEdit(UploadFileDlg);
        edtRemotePath->setObjectName(QString::fromUtf8("edtRemotePath"));
        edtRemotePath->setMinimumSize(QSize(0, 25));
        edtRemotePath->setReadOnly(true);

        gridLayout->addWidget(edtRemotePath, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        frame = new QFrame(UploadFileDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 15));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(UploadFileDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UploadFileDlg);

        QMetaObject::connectSlotsByName(UploadFileDlg);
    } // setupUi

    void retranslateUi(QDialog *UploadFileDlg)
    {
        UploadFileDlg->setWindowTitle(QApplication::translate("UploadFileDlg", "\344\270\212\344\274\240\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UploadFileDlg", "\346\234\254\345\234\260\346\272\220\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnBrowse->setText(QApplication::translate("UploadFileDlg", "...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UploadFileDlg", "\350\277\234\347\253\257\344\270\212\344\274\240\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("UploadFileDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UploadFileDlg: public Ui_UploadFileDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOADFILEDLG_H
