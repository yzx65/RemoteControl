#include "remotecmddlg.h"
#include "target.h"
#include "TargetConnection.h"

#include "maindlg.h"

#include <QtGui>

RemoteCmdDlg::RemoteCmdDlg(QWidget *parent, Target* tar)
	: QWidget(parent)
	, m_tar(tar)
{
	ui.setupUi(this);
	InitConnection();
}

RemoteCmdDlg::~RemoteCmdDlg()
{

}

void RemoteCmdDlg::InitConnection()
{
	connect(ui.btnWinExec, SIGNAL(clicked()), this, SLOT(onBtnWinExecClicked()));
	connect(ui.btnClearConsoleOutput, SIGNAL(clicked()), this, SLOT(onBtnClearConsoleOutputClicked()));
	connect(ui.btnExitProgress, SIGNAL(clicked()), this, SLOT(onBtnExitProcessClicked()));
	connect(ui.btnExecuteConsoleCmd, SIGNAL(clicked()), this, SLOT(onBtnExecuteConsoleCmdClicked()));
}

// 点击 '远程执行' 按钮
void RemoteCmdDlg::onBtnWinExecClicked()
{
	if ( !FrmMain->ctrOnlineFlag )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("离线状态下不能下达文件执行指令!"));
		return;
	}

	if ( FrmMain->ctrConn == NULL )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("异常错误，网络连接断开!"));  
		return;
	}

	if (m_tar->tarStatus == TAROFFLINE)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("离线状态下不能下达文件执行指令!"));
		return;
	}

	if ( ui.edtWinExec->text().trimmed().isEmpty() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请输入需要执行的命令及参数!"));
		return;
	}

	if ( ui.btnExecuteConsoleCmd->isEnabled() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("一次只能同步运行一个程序!"));
		return;
	}

	std::wstring path = ui.edtWinExec->text().toStdWString();
	FrmMain->ctrConn->Send_RUN(this->m_tar->dwTargetID, path, TRUE);
}

// 点击 '执行' 按钮
void RemoteCmdDlg::onBtnExecuteConsoleCmdClicked()
{
	std::string input = ui.edtConsoleInput->text().toStdString() + "\r\n";
	FrmMain->ctrConn->Send_CITA(this->m_tar->dwTargetID, input);
	ui.edtConsoleInput->clear();
}

// 点击 '清空输出' 按钮
void RemoteCmdDlg::onBtnClearConsoleOutputClicked()
{
	ui.edtConsoleOutput->clear();
}

// 点击 '强制退出' 按钮
void RemoteCmdDlg::onBtnExitProcessClicked()
{
	FrmMain->ctrConn->Send_CFI(this->m_tar->dwTargetID);
}

void RemoteCmdDlg::RemoteCmdFinished()
{
	ui.lbConsoleCaption->setText(QString::fromLocal8Bit("控制台程序输入与输出 (执行结束)"));
	ui.lbCurrentProcess->setText("");
	ui.btnExecuteConsoleCmd->setEnabled(false);
	ui.btnExitProgress->setEnabled(false);
}

void RemoteCmdDlg::RemoteCmdOutput()
{
	QString text = ui.edtConsoleOutput->toPlainText();

	text += QString::fromStdWString(this->m_tar->widRedirectOutput);
	ui.edtConsoleOutput->setPlainText(text);

	QScrollBar* bar = ui.edtConsoleOutput->verticalScrollBar();
	bar->setSliderPosition(bar->maximum());
	ui.edtConsoleInput->setFocus();
}

void RemoteCmdDlg::RemoteCmdExec()
{
	ui.lbCurrentProcess->setText(
		QString::fromLocal8Bit("当前进程 : ") + QString::fromStdWString(this->m_tar->widRedirectProc));
	ui.lbConsoleCaption->setText(QString::fromLocal8Bit("控制台程序输入与输出 (正在运行...)"));
	ui.btnExecuteConsoleCmd->setEnabled(true);
	ui.btnExitProgress->setEnabled(true);
}
