/********************************************************************************
** Form generated from reading UI file 'generatetardlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATETARDLG_H
#define UI_GENERATETARDLG_H

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
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateTarDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *edtPassword;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnGenerate;

    void setupUi(QDialog *GenerateTarDlg)
    {
        if (GenerateTarDlg->objectName().isEmpty())
            GenerateTarDlg->setObjectName(QString::fromUtf8("GenerateTarDlg"));
        GenerateTarDlg->resize(254, 125);
        GenerateTarDlg->setMinimumSize(QSize(254, 0));
        GenerateTarDlg->setMaximumSize(QSize(254, 99999));
        verticalLayout = new QVBoxLayout(GenerateTarDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(GenerateTarDlg);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 39));
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(50, 0));

        horizontalLayout_3->addWidget(label_3);

        edtPassword = new QLineEdit(frame_2);
        edtPassword->setObjectName(QString::fromUtf8("edtPassword"));

        horizontalLayout_3->addWidget(edtPassword);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(GenerateTarDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 39));
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        btnGenerate = new QPushButton(frame);
        btnGenerate->setObjectName(QString::fromUtf8("btnGenerate"));

        horizontalLayout_4->addWidget(btnGenerate);


        verticalLayout->addWidget(frame);


        retranslateUi(GenerateTarDlg);

        QMetaObject::connectSlotsByName(GenerateTarDlg);
    } // setupUi

    void retranslateUi(QDialog *GenerateTarDlg)
    {
        GenerateTarDlg->setWindowTitle(QApplication::translate("GenerateTarDlg", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GenerateTarDlg", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        btnGenerate->setText(QApplication::translate("GenerateTarDlg", "\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GenerateTarDlg: public Ui_GenerateTarDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETARDLG_H
