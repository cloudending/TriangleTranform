#include "triangletransform.h"
#include "glviewer.h"
#include <QFileDialog>
#include <QString>
#include "ImageTransform.h"
TriangleTransform::TriangleTransform(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//this->ui.mainLayout->addWidget(GLViewer::getInstance());
	//setWindowState(Qt::WindowMaximized);
	QObject::connect(ui.actionOpenImage, SIGNAL(triggered()), this, SLOT(onActionOpenImage()));
	QObject::connect(ui.actionTransform, SIGNAL(triggered()), this, SLOT(onActionTransform()));
	this->srcImgArea = new PaintArea(this);
	ui.horizontalLayout_2->addWidget(this->srcImgArea);
	this->dstImgArea = new PaintArea(this);
	ui.horizontalLayout_2->addWidget(this->dstImgArea);
}

TriangleTransform::~TriangleTransform()
{
	
}

void TriangleTransform::onActionOpenImage()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Image choose"));
	if (!filePath.isEmpty())
	{
		this->srcImgArea->loadImage(filePath);
		std::vector<Wml::Vector3f> triPoint;
		triPoint.push_back(Wml::Vector3f(this->srcImgArea->imgWidth*0.3, this->srcImgArea->imgHeigth*0.1, 1.0));
		triPoint.push_back(Wml::Vector3f(this->srcImgArea->imgWidth*0.2, this->srcImgArea->imgHeigth*0.5, 1.0));
		triPoint.push_back(Wml::Vector3f(this->srcImgArea->imgWidth*0.6, this->srcImgArea->imgHeigth*0.3, 1.0));
		this->srcImgArea->setTriPoint(triPoint);
		this->srcImgArea->update();
	}
}

void TriangleTransform::onActionTransform()
{
	if (!this->srcImgArea->isImgEmpty())
	{
	
		ImageTransform imgTrans(this->srcImgArea->filePath);
		imgTrans.setType(TRIANGLETRANS);
		std::vector<Wml::Vector2f> src, dst;
		std::cout << "src" << std::endl;
		for (int i = 0; i < 3; i++)
		{
			src.push_back(Wml::Vector2f(this->srcImgArea->triPoint[i][0], this->srcImgArea->triPoint[i][1]));
			
		}
		
		int h = this->srcImgArea->imgHeigth;
		int w = this->srcImgArea->imgWidth;

		dst.push_back(Wml::Vector2f(w*0.5, h*0.2));
		dst.push_back(Wml::Vector2f(w*0.1, h*0.5));
		dst.push_back(Wml::Vector2f(w*0.7, h*0.7));
		for (int i = 0; i < src.size(); i++)
		{
			src[i][1] = h-1 - src[i][1];
			dst[i][1] = h-1 - dst[i][1];
		}
		imgTrans.setTriangleTransPoint(src, dst);
		
		imgTrans.doTransform();
		//imgTrans.testCopyToDstImg();
		this->dstImgArea->loadFromBoxPartImage(imgTrans.getBoxPartImage());
		this->dstImgArea->update();
	}
}
