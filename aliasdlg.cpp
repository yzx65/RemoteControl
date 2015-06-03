#include "aliasdlg.h"
#include "Utility.h"

// ////////////////////////////////////////////////////////////////////////////////
// ���캯��
//
AliasDlg::AliasDlg(QWidget *parent, int targetId)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	ui.edtTargetId->setText(QString("%1").arg(targetId));

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));
	InitCustomText(this);
}

// ////////////////////////////////////////////////////////////////////////////////
// ��������
//
AliasDlg::~AliasDlg()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ����
//
QString AliasDlg::GetTargetAlias()
{
	return ui.edtTargetAlias->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ���ñ���
//
void AliasDlg::SetTargetAlias(QString alias)
{
	ui.edtTargetAlias->setText(alias);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ȷ��
//
void AliasDlg::OnOk()
{
	this->accept();
}