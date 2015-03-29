#include "logindatabasedlg.h"
#include <Windows.h>

LoginDatabaseDlg::LoginDatabaseDlg(QWidget *parent, std::wstring& user, std::wstring& password)
	: QDialog(parent)
	, m_user(user)
	, m_pwd(password)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.btnLogin, SIGNAL(clicked()), this, SLOT(OnLoginClicked()));
}

LoginDatabaseDlg::~LoginDatabaseDlg()
{

}

void LoginDatabaseDlg::OnLoginClicked()
{
	if ( ui.edtUserName->text() == "" )
	{
		MessageBox(this->winId(), L"用户名不能为空!", L"错误", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if ( ui.edtPassword->text() == "" )
	{
		MessageBox(this->winId(), L"密码不能为空!", L"错误", MB_OK | MB_ICONINFORMATION);
		return;
	}

	m_user = ui.edtUserName->text().toStdWString();
	m_pwd = ui.edtPassword->text().toStdWString();

	accept();
}
