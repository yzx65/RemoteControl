/*!
	Description : 设置目标别名
	Author		: Ruining Song
	Date		: 2013.11.18
	Remark		:
*/

#ifndef ALIASDLG_H
#define ALIASDLG_H

#include <QDialog>
#include "ui_aliasdlg.h"

class AliasDlg : public QDialog
{
	Q_OBJECT

public:

	// 构造函数
	AliasDlg(QWidget *parent, int targetId);

	// 析构函数
	~AliasDlg();

	// 获取目标别名
	QString GetTargetAlias();

	// 设置目标别名
	void SetTargetAlias(QString alias);

private slots:

	// 确定
	void OnOk();

private:
	Ui::AliasDlg ui;
};

#endif // ALIASDLG_H
