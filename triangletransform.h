#ifndef TRIANGLETRANSFORM_H
#define TRIANGLETRANSFORM_H

#include <QtWidgets/QMainWindow>
#include "ui_triangletransform.h"

class TriangleTransform : public QMainWindow
{
	Q_OBJECT

public:
	TriangleTransform(QWidget *parent = 0);
	~TriangleTransform();

private:
	Ui::TriangleTransformClass ui;
};

#endif // TRIANGLETRANSFORM_H
