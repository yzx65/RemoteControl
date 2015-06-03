#ifndef LOGDETAILDLG_H
#define LOGDETAILDLG_H

#include <QWidget>
#include "ui_logdetaildlg.h"

class WaitDlg;
class Target;

class LogDetailDlg : public QWidget
{
	Q_OBJECT

signals:

	void emitLogDetailInfo(unsigned int targetId, PageTableWidget* table);
	void emitLogDownloadInfo(unsigned int targetId, PageTableWidget* table);
	void emitLogUploadInfo(unsigned int targetId, PageTableWidget* table);
	void emitLogPluginInfo(unsigned int targetId, PageTableWidget* table);

public:
	LogDetailDlg(QWidget *parent, Target* tar);
	~LogDetailDlg();

	void AddDetail(const wchar_t* info);

private:

	void InitLogInfo();
	void InitConnection();

private slots:

	void onChkOnlineLogClicked();
	void onChkLogDetailClicked();
	void onChkLogDownloadClicked();
	void onChkLogUploadClicked();
	void onChkLogPluginClicked();

	void onQueryLogDetailFinished(unsigned int tarId);
	void onQueryLogDownloadFinished(unsigned int tarId);
	void onQueryLogUploadFinished(unsigned int tarId);
	void onQueryLogPluginFinished(unsigned int tarId);

	void RefreshOnlineLogInfo();

private:
	WaitDlg* m_waitLogDetailDlg;
	bool m_queryLogDetailFinished;

	WaitDlg* m_waitLogDownloadDlg;
	bool m_queryLogDownloadFinished;

	WaitDlg* m_waitLogUploadDlg;
	bool m_queryLogUploadFinished;

	WaitDlg* m_waitLogPluginDlg;
	bool m_queryLogPluginFinished;

	Ui::LogDetailDlg ui;

	Target* m_tar;
};

#endif // LOGDETAILDLG_H
