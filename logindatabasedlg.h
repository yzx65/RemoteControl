#ifndef LOGINDATABASEDLG_H
#define LOGINDATABASEDLG_H

#include <QDialog>
#include "ui_logindatabasedlg.h"

#include <string>

class LoginDatabaseDlg : public QDialog
{
	Q_OBJECT

public:
	LoginDatabaseDlg(QWidget *parent, std::wstring& user, std::wstring& password);
	~LoginDatabaseDlg();

private slots:
	void OnLoginClicked();

private:
	Ui::LoginDatabaseDlg ui;
	std::wstring& m_user;
	std::wstring& m_pwd;
};

#endif // LOGINDATABASEDLG_H
