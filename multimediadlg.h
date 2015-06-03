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

	// ��� App ���ͣ��� Skype
	void onLstMonitorAppItemClicked(QListWidgetItem* item);

	// �������
	void onLstSaveTimeItemClicked(QListWidgetItem* item);

	// ����ļ�����
	void onLstFileTypeItemClicked(QListWidgetItem* item);

	// ˫���ļ�
	void onLstFileListItemDoubleClicked(QListWidgetItem* item);

private:
	Ui::MultimediaDlg ui;
	Target* m_tar;
};

#endif // MULTIMEDIADLG_H
