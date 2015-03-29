#ifndef CUSTOMTREE_H
#define CUSTOMTREE_H

#include <QTreeWidget>

class CustomTree : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTree(QWidget *parent);
	~CustomTree();

protected:
	void mouseReleaseEvent(QMouseEvent *event);

private:
	
};

#endif // CUSTOMTREE_H
