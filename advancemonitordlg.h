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

	// �����������б�
	void onTrAdvanceFileMonitorItemClicked(QTreeWidgetItem* item, int column);

	// �����μ�¼�б��е�ĳһ��
	void onTbUsbPlugRecordItemClicked(QTableWidgetItem* item);

	// ˫��Ŀ¼�б��е�ĳһ��
	void onTbUsbDirItemDoubleClicked(QTableWidgetItem* item);

	// ��ռ�¼
	void onBtnCleanMonitorRecordClicked();

	// ȡ�����
	void onBtnCancelMonitorClicked();

private:

	// ���� usb Ŀ¼
	void UpdateUsbDirInformation(std::wstring curDirTime, std::wstring filePath);

	// ��һ��
	void LocateParentUsbDir();

	// ������һ��������
	void AddUpLink();

private:
	Ui::AdvanceMonitorDlg ui;
	Target* m_tar;

	std::wstring     curUsbFilePathW;
};

#endif // ADVANCEMONITORDLG_H
