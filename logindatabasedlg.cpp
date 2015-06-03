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
		MessageBox(this->winId(), L"�û�������Ϊ��!", L"����", MB_OK | MB_ICONINFORMATION);
		return;
	}

	if ( ui.edtPassword->text() == "" )
	{
		MessageBox(this->winId(), L"���벻��Ϊ��!", L"����", MB_OK | MB_ICONINFORMATION);
		return;
	}

	m_user = ui.edtUserName->text().toStdWString();
	m_pwd = ui.edtPassword->text().toStdWString();

	accept();
}
