#ifndef MigrateDaemonDlg_H
#define MigrateDaemonDlg_H

#include <QDialog>
#include "ui_MigrateDaemonDlg.h"
#include <QRegExpValidator>

#include <string>

class MigrateDaemonDlg : public QDialog
{
	Q_OBJECT

public:
	MigrateDaemonDlg(QDialog *parent = 0);
	~MigrateDaemonDlg();

	std::wstring GetNewDaemonAddress()
	{
		return m_newDaemonAddress;
	}

public slots:
	// ����/ip ���л�
	void ServerTypeChanged_1(int index);
	void ServerTypeChanged_2(int index);

	// ��������
	void GetIP();

	// Ǩ��
	void StartMigration();

private:
	Ui::MigrateDaemonDlg ui;
	QRegExpValidator* m_ipMask;
	std::wstring m_newDaemonAddress;
};

#endif // MigrateDaemonDlg_H
