/*!
	Description : This class is used for containing the 'TargetDlg' class
	Author		: Ruining Song
	Date		: 2014/07/30
	Remark		: Try to implement some tabs like the new version QQ.
*/

#ifndef DLGCONTAINER_H
#define DLGCONTAINER_H

#include <QWidget>
#include <QStackedWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>
#include <QScrollArea>

#include <list>
#include <map>

/*!
\brief
	Used to replace the normal QRadioButton
*/
class TargetDlg;
class QPushButton;
class CustomLabel : public QWidget
{
	Q_OBJECT

signals:
	void clicked();
	void CloseLabel();

public:
	enum PaintState{NORMAL=0, HORVER, CHECKED};
	CustomLabel(QWidget* parent = 0);

	void SetTargetDlg(TargetDlg* tarDlg);
	void SetStackIndex(int index);
	void SetCurrentState(PaintState state);
	void SetText(QString text);
	void SetIcon(QString icon);
	void SetUuid(unsigned int uuid);

	TargetDlg* GetTargetDlg() { return m_targetDlg; }
	int GetStackIndex() { return m_stackIndex; }
	QString Text() { return m_text; }
	unsigned int GetUuid() { return m_uuid; }

	void click(){ emit clicked(); }

protected:
	void paintEvent(QPaintEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void enterEvent(QEvent* e);
	void leaveEvent(QEvent* e);

private:
	void InitCloseButton();

private:
	TargetDlg* m_targetDlg;
	int m_stackIndex;
	PaintState m_state;
	QString m_text;
	QString m_icon;
	QPixmap m_pic[3];
	QPixmap m_iconLoader;
	QBrush m_brush[3];
	unsigned int m_uuid;
	QPushButton* m_closeBtn;
};

class DlgContainer : public QWidget
{
	Q_OBJECT

signals:
	void emitBack();

public:
	DlgContainer(QWidget* parent = 0);
	~DlgContainer();

	void AddDialog(QWidget* dialog, unsigned int uuid, QString tabName, QString icon);
	void SetCurrentTab(unsigned int uuid);
	void ChangeLabelIcon(unsigned int uuid, QString icon);
	void ChangeLabelText(unsigned int uuid, QString text);

public slots:
	void LabelSelected();
	void LabelClosed();

private:
	void InitLayout();
	CustomLabel* AddCustomLabel(QString title, QString icon);

private:
	std::map<unsigned int, CustomLabel*> m_tabMap;
	QStackedWidget* m_contentStack;
	QScrollArea* m_scrollLeft;
	QWidget* m_navigate;
	QButtonGroup* m_tabGroup;
};

#endif // DLGCONTAINER_H