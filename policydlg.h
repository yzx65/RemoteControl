/*!
	Description : 插件策略配置
	Author		: Ruining Song
	Date		: 2013.12.23
	Remark		:
*/

#ifndef POLICYDLG_H
#define POLICYDLG_H

#include <QtGui>
#include <Windows.h>
#include "ui_policydlg.h"

#include "include/T5UserAction.h"
#include "include/T5UsbConfig.h"
#include "include/T5Screen.h"

class Target;

class PolicyDlg : public QDialog
{
	Q_OBJECT

public:
	PolicyDlg(QWidget *parent, Target* tar, int pluginNumber);
	~PolicyDlg();

	// 获取用户行为配置信息
	bool GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData);

	// 获取 usb 配置信息
	bool GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData);

	// 获取截屏配置信息
	bool GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData);

private slots:

	// 确定更新
	void OnOk();

	// 点击 '智能截取目标窗口'
	void OnChkSmartCaptureClicked();

private:

	// 读取原来的策略
	void GetOldPolicy();

private:
	Ui::PolicyDlg ui;
	Target* tarBlock;
};

#endif // POLICYDLG_H
