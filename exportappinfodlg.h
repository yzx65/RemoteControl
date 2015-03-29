#ifndef EXPORTAPPINFODLG_H
#define EXPORTAPPINFODLG_H

#include <QDialog>
#include "ui_exportappinfodlg.h"

class ExportAppInfoDlg : public QDialog
{
	Q_OBJECT

signals:

	void emitStart(QString path, int targetId);
	void emitCancel();

public slots:

	void GetRecordCount(int count);
	void CurrentRecordAdd();
	void ExportFinished();
	void ExportCanceled();

	void OnBtnCancelClicked();

public:
	ExportAppInfoDlg(QString path, int targetId);
	~ExportAppInfoDlg();

private:
	Ui::ExportAppInfoDlg ui;
	int m_count;
	QString m_path;
};

#endif // EXPORTAPPINFODLG_H
