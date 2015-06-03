#ifndef UPLOADTHIRDPLUGINDLG_H
#define UPLOADTHIRDPLUGINDLG_H

#include <QDialog>
#include "ui_uploadthirdplugindlg.h"

class Target;

class UploadThirdPluginDlg : public QDialog
{
	Q_OBJECT

public:
	UploadThirdPluginDlg(Target* tar, QWidget *parent = 0, int ver = 0, int productId = 0, QString pluginName = "");
	~UploadThirdPluginDlg();

	void SetCfgPath(const std::wstring& cfgPath);

private slots:
	void onBtnGetPathClicked();
	void onBtnOKclicked();
	void onBtnAdvanceClicked();

private:
	bool ValidateValue();
	bool CompressPlugin(std::wstring& packageName);
	bool DoUpload(const std::wstring& plugin);

private:
	Ui::UploadThirdPluginDlg ui;
	int m_oldVersion;
	int m_productId;
	std::wstring m_targetDir;
	std::wstring m_cfgPath;
	bool m_isDll;
	Target* m_tar;
};

#endif // UPLOADTHIRDPLUGINDLG_H
