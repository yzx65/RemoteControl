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

	// ���´����б�
	void UpdateLirInfo();

	// ����ʧ��
	void SearchFailed(MSG* msg);

	// ��������
	void SearchFinished(MSG* msg);

	// ��ȡÿ���������
	void SearchStep(MSG* msg);

	// �����ļ�����
	void DownloadFileFinished(FileTask* fileTask);

	// ����Ŀ¼��Ϣ
	bool UpdateDirInformation(std::wstring wPath);

	// ���¼��״̬
	void UpdateItemMonitorStatus(const std::wstring& path, QTableWidgetItem* item);

private slots:

	// �ļ��б����Ҽ��˵�
	void onTbFileListContextMenuActived(QPoint point);

	// ��ർ�������Ҽ��˵�
	void onTrFileCtrlContextMenuActived(QPoint point);

	// �����ļ��б��е���
	void onTbFileListItemClick(QTableWidgetItem* item);

	// ˫���ļ��б��е���
	void onTbFileListItemDoubleClicked(QTableWidgetItem* item);

	// ��������ļ������б���
	void onTrFileCtrlItemClick(QTreeWidgetItem* item, int column);

	// ��ַ�������ı�
	void onAddressIndexChanged(int index);

	// ��� 'ת��' ��ť
	void onBtnGotoClicked();

	// ��ӵ��ղؼ�
	void onBtnFavoriteClicked();

	// '�ϴ�'
	void onBtnUploadClicked();

	// '����'
	void onBtnDownloadClicked();

	// 'Ŀ¼����'
	void onBtnDownloadDirClicked();

	// 'Ŀ¼�б��ȡ'
	void onBtnGetDirListClicked();

	// '����'
	void onBtnUpClicked();

	// 'ˢ��'
	void onBtnRefreshClicked();

	// 'ɾ��'
	void onBtnDeleteClicked();

	// 'ִ��'
	void onBtnRunClicked();

	// ���ܷ���
	void onBtnAnalyzeClicked();

	// '��Ӽ���'
	void onBtnMonitorClicked();

	// '����'
	void onBtnSearchClicked();

	// '��ʼ����'
	void onBtnStartSearchClicked();

	// �������������ļ�
	void onBtnStartDownloadClicked();

	// �����ļ��б�
	void onBtnReturnFileListClicked();

private:

	// �����ұߴ����б�
	void ShowDiskLogicDriver();

	// �����б�ģʽ
	void SwitchToDiskList();

	// �ļ��б�ģʽ
	void SwitchToFileList();

	// ��ȡĿ¼����
	void StartGetDirInfomation(std::wstring wPath, BOOL bOnline);

	// ��ַ���в�����ʷ��¼
	void InsertCmboxPath(std::wstring wPath);

	// ��ȡĿ¼��Ϣ ( ����״̬ )
	void StartGetOnlineDirInfo(std::wstring wPath);

	// ��ȡĿ¼��Ϣ ( ����״̬ )
	void StartGetASyncDirInfo(std::wstring wPath);

	// ��ʼ��ϵͳ��ݷ�ʽ
	void InitShortcut();

	// ��ӿ�ݷ�ʽ : ���� - ·�� - ͼ�� - ���ڵ�
	void AddShortcut(std::wstring description, std::wstring path, QIcon& icon, QTreeWidgetItem* parent = NULL);

	// ��������Ŀ¼
	void OnlineSearch(std::wstring path, std::wstring prefix, ULONG onlineSearchId);

	// �ϴ��ļ�
	void UploadFile(std::wstring dirPath);

	// �����ļ�
	void DownloadFile(std::wstring path);

	// ����������
	void ClearOnlineSearchBlock();

	// �鿴�ļ��Ƿ񱻼�����
	bool IsMonitored(QTableWidgetItem* item);

	// ����ղ�
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
