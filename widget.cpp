#include "widget.h"
#include <time.h>

#define WIDTH 40
#define HEIGHT 40

Widget::Widget(QWidget *parent)
	: QWidget(parent)
{	
	srand(time(NULL));
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()),
			this, SLOT(update()));
	timer->start(30);
}

Widget::~Widget()
{
	legoBricks.erase(legoBricks.begin(), legoBricks.end());
}


void Widget::paintEvent(QPaintEvent *event){
	QPainter painter(this);
	painter.translate(0, this->height());
	painter.scale(1,-1);
	
	for (int i = 0; i < legoBricks.size(); i++){
		legoBricks[i]->draw(&painter);
	}
}


void Widget::mousePressEvent(QMouseEvent *event){
	QPoint posit = event->pos();
	posit.setY(this->height() - posit.y());
	for (int i = 0; i < legoBricks.size(); i++)
		if (legoBricks[i]->isInside(posit) == 1){
			if (!legoBricks[i]->isEmployed())
				if (event->button() == Qt::LeftButton)
					legoBricks.push_back(new Rect(legoBricks[i], WIDTH, HEIGHT));
				else legoBricks.push_back(new Triangle(legoBricks[i], WIDTH, HEIGHT));
			return;
		}
		else if (legoBricks[i]->isInside(posit) == 2 && !legoBricks[i]->isEmployed())
			return;
	if (event->button() == Qt::LeftButton)
		legoBricks.push_back(new Rect(event->pos().x(), WIDTH, HEIGHT));
	else legoBricks.push_back(new Triangle(event->pos().x(), WIDTH, HEIGHT));
}
