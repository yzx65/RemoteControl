#ifndef THIRDPLUGINDLG_H
#define THIRDPLUGINDLG_H

#include <QWidget>
#include "ui_thirdplugindlg.h"

class Target;

class ThirdPluginDlg : public QWidget
{
	Q_OBJECT

public:
	ThirdPluginDlg(Target* tar);
	~ThirdPluginDlg();

public:
	void GetNewPluginFile(MSG* msg);

private slots:
	void OnBtnAddThirdPluginClicked();
	void OnBtnUpdateThirdPluginClicked();
	void OnBtnDeleteThirdPluginClicked();
	void OnTbThirdPluginListItemClicked(QTableWidgetItem* item);
	void OnTrThirdPluginFileListItemDoubleClicked(QTreeWidgetItem* item, int column);
	void OnTrThirdPluginFileListItemClicked(QTreeWidgetItem* item, int column);

private:
	void AddFileToPluginFileList(const wchar_t* fileName);

private:
	void InitPluginList();

private:
	Ui::ThirdPluginDlg ui;
	Target* m_tar;
};

#endif // THIRDPLUGINDLG_H
