#ifndef REMOTECMDDLG_H
#define REMOTECMDDLG_H

#include <QWidget>
#include "ui_remotecmddlg.h"

class Target;
class RemoteCmdDlg : public QWidget
{
	Q_OBJECT

public:
	RemoteCmdDlg(QWidget *parent, Target* tar);
	~RemoteCmdDlg();

private:
	void InitConnection();

public:
	void RemoteCmdFinished();
	void RemoteCmdOutput();
	void RemoteCmdExec();

private slots:

	// ��� 'Զ��ִ��' ��ť
	void onBtnWinExecClicked();

	// ��� 'ִ��' ��ť
	void onBtnExecuteConsoleCmdClicked();

	// ��� '������' ��ť
	void onBtnClearConsoleOutputClicked();

	// ��� 'ǿ���˳�' ��ť
	void onBtnExitProcessClicked();

private:
	Ui::RemoteCmdDlg ui;
	Target* m_tar;
};

#endif // REMOTECMDDLG_H
