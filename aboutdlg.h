#ifndef ABOUTDLG_H
#define ABOUTDLG_H

#include <QDialog>
#include "ui_aboutdlg.h"
#include "maindlg.h"

class AboutDlg : public QDialog
{
	Q_OBJECT

public:
	AboutDlg(QWidget *parent);
	~AboutDlg();

private:
	void UpdatePluginInfo(QTreeWidget* tree, PPLUGIN_CXT pluginInfo[]);
	void InitCustomGui();

private:
	Ui::AboutDlg ui;
};

#endif // ABOUTDLG_H
