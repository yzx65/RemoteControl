#ifndef FLOWCONTROLDLG_H
#define FLOWCONTROLDLG_H

#include <QDialog>
#include "ui_flowcontroldlg.h"

class Target;
class FlowControlDlg : public QDialog
{
	Q_OBJECT

public:
	FlowControlDlg(Target* tar);
	~FlowControlDlg();

private slots:
	void RefreshPolicy();

private:
	Ui::FlowControlDlg ui;
	Target* m_curTarget;
};

#endif // FLOWCONTROLDLG_H
