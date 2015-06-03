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
// @public ���캯��
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
// @public ��������
//
PageTableWidget::~PageTableWidget()
{

}

// ////////////////////////////////////////////////////////////////////////////////
// @public ��������
// @remark ��ʼ��֮�������ô˺���
//
void PageTableWidget::SetColumnCount(unsigned int count)
{
	_table->setColumnCount(count);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public �����б���
//
void PageTableWidget::SetColumnLabels(const QStringList& labels)
{
	_table->setHorizontalHeaderLabels(labels);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ����ÿҳ��ʾ����
// @remark Ĭ��Ϊ 500
//
void PageTableWidget::SetRowCountPerPage(unsigned int count)
{
	_rowCountPerPage = count;
	_table->setRowCount(count);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ����һ��
// @remark vector ���м����Ļ�����̫�󣬹���β������
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
// @public ���� item
//
void PageTableWidget::SetAppendRowItem(int column, QTableWidgetItem* item)
{
	std::vector<QTableWidgetItem*>& rowData = _dataSet[_totalRowCount-1];
	rowData[column] = item;
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ˢ��ҳ��
//
void PageTableWidget::RefreshPage()
{
	// ����Ҫ��ʾ�ķ�Χ
	int starRow = (_currentPage-1)*_rowCountPerPage;
	int endRow = starRow+_rowCountPerPage < _totalRowCount ? 
		starRow+_rowCountPerPage : _totalRowCount;

	// ��� table
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

	// ���� rowCount
	_table->setRowCount(endRow-starRow);

	// ��ʾ��Χ�ڵ����ݣ���������ӵ�����Ҫ��ʾ����ǰ��
	// ���Դ�β����ʼ����

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

	// ������ʾ��Ϣ
	_lbCurrentPage->setText(QString::fromLocal8Bit("�� %1 ҳ, �� %2 ҳ").arg(_currentPage).arg(_pageCount));

	// ���� 'ת��' �ĺ���Χ
	QIntValidator* range = new QIntValidator(1, _pageCount, 0);
	_edtJumpTo->setValidator(range);
}

// ////////////////////////////////////////////////////////////////////////////////
// @public ���
//
void PageTableWidget::Clear()
{
	_totalRowCount = 0;
	_pageCount = 1;
	_currentPage = 1;

	_dataSet.clear();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��һҳ
//
void PageTableWidget::FirstPage()
{
	_currentPage = 1;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��һҳ
//
void PageTableWidget::PrevPage()
{
	_currentPage = _currentPage-1 > 0 ? _currentPage-1 : 1;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ��һҳ
//
void PageTableWidget::NextPage()
{
	_currentPage = _currentPage+1 <= _pageCount ? _currentPage+1 : _pageCount;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ���һҳ
//
void PageTableWidget::LastPage()
{
	_currentPage = _pageCount;
	RefreshPage();
}

// ////////////////////////////////////////////////////////////////////////////////
// @private slot ת��
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
// @private ��ʼ�� signals
//
void PageTableWidget::InitSignals()
{
	connect(_table, SIGNAL(itemClicked(QTableWidgetItem*)), this, SIGNAL(itemClicked(QTableWidgetItem*)));
}

// ////////////////////////////////////////////////////////////////////////////////
// @private ��ʼ������
//
void PageTableWidget::InitLayout()
{
	_lbCurrentPage = new QLabel(QString::fromLocal8Bit("�� 1 ҳ, �� 1 ҳ"), this);

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
// @private ��ʼ�� slots
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
// @private ��ʼ�����
//
void PageTableWidget::InitAppearance()
{
	// ������
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

	// �ײ� frame ���
	_bottomFrame->setObjectName("_bottomFrame");
	_bottomFrame->setStyleSheet(FRAME_STYLE);

	//
	// 'ת��' �༭��
	//
	_edtJumpTo->setFixedSize(30, 20);
	_edtJumpTo->setStyleSheet(EDIT_STYLE);
	
	// ת���ĺ���Χ
	QIntValidator* range = new QIntValidator(1, 1, this);
	_edtJumpTo->setValidator(range);

	//
	// 'ת��' ��ť
	_btnJumpTo->setFixedSize(20, 20);
	_btnJumpTo->setStyleSheet(BUTTON_SYTLE);
	_btnJumpTo->setToolTip(QString::fromLocal8Bit("ת��"));

	//
	// ��ť���
	//
	_btnStart->setFixedSize(20, 20);
	_btnEnd->setFixedSize(20, 20);
	_btnPrev->setFixedSize(20, 20);
	_btnNext->setFixedSize(20, 20);

	_btnStart->setToolTip(QString::fromLocal8Bit("��һҳ"));
	_btnEnd->setToolTip(QString::fromLocal8Bit("���һҳ"));
	_btnPrev->setToolTip(QString::fromLocal8Bit("��һҳ"));
	_btnNext->setToolTip(QString::fromLocal8Bit("���һҳ"));

	_btnStart->setStyleSheet(BUTTON_SYTLE);
	_btnEnd->setStyleSheet(BUTTON_SYTLE);
	_btnPrev->setStyleSheet(BUTTON_SYTLE);
	_btnNext->setStyleSheet(BUTTON_SYTLE);
}