/********************************************************************************
** Form generated from reading UI file 'remotecmddlg.ui'
**
** Created: Tue Jun 30 23:21:58 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTECMDDLG_H
#define UI_REMOTECMDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RemoteCmdDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_29;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frameCmd;
    QVBoxLayout *verticalLayout_23;
    QLabel *label_16;
    QFrame *frame_14;
    QHBoxLayout *horizontalLayout_61;
    QLineEdit *edtWinExec;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *btnWinExec;
    QFrame *frame_6;
    QFrame *frame_15;
    QVBoxLayout *verticalLayout_31;
    QFrame *frame_8;
    QHBoxLayout *horizontalLayout_30;
    QLabel *lbConsoleCaption;
    QLabel *lbCurrentProcess;
    QFrame *frameExecute;
    QHBoxLayout *horizontalLayout_66;
    QLineEdit *edtConsoleInput;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *btnExecuteConsoleCmd;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_63;
    QTextEdit *edtConsoleOutput;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_62;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *btnClearConsoleOutput;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *btnExitProgress;
    QSpacerItem *horizontalSpacer_13;

    void setupUi(QWidget *RemoteCmdDlg)
    {
        if (RemoteCmdDlg->objectName().isEmpty())
            RemoteCmdDlg->setObjectName(QString::fromUtf8("RemoteCmdDlg"));
        RemoteCmdDlg->resize(1027, 584);
        verticalLayout = new QVBoxLayout(RemoteCmdDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_5 = new QFrame(RemoteCmdDlg);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setMinimumSize(QSize(500, 0));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame#frame_5\n"
"{\n"
"	border-style:solid;\n"
"	border-width:0px;\n"
"	border-bottom-width:1px;\n"
"	border-color:#cccccc;\n"
"	background-color:rgb(240,240,240);\n"
"}"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_29 = new QHBoxLayout(frame_5);
        horizontalLayout_29->setSpacing(0);
        horizontalLayout_29->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalLayout_29->setContentsMargins(0, 10, 0, 10);
        horizontalSpacer_3 = new QSpacerItem(227, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_3);

        frameCmd = new QFrame(frame_5);
        frameCmd->setObjectName(QString::fromUtf8("frameCmd"));
        frameCmd->setMinimumSize(QSize(600, 0));
        frameCmd->setStyleSheet(QString::fromUtf8("QFrame#frameCmd\n"
"{\n"
"	border-style:solid;\n"
"	border-color:#cccccc;\n"
"	border-width:1px;\n"
"	background-color:white;\n"
"}\n"
"\n"
"QFrame\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:none;\n"
"}"));
        verticalLayout_23 = new QVBoxLayout(frameCmd);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        label_16 = new QLabel(frameCmd);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        verticalLayout_23->addWidget(label_16);

        frame_14 = new QFrame(frameCmd);
        frame_14->setObjectName(QString::fromUtf8("frame_14"));
        frame_14->setMinimumSize(QSize(0, 0));
        frame_14->setMaximumSize(QSize(9999, 16777215));
        horizontalLayout_61 = new QHBoxLayout(frame_14);
        horizontalLayout_61->setSpacing(6);
        horizontalLayout_61->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_61->setObjectName(QString::fromUtf8("horizontalLayout_61"));
        edtWinExec = new QLineEdit(frame_14);
        edtWinExec->setObjectName(QString::fromUtf8("edtWinExec"));
        edtWinExec->setMinimumSize(QSize(0, 30));
        edtWinExec->setMaximumSize(QSize(16777215, 30));
        edtWinExec->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border:1px solid rgb(200,200,200);\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:rgb(240,240,240);\n"
"}"));

        horizontalLayout_61->addWidget(edtWinExec);

        horizontalSpacer_14 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_61->addItem(horizontalSpacer_14);

        btnWinExec = new QPushButton(frame_14);
        btnWinExec->setObjectName(QString::fromUtf8("btnWinExec"));
        btnWinExec->setMinimumSize(QSize(75, 30));
        btnWinExec->setMaximumSize(QSize(75, 30));
        btnWinExec->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_61->addWidget(btnWinExec);


        verticalLayout_23->addWidget(frame_14);

        frame_6 = new QFrame(frameCmd);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setMinimumSize(QSize(0, 1));
        frame_6->setMaximumSize(QSize(16777215, 1));
        frame_6->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color:#cccccc;\n"
"}"));
        frame_6->setFrameShape(QFrame::NoFrame);
        frame_6->setFrameShadow(QFrame::Raised);

        verticalLayout_23->addWidget(frame_6);

        frame_15 = new QFrame(frameCmd);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setMinimumSize(QSize(0, 0));
        frame_15->setMaximumSize(QSize(9999, 16777215));
        frame_15->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_31 = new QVBoxLayout(frame_15);
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setContentsMargins(11, 11, 11, 11);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        verticalLayout_31->setContentsMargins(-1, -1, -1, 0);
        frame_8 = new QFrame(frame_15);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        horizontalLayout_30 = new QHBoxLayout(frame_8);
        horizontalLayout_30->setSpacing(0);
        horizontalLayout_30->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        lbConsoleCaption = new QLabel(frame_8);
        lbConsoleCaption->setObjectName(QString::fromUtf8("lbConsoleCaption"));
        lbConsoleCaption->setMinimumSize(QSize(200, 25));
        lbConsoleCaption->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_30->addWidget(lbConsoleCaption);

        lbCurrentProcess = new QLabel(frame_8);
        lbCurrentProcess->setObjectName(QString::fromUtf8("lbCurrentProcess"));
        lbCurrentProcess->setMinimumSize(QSize(0, 25));
        lbCurrentProcess->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_30->addWidget(lbCurrentProcess);


        verticalLayout_31->addWidget(frame_8);

        frameExecute = new QFrame(frame_15);
        frameExecute->setObjectName(QString::fromUtf8("frameExecute"));
        horizontalLayout_66 = new QHBoxLayout(frameExecute);
        horizontalLayout_66->setSpacing(6);
        horizontalLayout_66->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_66->setObjectName(QString::fromUtf8("horizontalLayout_66"));
        edtConsoleInput = new QLineEdit(frameExecute);
        edtConsoleInput->setObjectName(QString::fromUtf8("edtConsoleInput"));
        edtConsoleInput->setMinimumSize(QSize(0, 30));
        edtConsoleInput->setMaximumSize(QSize(16777215, 30));
        edtConsoleInput->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border:1px solid rgb(200,200,200);\n"
"	font-family:\"Microsoft Yahei\";\n"
"	background-color:rgb(240,240,240);\n"
"}"));

        horizontalLayout_66->addWidget(edtConsoleInput);

        horizontalSpacer_16 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_66->addItem(horizontalSpacer_16);

        btnExecuteConsoleCmd = new QPushButton(frameExecute);
        btnExecuteConsoleCmd->setObjectName(QString::fromUtf8("btnExecuteConsoleCmd"));
        btnExecuteConsoleCmd->setEnabled(false);
        btnExecuteConsoleCmd->setMinimumSize(QSize(75, 30));
        btnExecuteConsoleCmd->setMaximumSize(QSize(75, 30));
        btnExecuteConsoleCmd->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_66->addWidget(btnExecuteConsoleCmd);


        verticalLayout_31->addWidget(frameExecute);

        verticalSpacer_3 = new QSpacerItem(40, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_31->addItem(verticalSpacer_3);

        horizontalLayout_63 = new QHBoxLayout();
        horizontalLayout_63->setSpacing(6);
        horizontalLayout_63->setObjectName(QString::fromUtf8("horizontalLayout_63"));
        edtConsoleOutput = new QTextEdit(frame_15);
        edtConsoleOutput->setObjectName(QString::fromUtf8("edtConsoleOutput"));
        edtConsoleOutput->setStyleSheet(QString::fromUtf8(" QTextEdit#edtConsoleOutput\n"
"{\n"
"	background-color:black;\n"
"	color:white;\n"
"	font: 11pt \"\345\256\213\344\275\223\";\n"
"}\n"
"QScrollBar:vertical {\n"
"     border-width:0px;\n"
"     background;transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     background-color: #555555;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background-color: #666666;\n"
"     min-heiht: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background-color:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background-color:transparent;\n"
" }"));
        edtConsoleOutput->setReadOnly(true);
        edtConsoleOutput->setAcceptRichText(false);

        horizontalLayout_63->addWidget(edtConsoleOutput);


        verticalLayout_31->addLayout(horizontalLayout_63);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_31->addItem(verticalSpacer_4);

        horizontalLayout_62 = new QHBoxLayout();
        horizontalLayout_62->setSpacing(6);
        horizontalLayout_62->setObjectName(QString::fromUtf8("horizontalLayout_62"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_62->addItem(horizontalSpacer_17);

        btnClearConsoleOutput = new QPushButton(frame_15);
        btnClearConsoleOutput->setObjectName(QString::fromUtf8("btnClearConsoleOutput"));
        btnClearConsoleOutput->setMinimumSize(QSize(75, 30));
        btnClearConsoleOutput->setMaximumSize(QSize(75, 30));
        btnClearConsoleOutput->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_62->addWidget(btnClearConsoleOutput);

        horizontalSpacer_15 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_62->addItem(horizontalSpacer_15);

        btnExitProgress = new QPushButton(frame_15);
        btnExitProgress->setObjectName(QString::fromUtf8("btnExitProgress"));
        btnExitProgress->setEnabled(false);
        btnExitProgress->setMinimumSize(QSize(75, 30));
        btnExitProgress->setMaximumSize(QSize(75, 30));
        btnExitProgress->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"	border:1px solid #bbbbbb;\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #eeeeee, stop:1 #cccccc);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:#d5d5d5;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #eeeeee);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"	background-color:transparent;\n"
"}"));

        horizontalLayout_62->addWidget(btnExitProgress);


        verticalLayout_31->addLayout(horizontalLayout_62);


        verticalLayout_23->addWidget(frame_15);


        horizontalLayout_29->addWidget(frameCmd);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_13);


        verticalLayout->addWidget(frame_5);


        retranslateUi(RemoteCmdDlg);

        QMetaObject::connectSlotsByName(RemoteCmdDlg);
    } // setupUi

    void retranslateUi(QWidget *RemoteCmdDlg)
    {
        RemoteCmdDlg->setWindowTitle(QApplication::translate("RemoteCmdDlg", "RemoteCmdDlg", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("RemoteCmdDlg", "  \345\220\214\346\255\245\346\211\247\350\241\214 (\347\233\264\346\216\245\345\234\250\347\275\221\347\273\234\350\277\233\347\250\213\344\270\255\346\211\247\350\241\214)", 0, QApplication::UnicodeUTF8));
        edtWinExec->setPlaceholderText(QApplication::translate("RemoteCmdDlg", "\350\276\223\345\205\245\345\221\275\344\273\244 . . .", 0, QApplication::UnicodeUTF8));
        btnWinExec->setText(QApplication::translate("RemoteCmdDlg", "\350\277\234\347\250\213\346\211\247\350\241\214", 0, QApplication::UnicodeUTF8));
        lbConsoleCaption->setText(QApplication::translate("RemoteCmdDlg", "\346\216\247\345\210\266\345\217\260\350\276\223\345\205\245\344\270\216\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        lbCurrentProcess->setText(QString());
        edtConsoleInput->setText(QString());
        edtConsoleInput->setPlaceholderText(QApplication::translate("RemoteCmdDlg", "\350\276\223\345\205\245\346\216\247\345\210\266\345\217\260\345\221\275\344\273\244. . . ", 0, QApplication::UnicodeUTF8));
        btnExecuteConsoleCmd->setText(QApplication::translate("RemoteCmdDlg", "\346\211\247\350\241\214", 0, QApplication::UnicodeUTF8));
        edtConsoleOutput->setHtml(QApplication::translate("RemoteCmdDlg", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:13pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnClearConsoleOutput->setText(QApplication::translate("RemoteCmdDlg", "\346\270\205\347\251\272\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        btnExitProgress->setText(QApplication::translate("RemoteCmdDlg", "\345\274\272\345\210\266\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RemoteCmdDlg: public Ui_RemoteCmdDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTECMDDLG_H
