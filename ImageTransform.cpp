#include "ImageTransform.h"
#include <algorithm>
#include <iostream>
ImageTransform::ImageTransform( QString filePath )
{
	this->srcImage.load(filePath);
	this->dstImage.img = NULL;
}

void ImageTransform::setType(TRANSFORMTYPE t)
{
	this->type = t;
}

void ImageTransform::triImageTransform()
{
	Wml::Matrix3f homoCoordSrc(this->src[0][0], this->src[1][0], this->src[2][0],
							   this->src[0][1], this->src[1][1], this->src[2][1],
							   1,               1,               1);
	
	Wml::Matrix3f homoCoordDst(this->dst[0][0], this->dst[1][0], this->dst[2][0],
							   this->dst[0][1], this->dst[1][1], this->dst[2][1],
							   1,               1,               1);
	
	Wml::Matrix3f transMat = homoCoordDst*homoCoordSrc.Inverse();
	std::cout << "src:" << std::endl;
	showMatrix3(homoCoordSrc);
	std::cout << "dst:" << std::endl;
	showMatrix3(homoCoordDst);
	std::cout << "transMat:" << std::endl;
	showMatrix3(transMat);

	std::vector<Wml::Vector2f> dstCopy = dst;

	std::sort(dstCopy.begin(), dstCopy.end(), comparePoint);
	if (dstCopy[0][1] == dstCopy[1][1] && dstCopy[1][1] != dstCopy[2][1])
	{
		if (dstCopy[0][0] > dstCopy[1][0])
		{
			std::swap(dstCopy[0], dstCopy[1]);
		}
		flatTopTriTrans(dstCopy, transMat);
	}
	else if (dstCopy[0][1] != dstCopy[1][1] && dstCopy[1][1] == dstCopy[2][1])
	{
		if (dstCopy[1][0] > dstCopy[2][0])
		{
			std::swap(dstCopy[1], dstCopy[2]);
		}
		flatButtomTriTrans(dstCopy, transMat);
	}
	else
	{
		otherTriTrans(dstCopy, transMat);
	}
	unsigned char* imgData = this->srcImage.bits();
}

void ImageTransform::doTransform()
{
	switch (type)
	{
	case TRIANGLETRANS:
		{
			triImageTransform();
			break;
		}
	}
}

void ImageTransform::setTriangleTransPoint( std::vector<Wml::Vector2f>& s, std::vector<Wml::Vector2f>& d )
{
	//std::copy(s.begin(), s.end(), this->src.begin());
	//std::copy(d.begin(), d.end(), this->dst.begin());
	this->src = s;
	this->dst = d;
	int minX = INT_MAX,minY = INT_MAX,maxX = INT_MIN,maxY = INT_MIN;
	for (int i = 0; i < 3; i++)
	{
		if (minX > dst[i][0])
		{
			minX = dst[i][0];
		}
		if (minY > dst[i][1])
		{
			minY = dst[i][1];
		}
		if (maxX < dst[i][0])
		{
			maxX = dst[i][0];
		}
		if (maxY < dst[i][1])
		{
			maxY = dst[i][1];
		}
	}
	dstImage.offset[0] = minX;
	dstImage.offset[1] = minY;
	dstImage.img = new QImage(maxX - minX + 1, maxY - minY + 1, srcImage.format());
	std::cout << "src:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << src[i][0] << " " << src[i][1] << std::endl;
	}
	std::cout << "dst:" << std::endl;
	for (int i = 0; i < 3; i++)
	{
		std::cout << dst[i][0] << " " << dst[i][1] << std::endl; 
	}
}

bool ImageTransform::comparePoint( const Wml::Vector2f& a, const Wml::Vector2f& b )
{
	return a[1] > b[1];
}

