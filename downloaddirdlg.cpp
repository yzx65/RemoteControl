#include "downloaddirdlg.h"

// ////////////////////////////////////////////////////////////////////////////////
// 构造函数
//
DownloadDirDlg::DownloadDirDlg(QWidget *parent, QString dir)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.edtDir->setText(dir);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	connect(ui.chkAllLevel, SIGNAL(clicked()), this, SLOT(OnChkAllLevelClicked()));
}

// ////////////////////////////////////////////////////////////////////////////////
// 析构函数
//
DownloadDirDlg::~DownloadDirDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 获取层数
//
int DownloadDirDlg::GetLevel()
{
	if ( ui.chkAllLevel->isChecked() )
	{
		return 0;
	}

	return ui.spnLevel->value();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 确定
//
void DownloadDirDlg::OnOk()
{
	accept();
}

void DownloadDirDlg::OnChkAllLevelClicked()
{
	if ( ui.chkAllLevel->isChecked() )
		ui.frmLevel->hide();
	else
		ui.frmLevel->show();

	this->adjustSize();
}
