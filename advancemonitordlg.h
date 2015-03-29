#ifndef ADVANCEMONITORDLG_H
#define ADVANCEMONITORDLG_H

#include <QWidget>
#include "ui_advancemonitordlg.h"

class Target;

class AdvanceMonitorDlg : public QWidget
{
	Q_OBJECT

public:
	AdvanceMonitorDlg(QWidget *parent, Target* target);
	~AdvanceMonitorDlg();

public:
	void AddMonitorItem(const std::wstring& path);
	void RemoveMonitorItem(const std::wstring& path);
	void MonitorFileChanged(MSG* msg);

public:
	void UpdateUsbFile(MSG* msg);
	void UpdateUsbOp(MSG* msg);

private:
	void InitConnection();
	void InitWidgetAppearance();
	void InitAdvanceMonitor();

private slots:

	// 点击左侧树形列表
	void onTrAdvanceFileMonitorItemClicked(QTreeWidgetItem* item, int column);

	// 点击插拔记录列表中的某一项
	void onTbUsbPlugRecordItemClicked(QTableWidgetItem* item);

	// 双击目录列表中的某一项
	void onTbUsbDirItemDoubleClicked(QTableWidgetItem* item);

	// 清空记录
	void onBtnCleanMonitorRecordClicked();

	// 取消监控
	void onBtnCancelMonitorClicked();

private:

	// 更新 usb 目录
	void UpdateUsbDirInformation(std::wstring curDirTime, std::wstring filePath);

	// 上一级
	void LocateParentUsbDir();

	// 增加上一级的链接
	void AddUpLink();

private:
	Ui::AdvanceMonitorDlg ui;
	Target* m_tar;

	std::wstring     curUsbFilePathW;
};

#endif // ADVANCEMONITORDLG_H
