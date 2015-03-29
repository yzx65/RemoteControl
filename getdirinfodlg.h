/*!
	Description : 多层目录信息获取
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

	// 构造函数
	GetDirInfoDlg(QWidget *parent, std::wstring dir);

	// 析构函数
	~GetDirInfoDlg();

	// 获取层数， 0 为所有层数
	int GetLevel();

private slots:

	// 确定
	void OnOk();

private:
	Ui::GetDirInfoDlg ui;
};

#endif // GETDIRINFODLG_H
