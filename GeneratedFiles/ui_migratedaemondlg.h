/********************************************************************************
** Form generated from reading UI file 'migratedaemondlg.ui'
**
** Created: Sun Jun 7 19:02:08 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIGRATEDAEMONDLG_H
#define UI_MIGRATEDAEMONDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MigrateDaemonDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *cmbIP;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edtIP;
    QPushButton *btnAnalyze;
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
    QPushButton *btnAnalyze2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *edtPort2;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOK;

    void setupUi(QWidget *MigrateDaemonDlg)
    {
        if (MigrateDaemonDlg->objectName().isEmpty())
            MigrateDaemonDlg->setObjectName(QString::fromUtf8("MigrateDaemonDlg"));
        MigrateDaemonDlg->resize(393, 272);
        MigrateDaemonDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(MigrateDaemonDlg);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(MigrateDaemonDlg);
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

        horizontalLayout->addWidget(edtIP);

        btnAnalyze = new QPushButton(groupBox);
        btnAnalyze->setObjectName(QString::fromUtf8("btnAnalyze"));
        btnAnalyze->setEnabled(false);
        btnAnalyze->setMaximumSize(QSize(40, 16777215));

        horizontalLayout->addWidget(btnAnalyze);


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

        horizontalLayout_2->addWidget(edtPort);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(groupBox);

        grpExtra = new QGroupBox(MigrateDaemonDlg);
        grpExtra->setObjectName(QString::fromUtf8("grpExtra"));
        grpExtra->setCheckable(true);
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

        horizontalLayout_3->addWidget(edtIP2);

        btnAnalyze2 = new QPushButton(grpExtra);
        btnAnalyze2->setObjectName(QString::fromUtf8("btnAnalyze2"));
        btnAnalyze2->setMaximumSize(QSize(40, 16777215));

        horizontalLayout_3->addWidget(btnAnalyze2);


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

        horizontalLayout_4->addWidget(edtPort2);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(grpExtra);

        frame = new QFrame(MigrateDaemonDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        btnOK = new QPushButton(MigrateDaemonDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 30));

        horizontalLayout_5->addWidget(btnOK);


        verticalLayout_3->addLayout(horizontalLayout_5);


        retranslateUi(MigrateDaemonDlg);

        QMetaObject::connectSlotsByName(MigrateDaemonDlg);
    } // setupUi

    void retranslateUi(QWidget *MigrateDaemonDlg)
    {
        MigrateDaemonDlg->setWindowTitle(QApplication::translate("MigrateDaemonDlg", "\350\277\201\347\247\273\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MigrateDaemonDlg", "\344\270\273\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIP->clear();
        cmbIP->insertItems(0, QStringList()
         << QApplication::translate("MigrateDaemonDlg", "IP \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MigrateDaemonDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        btnAnalyze->setText(QApplication::translate("MigrateDaemonDlg", "\350\247\243\346\236\220", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MigrateDaemonDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        grpExtra->setTitle(QApplication::translate("MigrateDaemonDlg", "\345\244\207\347\224\250\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIP2->clear();
        cmbIP2->insertItems(0, QStringList()
         << QApplication::translate("MigrateDaemonDlg", "IP \345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MigrateDaemonDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        btnAnalyze2->setText(QApplication::translate("MigrateDaemonDlg", "\350\247\243\346\236\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MigrateDaemonDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("MigrateDaemonDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MigrateDaemonDlg: public Ui_MigrateDaemonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIGRATEDAEMONDLG_H
