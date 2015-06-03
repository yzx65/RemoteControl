#include "favoritenamedlg.h"
#include <QtGui>

FavoriteNameDlg::FavoriteNameDlg(const std::wstring& path)
	: QDialog(0)
{
	ui.setupUi(this);
	
	ui.edtName->setText(QString::fromStdWString(path));
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnOK()));
}

FavoriteNameDlg::~FavoriteNameDlg()
{

}

void FavoriteNameDlg::OnOK()
{
	if ( "" == ui.edtName->text() )
	{
		QMessageBox::information(
			this, 
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("���Ʋ���Ϊ��!"));
		return;
	}

	accept();
}

std::wstring FavoriteNameDlg::GetFavoriteName()
{
	return ui.edtName->text().toStdWString();
}
