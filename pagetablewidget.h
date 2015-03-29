/*!
	Description : 带翻页的表格控件
	Author		: Ruining Song
	Date		: 2013.12.25
	Remark		:

			>> 2014.1.4 
				
				调整控件的外观，修正了页面跳转的一个 bug
			
			>> 测试结果: 插入 100000 行记录用时 1 s

			>> 使用范例:

			//
			// 插入 500000 行记录
			//

			table->SetColumnCount(5);
			table->SetRowCountPerPage(500);

			QStringList title;
			for (int i = 1; i < 6; i++)
			{
				title << QString::fromLocal8Bit("第 %1 列").arg(i);
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
	// tableWidget 的接口
	//

	QTableWidgetItem* item(int row, int column) { return _table->item(row, column); }
	QHeaderView* horizontalHeader(){ return _table->horizontalHeader(); }
	void SetTableStyle(QStyle* style)
	{
		_table->setStyle(style);
	}

	//
	// 新接口
	//

	// 设置列数
	void SetColumnCount(unsigned int count);

	// 设置列标题
	void SetColumnLabels(const QStringList& labels);

	// 设置每页显示行数
	void SetRowCountPerPage(unsigned int count);

	// 插入一行
	void AppendRow();

	// 设置插入行的 item
	void SetAppendRowItem(int column, QTableWidgetItem* item);

	// 刷新页面
	void RefreshPage();

	// 清空
	void Clear();

	// 隐藏指定列
	void SetColumnHidden(int column, bool hide)
	{
		_table->setColumnHidden(column, hide);
	}

private slots:
	
	// 第一页
	void FirstPage();

	// 上一页
	void PrevPage();

	// 下一页
	void NextPage();

	// 最后一页
	void LastPage();

	// 转到
	void JumpTo();

private:

	// 初始化布局
	void InitLayout();

	// 初始化 signals
	void InitSignals();

	// 初始化 slots
	void InitConnection();

	// 初始化外观
	void InitAppearance();

private:

	// 计算页数
	inline void CalculatePage()
	{
		_pageCount = _totalRowCount%_rowCountPerPage ? 
			_totalRowCount/_rowCountPerPage+1 : _totalRowCount/_rowCountPerPage;
	}

private:

	//
	// 子控件
	//
	QTableWidget* _table;
	QFrame* _bottomFrame;
	QLabel*	_lbCurrentPage;
	QPushButton* _btnPrev;
	QPushButton* _btnNext;
	QPushButton* _btnStart;
	QPushButton* _btnEnd;

	QLineEdit* _edtJumpTo;		// 转到
	QPushButton* _btnJumpTo;

	//
	// 数据相关
	// 
	std::vector<std::vector<QTableWidgetItem*> > _dataSet;
	int _totalRowCount;		// 总行数
	int _rowCountPerPage;	// 每页行数
	int _pageCount;			// 总页数
	int _currentPage;		// 当前页

};

#endif // PAGETABLEWIDGET_H
