/*!
	Description : 获取监控的文件类型
	Author		: Ruining Song
	Date		: 2013.12.10
	Remark		:
*/

#ifndef FILEMONTYPEDLG_H
#define FILEMONTYPEDLG_H

#include <QDialog>
#include "ui_filemontypedlg.h"

class FileMonTypeDlg : public QDialog
{
	Q_OBJECT

public:
	FileMonTypeDlg(QWidget *parent = 0);
	~FileMonTypeDlg();

	// 获取要监控的文件类型
	QString GetFileMonType();

private slots:

	// 确定
	void OnOk();


private:
	Ui::FileMonTypeDlg ui;
	QRegExpValidator* mask;
};

#endif // FILEMONTYPEDLG_H
