/********************************************************************************
** Form generated from reading UI file 'favoritenamedlg.ui'
**
** Created: Sun Sep 20 11:18:03 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAVORITENAMEDLG_H
#define UI_FAVORITENAMEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FavoriteNameDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *edtName;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnOK;

    void setupUi(QDialog *FavoriteNameDlg)
    {
        if (FavoriteNameDlg->objectName().isEmpty())
            FavoriteNameDlg->setObjectName(QString::fromUtf8("FavoriteNameDlg"));
        FavoriteNameDlg->resize(345, 61);
        FavoriteNameDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";g\n"
"}"));
        verticalLayout = new QVBoxLayout(FavoriteNameDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(FavoriteNameDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 25));

        horizontalLayout->addWidget(label_2);

        edtName = new QLineEdit(FavoriteNameDlg);
        edtName->setObjectName(QString::fromUtf8("edtName"));
        edtName->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(edtName);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnOK = new QPushButton(FavoriteNameDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(btnOK);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FavoriteNameDlg);

        QMetaObject::connectSlotsByName(FavoriteNameDlg);
    } // setupUi

    void retranslateUi(QDialog *FavoriteNameDlg)
    {
        FavoriteNameDlg->setWindowTitle(QApplication::translate("FavoriteNameDlg", "\346\267\273\345\212\240\345\210\260\346\224\266\350\227\217", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FavoriteNameDlg", "\345\220\215\347\247\260", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("FavoriteNameDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FavoriteNameDlg: public Ui_FavoriteNameDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVORITENAMEDLG_H
