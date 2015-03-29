#ifndef CAPTUREDLG_H
#define CAPTUREDLG_H

#include <QDialog>
#include "ui_capturedlg.h"

class Target;
class QTreeWidgetItem;
class QTableWidgetItem;

class CaptureDlg : public QWidget
{
	Q_OBJECT

signals:
	void emitModify();

public:
	CaptureDlg(QWidget *parent, Target* m_tar);
	~CaptureDlg();

	void UpdateScreen(MSG* msg);
	void UpdateCapturePolicy();

private slots:
	void onBtnCaptureScreenClicked();
	void onTrScreenshotItemClicked(QTreeWidgetItem* item, int column);
	void onTbScreenshotItemClicked(QTableWidgetItem* item);
	void onTbScreenshotItemDoubleClicked(QTableWidgetItem* item);

private:
	void InitCustomAppearance();
	void InitConnection();
	void InitCaptureFileList();
	void GetCapturePolicy(bool& enable, std::wstring& procList, std::wstring& keyWord, int& interval);

private:
	Ui::CaptureDlg ui;
	Target* m_tar;
};

#endif // CAPTUREDLG_H
