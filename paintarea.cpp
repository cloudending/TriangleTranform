#include "paintarea.h"

#include <QPainter>
#include <QPen>
#include <iostream>
PaintArea::PaintArea(QWidget *parent)
	: QWidget(parent),isLoad(false)
{

}

PaintArea::~PaintArea()
{

}

void PaintArea::paintEvent( QPaintEvent * p )
{
	if (isLoad)
	{
		float ratio = 1;
		if (this->width() < img.width())
		{
			ratio = (float)this->width() / (float)img.width();
			scaledImg = img.scaled(QSize((int)(img.width()*ratio), (int)(img.height()*ratio)));
		}
		else
			scaledImg = img.copy();
		std::cout << scaledImg.width() << " " << scaledImg.height() << std::endl;
		QPixmap temp = QPixmap::fromImage(scaledImg.copy());
		QPainter painter(&temp);
		QPen pen;
		pen.setColor(Qt::darkYellow);
		pen.setWidth(2);
		painter.setPen(pen);
		for (int i = 0; i < triPoint.size(); i++)
		{
			painter.drawLine(QPointF(triPoint[i][0]*ratio, triPoint[i][1]*ratio), 
						     QPointF(triPoint[(i+1)%3][0]*ratio, triPoint[(i+1)%3][1]*ratio));
		}
		QPainter wp(this);
		wp.drawPixmap(0, this->height()/2-temp.height()/2 , temp.width(), temp.height(), temp);
	}
}

void PaintArea::mousePressEvent( QMouseEvent* e )
{

}

void PaintArea::mouseReleaseEvent( QMouseEvent* e )
{

}

void PaintArea::mouseMoveEvent( QMouseEvent* e )
{

}

void PaintArea::loadImage( QString filePath )
{
	img.load(filePath);
	imgHeigth = img.height();
	imgWidth = img.width();
	this->filePath = filePath;
	isLoad = true;
}

void PaintArea::setTriPoint( std::vector<Wml::Vector3f> p )
{
	triPoint = p;
}

void PaintArea::loadFromBoxPartImage( BoxPartImage& bpImg )
{
	img = bpImg.img->copy();
	if (img.width() > this->width())
	{
		float ratio = (float)this->width() / (float)img.width();
		scaledImg = img.scaled(QSize((int)img.width()*ratio, (int)img.height()*ratio));
	}
	else
		scaledImg = img.copy();
	imgHeigth = img.height();
	imgWidth = img.width();
	this->filePath = "";
	isLoad = true;
}
