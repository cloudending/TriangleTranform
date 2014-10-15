#include "triangletransform.h"
#include "glviewer.h"
#include <QFileDialog>
#include <QString>
TriangleTransform::TriangleTransform(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->ui.mainLayout->addWidget(GLViewer::getInstance());
	QObject::connect(ui.actionOpenImage, SIGNAL(triggered()), this, SLOT(onActionOpenImage()));
}

TriangleTransform::~TriangleTransform()
{
	
}

void TriangleTransform::onActionOpenImage()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Image choose"));
	if (!filePath.isEmpty())
	{
		GLViewer::getInstance()->loadImage(filePath);
		GLViewer::getInstance()->updateGL();
	}
}
