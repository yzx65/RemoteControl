#ifndef MULTIMEDIADLG_H
#define MULTIMEDIADLG_H

#include <QWidget>
#include "ui_multimediadlg.h"

class Target;

class MultimediaDlg : public QWidget
{
	Q_OBJECT

public:
	MultimediaDlg(QWidget *parent, Target* tar);
	~MultimediaDlg();

	void RefreshSkypeData();

private:
	void InitConnection();

private slots:

	// 点击 App 类型，如 Skype
	void onLstMonitorAppItemClicked(QListWidgetItem* item);

	// 点击日期
	void onLstSaveTimeItemClicked(QListWidgetItem* item);

	// 点击文件类型
	void onLstFileTypeItemClicked(QListWidgetItem* item);

	// 双击文件
	void onLstFileListItemDoubleClicked(QListWidgetItem* item);

private:
	Ui::MultimediaDlg ui;
	Target* m_tar;
};

#endif // MULTIMEDIADLG_H
