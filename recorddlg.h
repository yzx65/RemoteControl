#ifndef RECORDDLG_H
#define RECORDDLG_H

#include <QFrame>
#include "ui_recorddlg.h"

class Target;

class RecordDlg : public QFrame
{
	Q_OBJECT

public:
	RecordDlg(QWidget *parent, Target* target);
	~RecordDlg();

private:
	Ui::RecordDlg ui;
	Target* m_tar;
};

#endif // RECORDDLG_H
