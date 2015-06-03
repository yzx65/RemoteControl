/*!
	Description : �����������
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

	// ��ȡ�û���Ϊ������Ϣ
	bool GetUserActionCfgInfo(PUSER_ACT_CFG& lpUserActCfgData);

	// ��ȡ usb ������Ϣ
	bool GetUsbCfgInfo(PUSB_THIEF_CONFIG& lpUsbThiefCfgData);

	// ��ȡ����������Ϣ
	bool GetScreenshotCfgInfo(PCAPTURE_CONFIG& lpCaptureCfgData);

private slots:

	// ȷ������
	void OnOk();

	// ��� '���ܽ�ȡĿ�괰��'
	void OnChkSmartCaptureClicked();

private:

	// ��ȡԭ���Ĳ���
	void GetOldPolicy();

private:
	Ui::PolicyDlg ui;
	Target* tarBlock;
};

#endif // POLICYDLG_H
