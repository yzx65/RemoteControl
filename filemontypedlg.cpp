#include "filemontypedlg.h"

#include <QMessageBox>

// ////////////////////////////////////////////////////////////////////////////////
// @public ���캯��
//
FileMonTypeDlg::FileMonTypeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

	QRegExp exp("(\\*\\.([^;]+);)+");
	mask = new QRegExpValidator(exp);
	ui.edtExt->setValidator(mask);

	connect(ui.btnOk, SIGNAL(clicked()), this, SLOT(OnOk()));	
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��������
//
FileMonTypeDlg::~FileMonTypeDlg()
{
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��ȡ��ص��ļ�����
//
QString FileMonTypeDlg::GetFileMonType()
{
	return ui.edtExt->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ȷ��
//
void FileMonTypeDlg::OnOk()
{
	if ( "" == ui.edtExt->text() )
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("������Ҫ�������ļ�����!"));
		return;
	}

	int pos = 0;

	if ( QValidator::Acceptable != mask->validate(ui.edtExt->text(), pos) )
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("������ļ���������"));
		return;
	}

	accept();
}