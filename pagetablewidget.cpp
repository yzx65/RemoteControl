#include "pagetablewidget.h"

#include <QtGui>

const char* BUTTON_SYTLE = "QPushButton{\
						   border:1px solid #aaaaaa;\
						   background:transparent;\
						   }\
						   QPushButton:hover{\
						   background:#cccccc;\
						   }";

const char* TABLE_STYLE = "QHeaderView::section{\
						  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeee);\
						  padding-left: 10px;\
						  border:none;\
						  border-right: 1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #dddddd, stop:1 #ffffff);\
						  border-bottom: 0px solid #eeeeee;\
						  height:25px;\
						  color:#333333;\
						  font-family:'Microsoft Yahei';\
						  text-align:center left;\
						  }\
						  QTableWidget QHeaderView::section:hover{\
						  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ddeeff, stop:1 #eef0ff);\
						  }\
						  QTableWidget:item{\
						  padding-left:10px;\
						  }\
						  QAbstractItemView#_table{\
						  border:1px solid #cccccc;\
						  border-bottom-width:0px;\
						  border-left-width:0px;\
						  }\
						  QHeaderView::down-arrow {\
						  image: none;\
						  }\
						  QHeaderView::up-arrow {\
						  image: none;\
						  }\
						  QScrollBar:vertical {\
						  border: 0px solid grey;\
						  background: transparent;\
						  width: 10px;\
						  border-bottom:0px solid #aaaaaa;\
						  }\
						  QScrollBar::handle:vertical {\
						  background: #cccccc;\
						  min-height: 100px;\
						  }\
						  QScrollBar::handle:vertical:hover {\
						  background: #aaaaaa;\
						  min-height: 100px;\
						  }\
						  QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical {\
						  border:none;\
						  background:transparent;\
						  }";

const char* EDIT_STYLE = "QLineEdit{\
						 border:1px solid #aaaaaa;\
						 }";

const char* FRAME_STYLE = "QFrame#_bottomFrame{\
						  border:1px solid #cccccc;\
						  border-top-width:0px;\
						  border-left-width:0px;\
						  background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #eeeeff);\
						  }";

