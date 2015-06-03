/*!
	Description : ���Ŀ¼��Ϣ��ȡ
	Author		: Ruining Song
	Date		: 2013.11.19
	Remark		:
*/

#ifndef GETDIRINFODLG_H
#define GETDIRINFODLG_H

#include <QDialog>
#include "ui_getdirinfodlg.h"

class GetDirInfoDlg : public QDialog
{
	Q_OBJECT

public:

	// ���캯��
	GetDirInfoDlg(QWidget *parent, std::wstring dir);

	// ��������
	~GetDirInfoDlg();

	// ��ȡ������ 0 Ϊ���в���
	int GetLevel();

private slots:

	// ȷ��
	void OnOk();

private:
	Ui::GetDirInfoDlg ui;
};

#endif // GETDIRINFODLG_H
