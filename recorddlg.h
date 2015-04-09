#ifndef RECORDDLG_H
#define RECORDDLG_H

#include <QFrame>
#include <QTimer>
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
	void TestSoundFinished();

private:

	void InitConnection();
	void InitFileList();
	void StartPlaySound();
	void StopPlaySound();

private:
	Ui::RecordDlg ui;
	Target* m_tar;
	AmrPlayer* m_amr;
	std::wstring m_curFile;
	int m_curIndex;
	QTimer m_timer;
};

#endif // RECORDDLG_H
