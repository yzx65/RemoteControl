/*!
	Description : 设置连接参数
	Author		: Ruining Song
	Date		: 2013.11.14
	Remark		:
*/

#ifndef CONNDLG_H
#define CONNDLG_H

#include <QtGui>
#include "ui_conndlg.h"
#include <string>
#include <list>

class ConnDlg : public QDialog
{
	Q_OBJECT

public:
	ConnDlg(QWidget *parent = 0);
	~ConnDlg();

public:

	QString GetIpAddress();

	QString GetCtrlPort();

	QString GetTargetPort();

	QString GetPass();

	bool IsAutoConn();

	void SetIpAddress(QString ipAddress);
	
	void SetCtrlPort(QString port);

	void SetTargetPort(QString port);

	void SetPass(QString pass);

	void SetAutoConn(bool autoConn);

	void GetDaemonHistory();

	void ApplyDaemonHistory();

private slots:

	// 连接
	void OnClickOk();


private:
	Ui::ConnDlg ui;
	std::list<std::wstring> m_daemonHistory;
};

#endif // CONNDLG_H
