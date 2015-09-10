/********************************************************************************
** Form generated from reading UI file 'querydaemonaddressdlg.ui'
**
** Created: Thu Sep 10 21:18:35 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYDAEMONADDRESSDLG_H
#define UI_QUERYDAEMONADDRESSDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QueryDaemonAddressDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *edtTargetId;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnQuery;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmbIP;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtIP;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *edtPort;
    QGroupBox *grpExtra;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *cmbIP2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *edtIP2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *edtPort2;

    void setupUi(QDialog *QueryDaemonAddressDlg)
    {
        if (QueryDaemonAddressDlg->objectName().isEmpty())
            QueryDaemonAddressDlg->setObjectName(QString::fromUtf8("QueryDaemonAddressDlg"));
        QueryDaemonAddressDlg->resize(400, 256);
        QueryDaemonAddressDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(QueryDaemonAddressDlg);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        label = new QLabel(QueryDaemonAddressDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 25));

        horizontalLayout_5->addWidget(label);

        edtTargetId = new QLineEdit(QueryDaemonAddressDlg);
        edtTargetId->setObjectName(QString::fromUtf8("edtTargetId"));
        edtTargetId->setMinimumSize(QSize(0, 25));
        edtTargetId->setReadOnly(true);

        horizontalLayout_5->addWidget(edtTargetId);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        btnQuery = new QPushButton(QueryDaemonAddressDlg);
        btnQuery->setObjectName(QString::fromUtf8("btnQuery"));
        btnQuery->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(btnQuery);


        verticalLayout_3->addLayout(horizontalLayout_5);

        groupBox = new QGroupBox(QueryDaemonAddressDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cmbIP = new QComboBox(groupBox);
        cmbIP->setObjectName(QString::fromUtf8("cmbIP"));
        cmbIP->setMinimumSize(QSize(69, 25));

        horizontalLayout->addWidget(cmbIP);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        edtIP = new QLineEdit(groupBox);
        edtIP->setObjectName(QString::fromUtf8("edtIP"));
        edtIP->setMinimumSize(QSize(0, 25));
        edtIP->setReadOnly(true);

        horizontalLayout->addWidget(edtIP);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(69, 25));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        edtPort = new QLineEdit(groupBox);
        edtPort->setObjectName(QString::fromUtf8("edtPort"));
        edtPort->setMinimumSize(QSize(0, 25));
        edtPort->setReadOnly(true);

        horizontalLayout_2->addWidget(edtPort);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox);

        grpExtra = new QGroupBox(QueryDaemonAddressDlg);
        grpExtra->setObjectName(QString::fromUtf8("grpExtra"));
        grpExtra->setCheckable(false);
        grpExtra->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(grpExtra);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cmbIP2 = new QComboBox(grpExtra);
        cmbIP2->setObjectName(QString::fromUtf8("cmbIP2"));
        cmbIP2->setMinimumSize(QSize(69, 25));

        horizontalLayout_3->addWidget(cmbIP2);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        edtIP2 = new QLineEdit(grpExtra);
        edtIP2->setObjectName(QString::fromUtf8("edtIP2"));
        edtIP2->setMinimumSize(QSize(0, 25));
        edtIP2->setReadOnly(true);

        horizontalLayout_3->addWidget(edtIP2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(grpExtra);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(69, 25));

        horizontalLayout_4->addWidget(label_3);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        edtPort2 = new QLineEdit(grpExtra);
        edtPort2->setObjectName(QString::fromUtf8("edtPort2"));
        edtPort2->setMinimumSize(QSize(0, 25));
        edtPort2->setReadOnly(true);

        horizontalLayout_4->addWidget(edtPort2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(grpExtra);


        retranslateUi(QueryDaemonAddressDlg);

        QMetaObject::connectSlotsByName(QueryDaemonAddressDlg);
    } // setupUi

    void retranslateUi(QDialog *QueryDaemonAddressDlg)
    {
        QueryDaemonAddressDlg->setWindowTitle(QApplication::translate("QueryDaemonAddressDlg", "\347\233\256\346\240\207\344\270\255\350\275\254\345\233\236\350\277\236\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QueryDaemonAddressDlg", "\347\233\256\346\240\207 ID", 0, QApplication::UnicodeUTF8));
        btnQuery->setText(QApplication::translate("QueryDaemonAddressDlg", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("QueryDaemonAddressDlg", "\344\270\273\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIP->clear();
        cmbIP->insertItems(0, QStringList()
         << QApplication::translate("QueryDaemonAddressDlg", "IP \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QueryDaemonAddressDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("QueryDaemonAddressDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        grpExtra->setTitle(QApplication::translate("QueryDaemonAddressDlg", "\345\244\207\347\224\250\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIP2->clear();
        cmbIP2->insertItems(0, QStringList()
         << QApplication::translate("QueryDaemonAddressDlg", "IP \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("QueryDaemonAddressDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("QueryDaemonAddressDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QueryDaemonAddressDlg: public Ui_QueryDaemonAddressDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYDAEMONADDRESSDLG_H
