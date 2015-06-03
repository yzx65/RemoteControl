#include "getdirinfodlg.h"

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
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
// 析构函数
//
GetDirInfoDlg::~GetDirInfoDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 获取层数
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
// @public 确定
//
void GetDirInfoDlg::OnOk()
{
	accept();
}