void ImageTransform::flatTopTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{
	//dstSort[0]:v1 dstSort[1]:v2 dstSort[2]:v3
	float dy = dstSort[0][1] - dstSort[2][1];
	float dxdyl = (dstSort[0][0] - dstSort[2][0]) / dy;
	float dxdyr = (dstSort[1][0] - dstSort[2][0]) / dy;
	float x0,x1;
	x0 = x1 = (int)dstSort[2][0];
	for (int y = (int)dstSort[2][1]; y < dstSort[0][1]; y++)
	{
		drawLine((int)x0, (int)x1, y, transMat);
		dy = (y + 1) - dstSort[2][1];
		x0 = dstSort[2][0] + dy * dxdyl;
		x1 = dstSort[2][0] + dy * dxdyr;
	}
}

void ImageTransform::flatButtomTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{
	float dy = dstSort[0][1] - dstSort[1][1];
	float dxdyl = (dstSort[0][0] - dstSort[1][0]) / dy;
	float dxdyr = (dstSort[0][0] - dstSort[2][0]) / dy;
	float x0,x1;
	x0 = (int)dstSort[1][0];
	x1 = (int)dstSort[2][0];
	for (int y = (int)dstSort[2][1]; y < dstSort[0][1]; y++)
	{
		drawLine((int)x0, (int)x1, y, transMat);
		dy = (y+1) - dstSort[1][1];
		x0 = dstSort[1][0] + dy * dxdyl;
		x1 = dstSort[2][0] + dy * dxdyr;
	}
	
}

void ImageTransform::otherTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{
	float dxdy =   (dstSort[0][0] - dstSort[2][0]) / (dstSort[0][1] - dstSort[2][1]);
	float x = dstSort[0][0] + (dstSort[1][1] - dstSort[0][1]) * dxdy;
	std::vector<Wml::Vector2f> flatButtomPoint;
	std::vector<Wml::Vector2f> flatTopPoint;

	flatButtomPoint.push_back(dstSort[0]);
	if (x < dstSort[1][0])
	{
		Wml::Vector2f tmp(x, dstSort[1][1]);
		flatButtomPoint.push_back(tmp);
		flatButtomPoint.push_back(dstSort[1]);
			
		flatTopPoint.push_back(tmp);
		flatTopPoint.push_back(dstSort[1]);
		flatTopPoint.push_back(dstSort[2]);
	}
	else
	{
		Wml::Vector2f tmp(x, dstSort[1][1]);
		flatButtomPoint.push_back(dstSort[1]);
		flatButtomPoint.push_back(tmp);
	
		flatTopPoint.push_back(dstSort[1]);
		flatTopPoint.push_back(tmp);
		flatTopPoint.push_back(dstSort[2]);
	}
	
	flatButtomTriTrans(flatButtomPoint, transMat);
	flatTopTriTrans(flatTopPoint, transMat);
}

void ImageTransform::drawLine( int x0, int x1, int y, Wml::Matrix3f& transMat )
{
	int dstImgHeight = dstImage.img->height();
	int dstImgWidth = dstImage.img->width();	
	int numChannels;
	if (srcImage.format() == QImage::Format_RGB32)
	{
		numChannels = 4;
	}
	else
		numChannels = 3;
	for (int x = x0; x <= x1; x++)
	{
		Wml::Vector3f dstPoint(x, y, 1);
		Wml::Vector3f srcPoint = transMat.Inverse()*dstPoint;
		srcPoint[1] = srcImage.height() - srcPoint[1]; 
		unsigned char* dstImageData = dstImage.img->bits();
		int widthStep = dstImage.img->bytesPerLine();
		Wml::Vector3i v0((int)srcPoint[0], (int)srcPoint[1], 1); 
		Wml::Vector3i v1((int)srcPoint[0]+1, (int)srcPoint[1], 1);
		Wml::Vector3i v2((int)srcPoint[0], (int)srcPoint[1]+1, 1);
		Wml::Vector3i v3((int)srcPoint[0]+1, (int)srcPoint[1]+1, 1);
		for (int i = 0; i < numChannels; i++)
		{
			unsigned char outData;
			interPolation(v0, v1, v2, v3, srcPoint, numChannels, i, outData);
			int yy = dstImgHeight - 1 -((int)dstPoint[1]-dstImage.offset[1]);
			int xx = (int)dstPoint[0]-dstImage.offset[0];
			//std::cout << "yy" << yy << " " << dstImgHeight << std::endl;
			assert(yy<dstImgHeight);
			dstImageData[(yy)*widthStep+(xx)*numChannels+i] = outData;
		}
	}
}

