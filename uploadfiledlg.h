/*!
	Description : 上传文件
	Author		: Ruining Song
	Date		: 2013.11.22
	Remark		:
*/

#ifndef UPLOADFILEDLG_H
#define UPLOADFILEDLG_H

#include <QDialog>
#include "ui_uploadfiledlg.h"

class UploadFileDlg : public QDialog
{
	Q_OBJECT

public:

	// 构造函数
	UploadFileDlg(QWidget *parent, QString remotePath);

	// 析构函数
	~UploadFileDlg();

	// 获取本地文件路径
	QString GetLocalPath();

	// 获取文件大小
	unsigned int GetFileSize();

private slots:

	// 确定
	void OnOk();

	// 浏览
	void OnBtnBrowseClicked();

private:
	Ui::UploadFileDlg ui;
};

#endif // UPLOADFILEDLG_H
