#ifndef TRIANGLETRANSFORM_H
#define TRIANGLETRANSFORM_H

#include <QtWidgets/QMainWindow>
#include "ui_triangletransform.h"
#include "paintarea.h"
class TriangleTransform : public QMainWindow
{
	Q_OBJECT

public:
	TriangleTransform(QWidget *parent = 0);
	~TriangleTransform();
private slots:
		void onActionOpenImage();
		void onActionTransform();
private:
	Ui::TriangleTransformClass ui;
	PaintArea* srcImgArea;
	PaintArea* dstImgArea;
};

#endif // TRIANGLETRANSFORM_H
