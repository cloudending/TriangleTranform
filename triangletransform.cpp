#include "triangletransform.h"
#include "glviewer.h"
TriangleTransform::TriangleTransform(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->ui.mainLayout->addWidget(GLViewer::getInstance());
}

TriangleTransform::~TriangleTransform()
{

}
