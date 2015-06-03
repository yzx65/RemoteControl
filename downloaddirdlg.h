/*!
	Description : ����Ŀ¼
	Author		: Ruining Song
	Date		: 2013.11.22
	Remark		:
*/

#ifndef DOWNLOADDIRDLG_H
#define DOWNLOADDIRDLG_H

#include <QDialog>
#include "ui_downloaddirdlg.h"

class DownloadDirDlg : public QDialog
{
	Q_OBJECT

public:

	// ���캯��
	DownloadDirDlg(QWidget *parent, QString dir);

	// ��������
	~DownloadDirDlg();

	// ��ȡ����
	int GetLevel();

private slots:

	// ȷ��
	void OnOk();

	// �����ѡ��
	void OnChkAllLevelClicked();

private:
	Ui::DownloadDirDlg ui;
};

#endif // DOWNLOADDIRDLG_H
