#include "DlgContainer.h"

#include <QObject>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QToolButton>

#include "skin.h"
#include "targetdlg.h"

CustomLabel::CustomLabel(QWidget* parent)
	: QWidget(parent)
	, m_state(NORMAL)
{
	setFixedSize(180, 40);
	setMouseTracking(true);
	InitCloseButton();

	m_pic[0] = QPixmap("image/function_normal.png");
	m_pic[1] = QPixmap("image/function_hovered.png");
	m_pic[2] = QPixmap("image/function_selected.png");

	m_brush[0] = QBrush(QColor(88,115,201));
	m_brush[1] = QBrush(QColor(108, 125, 217));
	m_brush[2] = QBrush(QColor(122, 141, 217));
}

void CustomLabel::InitCloseButton()
{
	m_closeBtn = new QPushButton(this);
	connect(m_closeBtn, SIGNAL(clicked()),this, SIGNAL(CloseLabel()));
	m_closeBtn->setFixedSize(16, 16);
	m_closeBtn->move(150, 12);
	m_closeBtn->setStyleSheet(
		"QPushButton{"
		"border:0px solid black;"
		"border-image:url(image/close_normal.png);}"
		"QPushButton:hover{"
		"border-image:url(image/close_hover.png);}"
		"QPushButton:pressed{"
		"border-image:url(image/close_pressed.png);}");

	m_closeBtn->hide();
}

void CustomLabel::SetCurrentState(CustomLabel::PaintState state)
{
	m_state = state;
	update();
}

void CustomLabel::SetTargetDlg(TargetDlg* tarDlg)
{
	m_targetDlg = tarDlg;
}

void CustomLabel::SetStackIndex(int index)
{
	m_stackIndex = index;
}

void CustomLabel::SetText(QString text)
{
	m_text = text;
}

void CustomLabel::SetIcon(QString icon)
{
	m_icon = icon;
	m_iconLoader.load(m_icon);
	update();
}

void CustomLabel::SetUuid(unsigned int uuid)
{
	m_uuid = uuid;
}

void CustomLabel::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	std::wstring setting = GetExePath() + L"\\setting.ini";
	std::wstring skinName = ReadStringPolicyFromLocal(L"Skin", L"Name", setting.c_str());

	if ( L"skin_blue" == skinName )
	{
		painter.fillRect(this->rect(), m_brush[m_state]);
		QPen lpen(QColor(122, 141, 217));
		painter.setPen(lpen);
		painter.drawLine(QPoint(0, this->height()-1), QPoint(this->width(), this->height()-1));
	}

	if ( L"skin_black" == skinName )
		painter.drawPixmap(this->rect(), m_pic[m_state], m_pic[m_state].rect());

	// Draw icon
	QRectF iconRect(15, 8, 24, 24);
	painter.drawPixmap(iconRect, m_iconLoader, m_iconLoader.rect());

	// Draw text
	QPen pen(QColor(250, 250, 250));
	QFont font("Microsoft Yahei", 10);
	painter.setFont(font);
	painter.setPen(pen);
	QRectF textRect = this->rect();
	textRect.setX(45);
	painter.drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, m_text);
}

void CustomLabel::mouseReleaseEvent(QMouseEvent *e)
{
	m_state = CHECKED;
	m_closeBtn->hide();
	update();
	emit clicked();
}

void CustomLabel::enterEvent(QEvent* e)
{
	if ( m_state == NORMAL )
		m_state = HORVER;

	if ( m_state != CHECKED )
		m_closeBtn->show();

	update();
}

void CustomLabel::leaveEvent(QEvent* e)
{
	if ( m_state == HORVER )
		m_state = NORMAL;

	m_closeBtn->hide();
	update();
}

//-------------------------------------------------------------------------------

DlgContainer::DlgContainer(QWidget* parent /* = 0 */)
	: QWidget(parent)
	, m_contentStack(0)
{
	InitLayout();
}

DlgContainer::~DlgContainer()
{

}

