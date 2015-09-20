/********************************************************************************
** Form generated from reading UI file 'aliasdlg.ui'
**
** Created: Sun Sep 20 11:18:03 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALIASDLG_H
#define UI_ALIASDLG_H

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

class Ui_AliasDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtTargetId;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtTargetAlias;
    QFrame *frame;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;

    void setupUi(QDialog *AliasDlg)
    {
        if (AliasDlg->objectName().isEmpty())
            AliasDlg->setObjectName(QString::fromUtf8("AliasDlg"));
        AliasDlg->resize(300, 134);
        AliasDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(AliasDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AliasDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(54, 25));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        edtTargetId = new QLineEdit(AliasDlg);
        edtTargetId->setObjectName(QString::fromUtf8("edtTargetId"));
        edtTargetId->setMinimumSize(QSize(0, 25));
        edtTargetId->setReadOnly(true);

        horizontalLayout->addWidget(edtTargetId);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(AliasDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(54, 25));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edtTargetAlias = new QLineEdit(AliasDlg);
        edtTargetAlias->setObjectName(QString::fromUtf8("edtTargetAlias"));
        edtTargetAlias->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(edtTargetAlias);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(AliasDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(0, 0, 282, 3));
        frame_2->setFrameShape(QFrame::HLine);
        frame_2->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnOk = new QPushButton(AliasDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setMinimumSize(QSize(0, 30));

        horizontalLayout_3->addWidget(btnOk);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(AliasDlg);

        QMetaObject::connectSlotsByName(AliasDlg);
    } // setupUi

    void retranslateUi(QDialog *AliasDlg)
    {
        AliasDlg->setWindowTitle(QApplication::translate("AliasDlg", "\350\256\276\347\275\256\347\233\256\346\240\207\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AliasDlg", "\347\233\256\346\240\207ID", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AliasDlg", "\347\233\256\346\240\207\345\210\253\345\220\215", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("AliasDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AliasDlg: public Ui_AliasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALIASDLG_H
