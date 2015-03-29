#include "flowcontroldlg.h"
#include "target.h"
#include "maindlg.h"
#include "DatabaseManager.h"

#define PLUGIN_ENABLE_1 0x00000001
#define PLUGIN_ENABLE_2 0x00000002
#define PLUGIN_ENABLE_3 0x00000004
#define PLUGIN_ENABLE_4 0x00000008

FlowControlDlg::FlowControlDlg(Target* tar)
	: QDialog(0)
	, m_curTarget(tar)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(RefreshPolicy()));

	DWORD preValue = DM->QueryTargetPluginStatus(m_curTarget->dwTargetID);

	ui.chkPlg1->setChecked(PLUGIN_ENABLE_1 & preValue);
	ui.chkPlg2->setChecked(PLUGIN_ENABLE_2 & preValue);
	ui.chkPlg4->setChecked(PLUGIN_ENABLE_4 & preValue);
}

FlowControlDlg::~FlowControlDlg()
{

}

void FlowControlDlg::RefreshPolicy()
{
	DWORD pluginEnableMask = 0;

	if ( ui.chkPlg1->isChecked() )
		pluginEnableMask |= PLUGIN_ENABLE_1;

	if ( ui.chkPlg2->isChecked() )
		pluginEnableMask |= PLUGIN_ENABLE_2;

	if ( ui.chkPlg4->isChecked() )
		pluginEnableMask |= PLUGIN_ENABLE_4;

	DWORD preValue = DM->QueryTargetPluginStatus(m_curTarget->dwTargetID);

	if ( preValue != pluginEnableMask )
	{
		FrmMain->ctrConn->Send_SDA(m_curTarget->dwTargetID, pluginEnableMask);
		DM->UpdatetargetPluginStatus(m_curTarget->dwTargetID, pluginEnableMask);
		SetTarStatusInfoExW(STATUS_INFO, m_curTarget, L"[目标%s(ID:%u)] 成功修改流量控制策略",
			m_curTarget->widTargetName.c_str(),
			m_curTarget->dwTargetID);
	}

	accept();
}
