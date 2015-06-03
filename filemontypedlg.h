/*!
	Description : ��ȡ��ص��ļ�����
	Author		: Ruining Song
	Date		: 2013.12.10
	Remark		:
*/

#ifndef FILEMONTYPEDLG_H
#define FILEMONTYPEDLG_H

#include <QDialog>
#include "ui_filemontypedlg.h"

class FileMonTypeDlg : public QDialog
{
	Q_OBJECT

public:
	FileMonTypeDlg(QWidget *parent = 0);
	~FileMonTypeDlg();

	// ��ȡҪ��ص��ļ�����
	QString GetFileMonType();

private slots:

	// ȷ��
	void OnOk();


private:
	Ui::FileMonTypeDlg ui;
	QRegExpValidator* mask;
};

#endif // FILEMONTYPEDLG_H