// ////////////////////////////////////////////////////////////////////////////////
// @public 构造函数
//
PageTableWidget::PageTableWidget(QWidget *parent)
	: QWidget(parent)
	, _table(NULL)
	, _lbCurrentPage(NULL)
	, _btnStart(NULL)
	, _btnPrev(NULL)
	, _btnNext(NULL)
	, _btnEnd(NULL)
	, _totalRowCount(0)
	, _rowCountPerPage(40)
	, _pageCount(1)
	, _currentPage(1)
{
	InitLayout();
	InitSignals();
	InitConnection();
	InitAppearance();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 析构函数
//
PageTableWidget::~PageTableWidget()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置列数
// @remark 初始化之后必须调用此函数
//
void PageTableWidget::SetColumnCount(unsigned int count)
{
	_table->setColumnCount(count);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置列标题
//
void PageTableWidget::SetColumnLabels(const QStringList& labels)
{
	_table->setHorizontalHeaderLabels(labels);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置每页显示行数
// @remark 默认为 500
//
void PageTableWidget::SetRowCountPerPage(unsigned int count)
{
	_rowCountPerPage = count;
	_table->setRowCount(count);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 插入一行
// @remark vector 在中间插入的话开销太大，故在尾部插入
//
void PageTableWidget::AppendRow()
{
	_totalRowCount++;
	
	CalculatePage();

	std::vector<QTableWidgetItem*> row;

	for (int i = 0; i < _table->columnCount(); i++)
	{
		row.push_back(NULL);
	}

	_dataSet.push_back(row);

	//RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 设置 item
//
void PageTableWidget::SetAppendRowItem(int column, QTableWidgetItem* item)
{
	std::vector<QTableWidgetItem*>& rowData = _dataSet[_totalRowCount-1];
	rowData[column] = item;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 刷新页面
//
void PageTableWidget::RefreshPage()
{
	// 计算要显示的范围
	int starRow = (_currentPage-1)*_rowCountPerPage;
	int endRow = starRow+_rowCountPerPage < _totalRowCount ? 
		starRow+_rowCountPerPage : _totalRowCount;

	// 清空 table
	for (int i = 0; i < _rowCountPerPage; i++)
	{
		for(int j = 0; j < _table->columnCount(); j++)
		{
			if ( 0 != _table->item(i, j) )
			{
				_table->takeItem(i, j);
			}
		}
	}

	// 更新 rowCount
	_table->setRowCount(endRow-starRow);

	// 显示范围内的数据，由于新添加的数据要显示在最前面
	// 所以从尾部开始算起

	int maxIndex = _dataSet.size()-1;
	for ( int i = _totalRowCount-starRow-1, row = 0; i >= _totalRowCount-endRow; i--, row++ )
	{
		if ( i > maxIndex )
			continue;

		std::vector<QTableWidgetItem*>& rowData = _dataSet[i];

		int maxSubIndex = rowData.size()-1;

		for ( int j = 0; j < _table->columnCount() && j <= maxSubIndex ; j++ )
		{
			QTableWidgetItem* item = rowData[j];
			_table->setItem(row, j, item);
		}
	}

	// 更新提示信息
	_lbCurrentPage->setText(QString::fromLocal8Bit("第 %1 页, 共 %2 页").arg(_currentPage).arg(_pageCount));

	// 更新 '转到' 的合理范围
	QIntValidator* range = new QIntValidator(1, _pageCount, 0);
	_edtJumpTo->setValidator(range);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public 清空
//
void PageTableWidget::Clear()
{
	_totalRowCount = 0;
	_pageCount = 1;
	_currentPage = 1;

	_dataSet.clear();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 第一页
//
void PageTableWidget::FirstPage()
{
	_currentPage = 1;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 上一页
//
void PageTableWidget::PrevPage()
{
	_currentPage = _currentPage-1 > 0 ? _currentPage-1 : 1;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 下一页
//
void PageTableWidget::NextPage()
{
	_currentPage = _currentPage+1 <= _pageCount ? _currentPage+1 : _pageCount;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 最后一页
//
void PageTableWidget::LastPage()
{
	_currentPage = _pageCount;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot 转到
//
void PageTableWidget::JumpTo()
{
	if ( "" != _edtJumpTo->text() )
	{
		_currentPage = _edtJumpTo->text().toUInt();
		RefreshPage();
	}
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化 signals
//
void PageTableWidget::InitSignals()
{
	connect(_table, SIGNAL(itemClicked(QTableWidgetItem*)), this, SIGNAL(itemClicked(QTableWidgetItem*)));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化布局
//
void PageTableWidget::InitLayout()
{
	_lbCurrentPage = new QLabel(QString::fromLocal8Bit("第 1 页, 共 1 页"), this);

	_edtJumpTo = new QLineEdit(this);
	_btnJumpTo = new QPushButton(QString::fromLocal8Bit("->"), this);

	_btnPrev = new QPushButton(QString::fromLocal8Bit("<"), this);
	_btnNext = new QPushButton(QString::fromLocal8Bit(">"), this);
	_btnStart = new QPushButton(QString::fromLocal8Bit("|<"), this);
	_btnEnd = new QPushButton(QString::fromLocal8Bit(">|"), this);

	QVBoxLayout* mainLayout = new QVBoxLayout;

	_table = new QTableWidget(this);
	_table->setRowCount(_rowCountPerPage);

	_bottomFrame = new QFrame(this);
	QHBoxLayout* bottomLayout = new QHBoxLayout;
	_bottomFrame->setLayout(bottomLayout);

	bottomLayout->addWidget(_lbCurrentPage);
	bottomLayout->addStretch();
	bottomLayout->addWidget(_btnStart);
	bottomLayout->addWidget(_btnPrev);
	bottomLayout->addWidget(_btnNext);
	bottomLayout->addWidget(_btnEnd);
	bottomLayout->addSpacing(20);
	bottomLayout->addWidget(_edtJumpTo);
	bottomLayout->addWidget(_btnJumpTo);

	bottomLayout->setContentsMargins(10, 5, 10, 5);

	mainLayout->addWidget(_table);
	mainLayout->addWidget(_bottomFrame);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	this->setLayout(mainLayout);
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化 slots
//
void PageTableWidget::InitConnection()
{
	connect(_btnStart, SIGNAL(clicked()), this, SLOT(FirstPage()));
	connect(_btnPrev, SIGNAL(clicked()), this, SLOT(PrevPage()));
	connect(_btnNext, SIGNAL(clicked()), this, SLOT(NextPage()));
	connect(_btnEnd, SIGNAL(clicked()), this, SLOT(LastPage()));

	connect(_btnJumpTo, SIGNAL(clicked()), this, SLOT(JumpTo()));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private 初始化外观
//
void PageTableWidget::InitAppearance()
{
	// 表格外观
	_table->setSortingEnabled(false);
	_table->setSelectionMode(QAbstractItemView::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_table->setShowGrid(false);
	_table->horizontalHeader()->setHighlightSections(false);
	_table->horizontalHeader()->setStretchLastSection(true);
	_table->horizontalHeader()->setDefaultSectionSize(150);
	_table->verticalHeader()->setHighlightSections(false);
	_table->verticalHeader()->setVisible(false);
	_table->verticalHeader()->setDefaultSectionSize(21);
	_table->setFrameShape(QFrame::NoFrame);

	_table->setObjectName("_table");
	_table->setStyleSheet(TABLE_STYLE);

	// 底部 frame 外观
	_bottomFrame->setObjectName("_bottomFrame");
	_bottomFrame->setStyleSheet(FRAME_STYLE);

	//
	// '转到' 编辑框
	//
	_edtJumpTo->setFixedSize(30, 20);
	_edtJumpTo->setStyleSheet(EDIT_STYLE);
	
	// 转到的合理范围
	QIntValidator* range = new QIntValidator(1, 1, this);
	_edtJumpTo->setValidator(range);

	//
	// '转到' 按钮
	_btnJumpTo->setFixedSize(20, 20);
	_btnJumpTo->setStyleSheet(BUTTON_SYTLE);
	_btnJumpTo->setToolTip(QString::fromLocal8Bit("转到"));

	//
	// 按钮外观
	//
	_btnStart->setFixedSize(20, 20);
	_btnEnd->setFixedSize(20, 20);
	_btnPrev->setFixedSize(20, 20);
	_btnNext->setFixedSize(20, 20);

	_btnStart->setToolTip(QString::fromLocal8Bit("第一页"));
	_btnEnd->setToolTip(QString::fromLocal8Bit("最后一页"));
	_btnPrev->setToolTip(QString::fromLocal8Bit("上一页"));
	_btnNext->setToolTip(QString::fromLocal8Bit("最后一页"));

	_btnStart->setStyleSheet(BUTTON_SYTLE);
	_btnEnd->setStyleSheet(BUTTON_SYTLE);
	_btnPrev->setStyleSheet(BUTTON_SYTLE);
	_btnNext->setStyleSheet(BUTTON_SYTLE);
}