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

	// 点击 '远程执行' 按钮
	void onBtnWinExecClicked();

	// 点击 '执行' 按钮
	void onBtnExecuteConsoleCmdClicked();

	// 点击 '清空输出' 按钮
	void onBtnClearConsoleOutputClicked();

	// 点击 '强制退出' 按钮
	void onBtnExitProcessClicked();

private:
	Ui::RemoteCmdDlg ui;
	Target* m_tar;
};

#endif // REMOTECMDDLG_H
