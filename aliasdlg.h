/*!
	Description : ����Ŀ�����
	Author		: Ruining Song
	Date		: 2013.11.18
	Remark		:
*/

#ifndef ALIASDLG_H
#define ALIASDLG_H

#include <QDialog>
#include "ui_aliasdlg.h"

class AliasDlg : public QDialog
{
	Q_OBJECT

public:

	// ���캯��
	AliasDlg(QWidget *parent, int targetId);

	// ��������
	~AliasDlg();

	// ��ȡĿ�����
	QString GetTargetAlias();

	// ����Ŀ�����
	void SetTargetAlias(QString alias);

private slots:

	// ȷ��
	void OnOk();

private:
	Ui::AliasDlg ui;
};

#endif // ALIASDLG_H
