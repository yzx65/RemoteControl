/*!
	Description : 生成中转服务器
	Author		: Ruining Song
	Date		: 2013.12.7
	Remark		:
*/

#ifndef DAEMONDLG_H
#define DAEMONDLG_H

#include <QDialog>
#include "ui_daemondlg.h"

#include "target.h"

class DaemonDlg : public QDialog
{
	Q_OBJECT

public:

	// 构造函数
	DaemonDlg(QWidget *parent = 0);

	// 析构函数
	~DaemonDlg();


private slots:

	// 确定
	void OnOk();

private:

	// 生成 plg.cfg
	bool CreatePluginCfgFile(std::wstring plgCfgPath, PPLUGIN_CXT PlgCxtVect[]);

	// 生成中转服务器文件
	bool GenerateDaemonFileList(std::wstring daemonDir);

	// \_Plugin 目录 -> 中转 \update 目录
	bool CopyPlgToDaemon(std::wstring OrgPluginPath, std::wstring NewPluginPath, PPLUGIN_CXT PlgCxtVect[]);

	// 将配置信息写入中转服务器
	bool UpdateDaemonResource(std::wstring daemonFile);

private:
	Ui::DaemonDlg ui;
};

#endif // DAEMONDLG_H
