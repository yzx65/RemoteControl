#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui>
#include <QPixmap>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    void SetWidget(QWidget* widget);

protected:
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);
    
private:
    QPixmap m_shadow;
};

#endif // WIDGET_H
