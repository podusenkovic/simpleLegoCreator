#ifndef LEGO_H
#define LEGO_H

#include <QPainter>
#include <QWidget>
#include <QDebug>


class Lego {
protected:
	int x, y, width, height;
	bool employed;
	QColor color;
public:
	Lego(Lego *p, int _w, int _h) :
		width(_w), height(_h),
		x((p->x + p->width / 2 - _w / 2)), y(p->y + p->height),
		employed(false), color(QColor(rand()%256, rand()%256, rand()%256)){
		p->employed = true;
	}
	Lego(int _x, int _w, int _h) :
		width(_w), height(_h),
		x(_x), y(0), employed(false), 
		color(QColor(rand()%256, rand()%256, rand()%256)){}
		
	virtual void draw(QPainter*) = 0;
	virtual short isInside(QPoint) = 0;
	
	bool isEmployed(){
		return employed;
	}
};

class Rect : public Lego {
public:
	Rect(Lego *p, int _w, int _h) :
		Lego(p, _w, _h) {}
	Rect(int _x, int _w, int _h) :
		Lego(_x, _w, _h) {}
	
	void draw(QPainter* painter){
		painter->setBrush(QBrush(color));
		painter->drawRect(x, y, width, height);
	}
	short isInside(QPoint a){
		if (a.x() > x && a.x() < x + width &&
			a.y() > y && a.y() < y + height)
			return 1;
		if (a.x() > x && a.x() < x + width)
			return 2;
		return 0;
	}
};

class Triangle : public Lego {
public:
	Triangle(Lego *p, int _w, int _h) :
		Lego(p, _w, _h) {}
	Triangle(int _x, int _w, int _h) :
		Lego(_x, _w, _h) {}
	
	void draw(QPainter* painter){
		painter->setBrush(QBrush(color));
		QPoint *points = new QPoint[3];
		points[0] = QPoint(x, y);
		points[1] = QPoint(x + width, y);
		points[2] = QPoint(x + width/2, y + height);
		painter->drawPolygon(points,3);
	}
	
	short isInside(QPoint a){
		double res1 = -(width) * (y - a.y());
		double res2 = (x + width - a.x()) * (height) - (-width/2) * (y - a.y());
		double res3 = (x + width/2 - a.x()) * (-height) - (-width/2) * (y + height - a.y());
		if (res1/res2 > 0 && res2/res3 > 0)
			return 1;
		if (a.x() > x && a.x() < x + width)
			return 2;
		return 0;
	}
};

#endif
