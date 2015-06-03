#ifndef AUTOGETDLG_H
#define AUTOGETDLG_H

#include <QDialog>
#include "ui_autogetdlg.h"

class Target;
class AutoGetDlg : public QDialog
{
	Q_OBJECT

public:
	AutoGetDlg(Target* tar);
	~AutoGetDlg();

private slots:
	void OnChkAutoGetClicked();
	void OnOK();

private:
	Ui::AutoGetDlg ui;
	Target* m_tar;
};

#endif // AUTOGETDLG_H
