#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QImage>
#include <vector>
#include "WmlMathLib.h"
#include <ImageTransform.h>
class PaintArea : public QWidget
{
	Q_OBJECT

public:
	PaintArea(QWidget *parent);
	~PaintArea();
	void loadImage(QString filePath);
	void loadFromBoxPartImage(BoxPartImage& bpImg);
	void setTriPoint(std::vector<Wml::Vector3f> p);
	void paintEvent(QPaintEvent * p);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	int imgHeigth;
	int imgWidth;
	std::vector<Wml::Vector3f> triPoint; // scaledImg point
	QString filePath;
	bool isImgEmpty(){return !isLoad;}
private:
	QImage img;
	QImage scaledImg;
	bool isLoad;
	
};

#endif // PAINTAREA_H
