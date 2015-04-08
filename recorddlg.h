#ifndef RECORDDLG_H
#define RECORDDLG_H

#include <QFrame>
#include "ui_recorddlg.h"

class Target;
class AmrPlayer;
class RecordDlg : public QFrame
{
	Q_OBJECT

public:
	RecordDlg(QWidget *parent, Target* target);
	~RecordDlg();

public:
	void GetNewRecordFile(MSG* msg);

private slots:

	void OnBtnSettingClicked();
	void OnBtnStopRecordClicked();

	void OnTrRecordListItemDoubleClicked(QTreeWidgetItem* item, int column);

private:

	void InitConnection();
	void InitFileList();
	void StartPlaySound(std::wstring file);
	void StopPlaySound();

private:
	Ui::RecordDlg ui;
	Target* m_tar;
	AmrPlayer* m_amr;
};

#endif // RECORDDLG_H
