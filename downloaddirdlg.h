/*!
	Description : 下载目录
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

	// 构造函数
	DownloadDirDlg(QWidget *parent, QString dir);

	// 析构函数
	~DownloadDirDlg();

	// 获取层数
	int GetLevel();

private slots:

	// 确定
	void OnOk();

	// 点击复选框
	void OnChkAllLevelClicked();

private:
	Ui::DownloadDirDlg ui;
};

#endif // DOWNLOADDIRDLG_H