void DlgContainer::InitLayout()
{
	setMinimumSize(1310, 715);

	setObjectName("dlgContainer");

	std::wstring setting = GetExePath() + L"\\setting.ini";
	std::wstring skinName = ReadStringPolicyFromLocal(L"Skin", L"Name", setting.c_str());

	m_contentStack = new QStackedWidget;

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	m_navigate = new QWidget(this);
	m_navigate->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_navigate->setObjectName("m_navigate");
	m_navigate->setFixedWidth(180);
	QVBoxLayout* navigateLayout = new QVBoxLayout(m_navigate);
	navigateLayout->setSpacing(0);
	navigateLayout->setContentsMargins(0, 0, 0, 0);

	QToolButton* back = new QToolButton(this);
	back->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	back->setIcon(QIcon(QPixmap("image/EXIT.png")));
	back->setStyleSheet(GetStylesheetFromFile(L"backbtn"));

	back->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	back->setText(QString::fromLocal8Bit("返回主界面"));
	navigateLayout->addWidget(back);
	connect(back, SIGNAL(clicked()), this, SIGNAL(emitBack()));

	navigateLayout->addSpacerItem(new QSpacerItem(40, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

	m_contentStack->setObjectName("m_contentStack");

	m_scrollLeft = new QScrollArea(this);
	m_scrollLeft->setFixedWidth(180);
	m_scrollLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_scrollLeft->setWidget(m_navigate);
	m_scrollLeft->setWidgetResizable(true);
	m_scrollLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_scrollLeft->setStyleSheet(GetStylesheetFromFile(L"scrollbar"));
	layout->addWidget(m_scrollLeft);
	layout->addWidget(m_contentStack);

	m_tabGroup = new QButtonGroup(this);

	if ( L"skin_blue" == skinName )
	{
		setStyleSheet("QWidget#dlgContainer{background: rgb(88,115,201);}");
		m_navigate->setStyleSheet(
			"QWidget#m_navigate{"
			"background-color:rgb(88,115,201);"
			"}");
	}

	if ( L"skin_black" == skinName )
	{
		setStyleSheet("QWidget#dlgContainer{background: rgb(71,78,94);}");
		m_navigate->setStyleSheet(
			"QWidget#m_navigate{"
			"background-color:rgb(46,52,52);"
			"}");
	}
}

void DlgContainer::AddDialog(QWidget* dialog, unsigned int uuid, QString tabName, QString icon)
{
	if ( m_tabMap.find(uuid) != m_tabMap.end() )
		return;

	CustomLabel* tab = AddCustomLabel(tabName, icon);
	m_tabMap[uuid] = tab;

	(qobject_cast<QVBoxLayout*>(m_navigate->layout()))->insertWidget(1, tab);
	int index = m_contentStack->addWidget(dialog);
	tab->SetStackIndex(index);
	tab->SetTargetDlg((TargetDlg*)dialog);
	tab->SetUuid(uuid);
	connect(tab, SIGNAL(clicked()), this, SLOT(LabelSelected()));
	connect(tab, SIGNAL(CloseLabel()), this, SLOT(LabelClosed()));
}

void DlgContainer::SetCurrentTab(unsigned int uuid)
{
	CustomLabel* tab = m_tabMap[uuid];
	tab->click();
}

void DlgContainer::LabelSelected()
{
	// Uncheck all labels
	std::map<unsigned int, CustomLabel*>::iterator it = m_tabMap.begin();
	while ( it != m_tabMap.end() )
	{
		CustomLabel* tab = (*it).second;
		tab->SetCurrentState(CustomLabel::NORMAL);
		++it;
	}

	CustomLabel* tab = qobject_cast<CustomLabel*>(sender());
	tab->SetCurrentState(CustomLabel::CHECKED);

	m_contentStack->setCurrentIndex(tab->GetStackIndex());
	setWindowTitle(QString::fromLocal8Bit("当前目标 : ") + tab->Text());
}

void DlgContainer::LabelClosed()
{
	CustomLabel* tab = qobject_cast<CustomLabel*>(sender());
	TargetDlg* tarDlg = tab->GetTargetDlg();
	tarDlg->tarBlock->frmTarControl = NULL;
	//tarDlg->setParent(NULL);
	//delete tarDlg;

	std::map<unsigned int, CustomLabel*>::iterator it = m_tabMap.find(tab->GetUuid());
	if ( it != m_tabMap.end() )
		m_tabMap.erase(it);

	tab->setParent(NULL);
	delete tab;

	if ( 0 == m_tabMap.size() )
		hide();
}

CustomLabel* DlgContainer::AddCustomLabel(QString title, QString icon)
{
	CustomLabel* tab = new CustomLabel;
	tab->SetText(title);
	tab->SetIcon(icon);
	tab->SetCurrentState(CustomLabel::CHECKED);

	return tab;
}

void DlgContainer::ChangeLabelIcon(unsigned int uuid, QString icon)
{
	if ( m_tabMap.find(uuid) == m_tabMap.end() )
		return;

	CustomLabel* label = m_tabMap[uuid];

	if ( label )
		label->SetIcon(icon);
}

void DlgContainer::ChangeLabelText( unsigned int uuid, QString text )
{
	if ( m_tabMap.find(uuid) == m_tabMap.end() )
		return;

	CustomLabel* label = m_tabMap[uuid];

	if ( label )
		label->SetText(text);
}