/********************************************************************************
** Form generated from reading UI file 'configdlg.ui'
**
** Created: Thu Apr 2 16:13:21 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDLG_H
#define UI_CONFIGDLG_H

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
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConfigDlg
{
public:
    QVBoxLayout *verticalLayout_5;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *btnAccess;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *btnSQLServer;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frame1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *chkAutoConnect;
    QSpacerItem *horizontalSpacer_6;
    QFrame *frmAutoGet;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *chkAutoGet;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *chkAutoGetAll;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_12;
    QSpinBox *spnAutoGetLevel;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_11;
    QFrame *frame2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QFrame *frame_6;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_14;
    QRadioButton *btnReadDirInfoFromDb;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_16;
    QRadioButton *btnReadDirInfoFromTarget;
    QSpacerItem *horizontalSpacer_17;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_7;
    QFrame *frame_9;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_22;
    QRadioButton *btnDownloadAuto;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_24;
    QRadioButton *btnAskBeforeDownload;
    QSpacerItem *horizontalSpacer_25;
    QHBoxLayout *horizontalLayout_20;
    QSpacerItem *horizontalSpacer_26;
    QRadioButton *btnDisableDownload;
    QSpacerItem *horizontalSpacer_27;
    QFrame *frame3;
    QFrame *frame_7;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *btnOK;

    void setupUi(QDialog *ConfigDlg)
    {
        if (ConfigDlg->objectName().isEmpty())
            ConfigDlg->setObjectName(QString::fromUtf8("ConfigDlg"));
        ConfigDlg->resize(459, 602);
        ConfigDlg->setMinimumSize(QSize(459, 0));
        ConfigDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}\n"
"\n"
"QWidget#ConfigDlg\n"
"{\n"
"	background-color:white;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(ConfigDlg);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame = new QFrame(ConfigDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::HLine);
        frame_2->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnAccess = new QRadioButton(frame);
        btnAccess->setObjectName(QString::fromUtf8("btnAccess"));

        horizontalLayout_2->addWidget(btnAccess);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        btnSQLServer = new QRadioButton(frame);
        btnSQLServer->setObjectName(QString::fromUtf8("btnSQLServer"));

        horizontalLayout_3->addWidget(btnSQLServer);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_5->addWidget(frame);

        frame1 = new QFrame(ConfigDlg);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        verticalLayout_2 = new QVBoxLayout(frame1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(frame1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        frame_3 = new QFrame(frame1);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::HLine);
        frame_3->setFrameShadow(QFrame::Raised);

        horizontalLayout_4->addWidget(frame_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        chkAutoConnect = new QCheckBox(frame1);
        chkAutoConnect->setObjectName(QString::fromUtf8("chkAutoConnect"));

        horizontalLayout_5->addWidget(chkAutoConnect);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_5->addWidget(frame1);

        frmAutoGet = new QFrame(ConfigDlg);
        frmAutoGet->setObjectName(QString::fromUtf8("frmAutoGet"));
        verticalLayout_3 = new QVBoxLayout(frmAutoGet);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(frmAutoGet);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        frame_4 = new QFrame(frmAutoGet);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setFrameShape(QFrame::HLine);
        frame_4->setFrameShadow(QFrame::Raised);

        horizontalLayout_6->addWidget(frame_4);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        chkAutoGet = new QCheckBox(frmAutoGet);
        chkAutoGet->setObjectName(QString::fromUtf8("chkAutoGet"));

        horizontalLayout_7->addWidget(chkAutoGet);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_9);

        chkAutoGetAll = new QCheckBox(frmAutoGet);
        chkAutoGetAll->setObjectName(QString::fromUtf8("chkAutoGetAll"));

        horizontalLayout_8->addWidget(chkAutoGetAll);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_12);

        spnAutoGetLevel = new QSpinBox(frmAutoGet);
        spnAutoGetLevel->setObjectName(QString::fromUtf8("spnAutoGetLevel"));

        horizontalLayout_9->addWidget(spnAutoGetLevel);

        label_4 = new QLabel(frmAutoGet);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_9->addWidget(label_4);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_11);


        verticalLayout_3->addLayout(horizontalLayout_9);


        verticalLayout_5->addWidget(frmAutoGet);

        frame2 = new QFrame(ConfigDlg);
        frame2->setObjectName(QString::fromUtf8("frame2"));
        verticalLayout_4 = new QVBoxLayout(frame2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, -1, -1, -1);
        label_5 = new QLabel(frame2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_11->addWidget(label_5);

        frame_6 = new QFrame(frame2);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        sizePolicy.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy);
        frame_6->setFrameShape(QFrame::HLine);
        frame_6->setFrameShadow(QFrame::Raised);

        horizontalLayout_11->addWidget(frame_6);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_14);

        btnReadDirInfoFromDb = new QRadioButton(frame2);
        btnReadDirInfoFromDb->setObjectName(QString::fromUtf8("btnReadDirInfoFromDb"));

        horizontalLayout_12->addWidget(btnReadDirInfoFromDb);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_15);


        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_16);

        btnReadDirInfoFromTarget = new QRadioButton(frame2);
        btnReadDirInfoFromTarget->setObjectName(QString::fromUtf8("btnReadDirInfoFromTarget"));

        horizontalLayout_13->addWidget(btnReadDirInfoFromTarget);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_17);


        verticalLayout_4->addLayout(horizontalLayout_13);


        verticalLayout_5->addWidget(frame2);

        frame_5 = new QFrame(ConfigDlg);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        verticalLayout_7 = new QVBoxLayout(frame_5);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, -1, -1, -1);
        label_7 = new QLabel(frame_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_17->addWidget(label_7);

        frame_9 = new QFrame(frame_5);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        sizePolicy.setHeightForWidth(frame_9->sizePolicy().hasHeightForWidth());
        frame_9->setSizePolicy(sizePolicy);
        frame_9->setFrameShape(QFrame::HLine);
        frame_9->setFrameShadow(QFrame::Raised);

        horizontalLayout_17->addWidget(frame_9);


        verticalLayout_7->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_22);

        btnDownloadAuto = new QRadioButton(frame_5);
        btnDownloadAuto->setObjectName(QString::fromUtf8("btnDownloadAuto"));

        horizontalLayout_18->addWidget(btnDownloadAuto);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_23);


        verticalLayout_7->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_24);

        btnAskBeforeDownload = new QRadioButton(frame_5);
        btnAskBeforeDownload->setObjectName(QString::fromUtf8("btnAskBeforeDownload"));

        horizontalLayout_19->addWidget(btnAskBeforeDownload);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_25);


        verticalLayout_7->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_26);

        btnDisableDownload = new QRadioButton(frame_5);
        btnDisableDownload->setObjectName(QString::fromUtf8("btnDisableDownload"));

        horizontalLayout_20->addWidget(btnDisableDownload);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_27);


        verticalLayout_7->addLayout(horizontalLayout_20);


        verticalLayout_5->addWidget(frame_5);

        frame3 = new QFrame(ConfigDlg);
        frame3->setObjectName(QString::fromUtf8("frame3"));
        frame3->setFrameShape(QFrame::HLine);
        frame3->setFrameShadow(QFrame::Raised);
        frame_7 = new QFrame(frame3);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(30, -10, 461, 16));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(frame3);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        btnOK = new QPushButton(ConfigDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setMinimumSize(QSize(0, 30));

        horizontalLayout_10->addWidget(btnOK);


        verticalLayout_5->addLayout(horizontalLayout_10);


        retranslateUi(ConfigDlg);

        QMetaObject::connectSlotsByName(ConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *ConfigDlg)
    {
        ConfigDlg->setWindowTitle(QApplication::translate("ConfigDlg", "\345\205\250\345\261\200\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConfigDlg", "\350\277\236\346\216\245\347\232\204\346\225\260\346\215\256\345\272\223\347\261\273\345\236\213 ( \344\270\213\346\254\241\347\250\213\345\272\217\345\220\257\345\212\250\346\227\266\347\224\237\346\225\210 )", 0, QApplication::UnicodeUTF8));
        btnAccess->setText(QApplication::translate("ConfigDlg", "Microsoft Access", 0, QApplication::UnicodeUTF8));
        btnSQLServer->setText(QApplication::translate("ConfigDlg", "Microsoft SQL Server", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConfigDlg", "\350\207\252\345\212\250\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        chkAutoConnect->setText(QApplication::translate("ConfigDlg", "\347\250\213\345\272\217\345\220\257\345\212\250\345\220\216\350\207\252\345\212\250\350\277\236\346\216\245\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ConfigDlg", "\350\207\252\345\212\250\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        chkAutoGet->setText(QApplication::translate("ConfigDlg", "\347\233\256\346\240\207\344\270\212\347\272\277\345\220\216\350\207\252\345\212\250\350\216\267\345\217\226\347\233\256\345\275\225\347\273\223\346\236\204", 0, QApplication::UnicodeUTF8));
        chkAutoGetAll->setText(QApplication::translate("ConfigDlg", "\350\207\252\345\212\250\350\216\267\345\217\226\347\233\256\346\240\207\346\211\200\346\234\211\345\261\202\346\254\241\347\232\204\347\233\256\345\275\225\347\273\223\346\236\204", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ConfigDlg", "\350\216\267\345\217\226\345\261\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ConfigDlg", "\347\233\256\345\275\225\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        btnReadDirInfoFromDb->setText(QApplication::translate("ConfigDlg", "\344\274\230\345\205\210\344\273\216\346\225\260\346\215\256\345\272\223\344\270\255\350\257\273\345\217\226\347\233\256\345\275\225\344\277\241\346\201\257 ( \350\212\202\347\234\201\346\265\201\351\207\217 )", 0, QApplication::UnicodeUTF8));
        btnReadDirInfoFromTarget->setText(QApplication::translate("ConfigDlg", "\344\274\230\345\205\210\344\273\216\347\233\256\346\240\207\347\253\257\351\207\215\346\226\260\350\216\267\345\217\226\347\233\256\345\275\225\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("ConfigDlg", "\346\226\207\344\273\266\345\217\212\346\226\207\344\273\266\345\244\271\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        btnDownloadAuto->setText(QApplication::translate("ConfigDlg", "\350\207\252\345\212\250\344\270\213\350\275\275\345\217\221\347\224\237\345\217\230\345\214\226\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnAskBeforeDownload->setText(QApplication::translate("ConfigDlg", "\344\270\213\350\275\275\344\271\213\345\211\215\346\217\220\347\244\272\347\224\250\346\210\267\346\230\257\345\220\246\344\270\213\350\275\275", 0, QApplication::UnicodeUTF8));
        btnDisableDownload->setText(QApplication::translate("ConfigDlg", "\347\246\201\346\255\242\350\207\252\345\212\250\344\270\213\350\275\275\345\217\221\347\224\237\345\217\230\345\214\226\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("ConfigDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigDlg: public Ui_ConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDLG_H
