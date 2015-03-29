#ifndef FILECTRLDLG_H
#define FILECTRLDLG_H

#include <QWidget>
#include "ui_filectrldlg.h"

#include <Windows.h>

#include "target.h"

class Target;
class FileCtrlDlg : public QWidget
{
	Q_OBJECT

public:
	FileCtrlDlg(QWidget *parent, Target* tar);
	~FileCtrlDlg();

public:
	void SetItemMonitorFlag(bool flag);

private:
	void InitConnection();
	void InitWidgetAppearance();
	void InitFileControl();

	void AddCustomShortcut();

public:

	// 更新磁盘列表
	void UpdateLirInfo();

	// 搜索失败
	void SearchFailed(MSG* msg);

	// 搜索结束
	void SearchFinished(MSG* msg);

	// 获取每个搜索结果
	void SearchStep(MSG* msg);

	// 下载文件结束
	void DownloadFileFinished(FileTask* fileTask);

	// 更新目录信息
	bool UpdateDirInformation(std::wstring wPath);

	// 更新监控状态
	void UpdateItemMonitorStatus(const std::wstring& path, QTableWidgetItem* item);

private slots:

	// 文件列表弹出右键菜单
	void onTbFileListContextMenuActived(QPoint point);

	// 左侧导航弹出右键菜单
	void onTrFileCtrlContextMenuActived(QPoint point);

	// 单击文件列表中的项
	void onTbFileListItemClick(QTableWidgetItem* item);

	// 双击文件列表中的项
	void onTbFileListItemDoubleClicked(QTableWidgetItem* item);

	// 单击左侧文件控制列表项
	void onTrFileCtrlItemClick(QTreeWidgetItem* item, int column);

	// 地址栏索引改变
	void onAddressIndexChanged(int index);

	// 点击 '转到' 按钮
	void onBtnGotoClicked();

	// 添加到收藏夹
	void onBtnFavoriteClicked();

	// '上传'
	void onBtnUploadClicked();

	// '下载'
	void onBtnDownloadClicked();

	// '目录下载'
	void onBtnDownloadDirClicked();

	// '目录列表获取'
	void onBtnGetDirListClicked();

	// '向上'
	void onBtnUpClicked();

	// '刷新'
	void onBtnRefreshClicked();

	// '删除'
	void onBtnDeleteClicked();

	// '执行'
	void onBtnRunClicked();

	// 智能分析
	void onBtnAnalyzeClicked();

	// '添加监视'
	void onBtnMonitorClicked();

	// '搜索'
	void onBtnSearchClicked();

	// '开始搜索'
	void onBtnStartSearchClicked();

	// 下载搜索到的文件
	void onBtnStartDownloadClicked();

	// 返回文件列表
	void onBtnReturnFileListClicked();

private:

	// 更新右边磁盘列表
	void ShowDiskLogicDriver();

	// 磁盘列表模式
	void SwitchToDiskList();

	// 文件列表模式
	void SwitchToFileList();

	// 获取目录内容
	void StartGetDirInfomation(std::wstring wPath, BOOL bOnline);

	// 地址栏中插入历史记录
	void InsertCmboxPath(std::wstring wPath);

	// 获取目录信息 ( 在线状态 )
	void StartGetOnlineDirInfo(std::wstring wPath);

	// 获取目录信息 ( 离线状态 )
	void StartGetASyncDirInfo(std::wstring wPath);

	// 初始化系统快捷方式
	void InitShortcut();

	// 添加快捷方式 : 描述 - 路径 - 图标 - 父节点
	void AddShortcut(std::wstring description, std::wstring path, QIcon& icon, QTreeWidgetItem* parent = NULL);

	// 在线搜索目录
	void OnlineSearch(std::wstring path, std::wstring prefix, ULONG onlineSearchId);

	// 上传文件
	void UploadFile(std::wstring dirPath);

	// 下载文件
	void DownloadFile(std::wstring path);

	// 清空搜索结果
	void ClearOnlineSearchBlock();

	// 查看文件是否被监视了
	bool IsMonitored(QTableWidgetItem* item);

	// 添加收藏
	void AddFavorite(std::wstring path);

private:
	Ui::FileCtrlDlg ui;
	Target* m_tar;

	std::wstring     curFilePathW;

	// Shortcut map
	std::map<std::wstring, std::wstring> m_customShortMap;

	bool bShowDiskList;

	bool            bSearching;
	DWORD           dwOnlineSearchId;
};

#endif // FILECTRLDLG_H
