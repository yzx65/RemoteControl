#include "getdirinfodlg.h"

// ////////////////////////////////////////////////////////////////////////////////
// ���캯��
//
GetDirInfoDlg::GetDirInfoDlg(QWidget *parent, std::wstring dir)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.edtDir->setText(QString::fromStdWString(dir));
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
}

// ////////////////////////////////////////////////////////////////////////////////
// ��������
//
GetDirInfoDlg::~GetDirInfoDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ����
//
int GetDirInfoDlg::GetLevel()
{
	if ( ui.chkAllLevel->isChecked() )
	{
		return 0;
	}

	return ui.spnLevel->value();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ȷ��
//
void GetDirInfoDlg::OnOk()
{
	accept();
}