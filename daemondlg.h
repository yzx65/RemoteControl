/*!
	Description : ������ת������
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

	// ���캯��
	DaemonDlg(QWidget *parent = 0);

	// ��������
	~DaemonDlg();


private slots:

	// ȷ��
	void OnOk();

private:

	// ���� plg.cfg
	bool CreatePluginCfgFile(std::wstring plgCfgPath, PPLUGIN_CXT PlgCxtVect[]);

	// ������ת�������ļ�
	bool GenerateDaemonFileList(std::wstring daemonDir);

	// \_Plugin Ŀ¼ -> ��ת \update Ŀ¼
	bool CopyPlgToDaemon(std::wstring OrgPluginPath, std::wstring NewPluginPath, PPLUGIN_CXT PlgCxtVect[]);

	// ��������Ϣд����ת������
	bool UpdateDaemonResource(std::wstring daemonFile);

private:
	Ui::DaemonDlg ui;
};

#endif // DAEMONDLG_H
