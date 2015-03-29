#ifndef QUERYDAEMONADDRESSDLG_H
#define QUERYDAEMONADDRESSDLG_H

#include <QDialog>
#include "ui_querydaemonaddressdlg.h"

class Target;

class QueryDaemonAddressDlg : public QDialog
{
	Q_OBJECT

public:
	QueryDaemonAddressDlg(QWidget *parent, Target* tar);
	~QueryDaemonAddressDlg();

	void OnQueryDaemonAddressFinished(MSG* msg);
	void OnQueryDaemonAddressFinished2(MSG* msg);

public slots:
	void OnBtnQueryClicked();

private:
	Ui::QueryDaemonAddressDlg ui;
	Target* m_tar;
};

#endif // QUERYDAEMONADDRESSDLG_H
