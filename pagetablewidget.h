/*!
	Description : ����ҳ�ı��ؼ�
	Author		: Ruining Song
	Date		: 2013.12.25
	Remark		:

			>> 2014.1.4 
				
				�����ؼ�����ۣ�������ҳ����ת��һ�� bug
			
			>> ���Խ��: ���� 100000 �м�¼��ʱ 1 s

			>> ʹ�÷���:

			//
			// ���� 500000 �м�¼
			//

			table->SetColumnCount(5);
			table->SetRowCountPerPage(500);

			QStringList title;
			for (int i = 1; i < 6; i++)
			{
				title << QString::fromLocal8Bit("�� %1 ��").arg(i);
			}
			table->SetColumnLabels(title);

			for (int i = 0; i < 500000; i++)
			{
				table->AppendRow();

				for (int j = 0; j < 5; j++)
				{
					QTableWidgetItem* item = new QTableWidgetItem;
					item->setText(tr("%1, %2").arg(i).arg(j));
					item->setTextAlignment(Qt::AlignCenter);
					table->SetAppendRowItem(j, item);
				}
			}

			table->RefreshPage();
*/

#ifndef PAGETABLEWIDGET_H
#define PAGETABLEWIDGET_H

#include <vector>
#include <string>

#include <QWidget>
#include <QTableWidget>

class QLabel;
class QPushButton;
class QTableWidgetItem;
class QStringList;
class QLineEdit;
class QFrame;
class QHeaderView;

class PageTableWidget : public QWidget
{
	Q_OBJECT

public:
	PageTableWidget(QWidget *parent);
	~PageTableWidget();

signals:
	void itemClicked(QTableWidgetItem* item);

public:

	//
	// tableWidget �Ľӿ�
	//

	QTableWidgetItem* item(int row, int column) { return _table->item(row, column); }
	QHeaderView* horizontalHeader(){ return _table->horizontalHeader(); }
	void SetTableStyle(QStyle* style)
	{
		_table->setStyle(style);
	}

	//
	// �½ӿ�
	//

	// ��������
	void SetColumnCount(unsigned int count);

	// �����б���
	void SetColumnLabels(const QStringList& labels);

	// ����ÿҳ��ʾ����
	void SetRowCountPerPage(unsigned int count);

	// ����һ��
	void AppendRow();

	// ���ò����е� item
	void SetAppendRowItem(int column, QTableWidgetItem* item);

	// ˢ��ҳ��
	void RefreshPage();

	// ���
	void Clear();

	// ����ָ����
	void SetColumnHidden(int column, bool hide)
	{
		_table->setColumnHidden(column, hide);
	}

private slots:
	
	// ��һҳ
	void FirstPage();

	// ��һҳ
	void PrevPage();

	// ��һҳ
	void NextPage();

	// ���һҳ
	void LastPage();

	// ת��
	void JumpTo();

private:

	// ��ʼ������
	void InitLayout();

	// ��ʼ�� signals
	void InitSignals();

	// ��ʼ�� slots
	void InitConnection();

	// ��ʼ�����
	void InitAppearance();

private:

	// ����ҳ��
	inline void CalculatePage()
	{
		_pageCount = _totalRowCount%_rowCountPerPage ? 
			_totalRowCount/_rowCountPerPage+1 : _totalRowCount/_rowCountPerPage;
	}

private:

	//
	// �ӿؼ�
	//
	QTableWidget* _table;
	QFrame* _bottomFrame;
	QLabel*	_lbCurrentPage;
	QPushButton* _btnPrev;
	QPushButton* _btnNext;
	QPushButton* _btnStart;
	QPushButton* _btnEnd;

	QLineEdit* _edtJumpTo;		// ת��
	QPushButton* _btnJumpTo;

	//
	// �������
	// 
	std::vector<std::vector<QTableWidgetItem*> > _dataSet;
	int _totalRowCount;		// ������
	int _rowCountPerPage;	// ÿҳ����
	int _pageCount;			// ��ҳ��
	int _currentPage;		// ��ǰҳ

};

#endif // PAGETABLEWIDGET_H
