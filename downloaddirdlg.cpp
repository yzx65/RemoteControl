#include "downloaddirdlg.h"
#include "Utility.h"

// ////////////////////////////////////////////////////////////////////////////////
// ���캯��
//
DownloadDirDlg::DownloadDirDlg(QWidget *parent, QString dir)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.edtDir->setText(dir);
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::MSWindowsFixedSizeDialogHint);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	connect(ui.chkAllLevel, SIGNAL(clicked()), this, SLOT(OnChkAllLevelClicked()));

	InitCustomText(this);
}

// ////////////////////////////////////////////////////////////////////////////////
// ��������
//
DownloadDirDlg::~DownloadDirDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ����
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
// @private slot ȷ��
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
