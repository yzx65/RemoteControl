#include "filemontypedlg.h"

#include <QMessageBox>

// ////////////////////////////////////////////////////////////////////////////////
// @public 构造函数
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
// @public 析构函数
//
FileMonTypeDlg::~FileMonTypeDlg()
{
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 获取监控的文件类型
//
QString FileMonTypeDlg::GetFileMonType()
{
	return ui.edtExt->text();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 确定
//
void FileMonTypeDlg::OnOk()
{
	if ( "" == ui.edtExt->text() )
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("请输入要搜索的文件类型!"));
		return;
	}

	int pos = 0;

	if ( QValidator::Acceptable != mask->validate(ui.edtExt->text(), pos) )
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("输入的文件类型有误"));
		return;
	}

	accept();
}