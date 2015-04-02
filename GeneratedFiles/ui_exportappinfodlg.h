/********************************************************************************
** Form generated from reading UI file 'exportappinfodlg.ui'
**
** Created: Thu Apr 2 16:13:20 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTAPPINFODLG_H
#define UI_EXPORTAPPINFODLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ExportAppInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lbText;
    QProgressBar *progress;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnCancel;

    void setupUi(QDialog *ExportAppInfoDlg)
    {
        if (ExportAppInfoDlg->objectName().isEmpty())
            ExportAppInfoDlg->setObjectName(QString::fromUtf8("ExportAppInfoDlg"));
        ExportAppInfoDlg->resize(523, 120);
        ExportAppInfoDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(ExportAppInfoDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lbText = new QLabel(ExportAppInfoDlg);
        lbText->setObjectName(QString::fromUtf8("lbText"));

        verticalLayout->addWidget(lbText);

        progress = new QProgressBar(ExportAppInfoDlg);
        progress->setObjectName(QString::fromUtf8("progress"));
        progress->setValue(0);
        progress->setTextVisible(false);

        verticalLayout->addWidget(progress);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnCancel = new QPushButton(ExportAppInfoDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ExportAppInfoDlg);

        QMetaObject::connectSlotsByName(ExportAppInfoDlg);
    } // setupUi

    void retranslateUi(QDialog *ExportAppInfoDlg)
    {
        ExportAppInfoDlg->setWindowTitle(QString());
        lbText->setText(QApplication::translate("ExportAppInfoDlg", "\346\255\243\345\234\250\345\257\274\345\207\272\347\254\254 1 \346\235\241\350\201\212\345\244\251\350\256\260\345\275\225 ...", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("ExportAppInfoDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ExportAppInfoDlg: public Ui_ExportAppInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTAPPINFODLG_H