void ImageTransform::interPolation( Wml::Vector3i v0, Wml::Vector3i v1, Wml::Vector3i v2, 
									Wml::Vector3i v3, Wml::Vector3f outPos, int numChannels, int channel, unsigned char& outData )
{
	unsigned char* imgData = srcImage.bits();
	int widthStep = srcImage.bytesPerLine();
	int v0Data = (int)getData(v0,numChannels, channel);
	int v1Data = (int)getData(v1,numChannels, channel);
	int v2Data = (int)getData(v2,numChannels, channel);
	int v3Data = (int)getData(v3,numChannels, channel);
	int tmp1 = (v1Data-v0Data) * (outPos[0]-v0[0]) + v0Data;
	int tmp2 = (v3Data-v2Data) * (outPos[0]-v2[0]) + v2Data;
	int result = (tmp2-tmp1) * (outPos[1]-v0[1]) + tmp1; 
	outData = (unsigned char)result;
}

unsigned char ImageTransform::getData( Wml::Vector3i pos,int Numchannel, int channel )
{
	unsigned char* imgData = srcImage.bits();
	int widthStep = srcImage.bytesPerLine();
	return imgData[pos[1]*widthStep+pos[0]*Numchannel+channel];
}

void ImageTransform::sortPoint( std::vector<Wml::Vector2f>& dstCopy )
{
	std::sort(dstCopy.begin(), dstCopy.end(), comparePoint);
	if (dstCopy[0][1] == dstCopy[1][1])
	{
		if (dstCopy[0][0] > dstCopy[1][0])
		{
			std::swap(dstCopy[0], dstCopy[1]);
		}
	}
	else if (dstCopy[1][1] == dstCopy[2][1])
	{
		if (dstCopy[1][0] > dstCopy[2][0])
		{
			std::swap(dstCopy[1], dstCopy[2]);
		}
	}
}

ImageTransform::~ImageTransform()
{

}

BoxPartImage& ImageTransform::getBoxPartImage()
{
	return dstImage;
}

void ImageTransform::testCopyToDstImg()
{
	int minX = INT_MAX,minY = INT_MAX,maxX = INT_MIN,maxY = INT_MIN;
	for (int i = 0; i < 3; i++)
	{
		if (minX > src[i][0])
		{
			minX = src[i][0];
		}
		if (minY > src[i][1])
		{
			minY = src[i][1];
		}
		if (maxX < src[i][0])
		{
			maxX = src[i][0];
		}
		if (maxY < src[i][1])
		{
			maxY = src[i][1];
		}
	}

	dstImage.offset[0] = minX;
	dstImage.offset[1] = minY;
	dstImage.img = new QImage(maxX - minX + 1, maxY - minY + 1, srcImage.format());
	unsigned char* srcData = srcImage.bits();
	std::cout << srcImage.width() << " " << srcImage.height() << std::endl;
	int srcWidthStep = srcImage.bytesPerLine();
	unsigned char* dstData = dstImage.img->bits();
	int dstWidthStep = dstImage.img->bytesPerLine();
	int channels;
	if (srcImage.format() == QImage::Format_RGB32)
	{
		channels = 4;
	}
	else
		channels = 3;
	for (int y = 0; y < dstImage.img->height(); y++)
	{
		for (int x = 0; x < dstImage.img->width(); x++)
		{
			for (int i = 0; i < channels; i++)
			{
				dstData[y*dstWidthStep+x*channels+i] = srcData[(dstImage.offset[1]+y)*srcWidthStep+(dstImage.offset[0]+x)*channels+i];
			}
		}
	}

}

void ImageTransform::showMatrix3( Wml::Matrix3f m )
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}




