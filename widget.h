#ifndef WIDGET_H
#define WIDGET_H

#include "Lego.h"

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>

class Widget : public QWidget
{
	Q_OBJECT
	
public:
	Widget(QWidget *parent = 0);
	~Widget();
	void paintEvent(QPaintEvent *event);
	
	void mousePressEvent(QMouseEvent *event);
private:
	QVector<Lego*> legoBricks;
};

#endif // WIDGET_H
