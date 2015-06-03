#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <QDialog>
#include "ui_configdlg.h"
#include <string>

class ConfigDlg : public QDialog
{
	Q_OBJECT

public:
	ConfigDlg(QWidget *parent = 0);
	~ConfigDlg();

private slots:
	void OnOK();

private:
	void InitDataBaseType();
	void InitAutoConnect();
	void InitAutoGet();
	void InitDirInfoPolicy();
	void InitAdvanceMonitorPolicy();

	void ApplyDataBaseType();
	void ApplyAutoConnect();
	void ApplyAutoGet();
	void ApplyDirInfoPolicy();
	void ApplyAdvanceMonitorPolicy();

private:
	Ui::ConfigDlg ui;
	std::wstring m_setting;
};

#endif // CONFIGDLG_H
