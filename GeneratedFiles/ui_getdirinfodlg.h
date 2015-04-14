/********************************************************************************
** Form generated from reading UI file 'getdirinfodlg.ui'
**
** Created: Tue Apr 14 09:44:29 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETDIRINFODLG_H
#define UI_GETDIRINFODLG_H

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

class Ui_GetDirInfoDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *edtDir;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spnLevel;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chkAllLevel;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;

    void setupUi(QDialog *GetDirInfoDlg)
    {
        if (GetDirInfoDlg->objectName().isEmpty())
            GetDirInfoDlg->setObjectName(QString::fromUtf8("GetDirInfoDlg"));
        GetDirInfoDlg->resize(303, 132);
        GetDirInfoDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(GetDirInfoDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(GetDirInfoDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(40, 25));
        label->setMaximumSize(QSize(40, 25));

        horizontalLayout_3->addWidget(label);

        edtDir = new QLineEdit(GetDirInfoDlg);
        edtDir->setObjectName(QString::fromUtf8("edtDir"));
        edtDir->setMinimumSize(QSize(0, 25));
        edtDir->setMaximumSize(QSize(16777215, 25));
        edtDir->setReadOnly(true);

        horizontalLayout_3->addWidget(edtDir);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(GetDirInfoDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(40, 25));
        label_2->setMaximumSize(QSize(40, 25));

        horizontalLayout_2->addWidget(label_2);

        spnLevel = new QSpinBox(GetDirInfoDlg);
        spnLevel->setObjectName(QString::fromUtf8("spnLevel"));
        spnLevel->setMinimumSize(QSize(0, 25));
        spnLevel->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(spnLevel);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(GetDirInfoDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chkAllLevel = new QCheckBox(GetDirInfoDlg);
        chkAllLevel->setObjectName(QString::fromUtf8("chkAllLevel"));

        horizontalLayout->addWidget(chkAllLevel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(GetDirInfoDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(GetDirInfoDlg);

        QMetaObject::connectSlotsByName(GetDirInfoDlg);
    } // setupUi

    void retranslateUi(QDialog *GetDirInfoDlg)
    {
        GetDirInfoDlg->setWindowTitle(QApplication::translate("GetDirInfoDlg", "\345\244\232\345\261\202\347\233\256\345\275\225\344\277\241\346\201\257\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GetDirInfoDlg", "\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GetDirInfoDlg", "\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        chkAllLevel->setText(QApplication::translate("GetDirInfoDlg", "\350\216\267\345\217\226\346\211\200\346\234\211\345\261\202\346\254\241\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("GetDirInfoDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GetDirInfoDlg: public Ui_GetDirInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETDIRINFODLG_H
