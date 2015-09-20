#ifndef GENERATETARDLG_H
#define GENERATETARDLG_H

#include <QDialog>
#include "ui_generatetardlg.h"

class GenerateTarDlg : public QDialog
{
	Q_OBJECT

public:
	GenerateTarDlg(QWidget *parent = 0);
	~GenerateTarDlg();

public slots:

	void OnGenerate();

private:
	Ui::GenerateTarDlg ui;
};

#endif // GENERATETARDLG_H
