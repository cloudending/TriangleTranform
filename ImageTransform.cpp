#include "ImageTransform.h"
#include <algorithm>

ImageTransform::ImageTransform( QString filePath )
{
	this->srcImage.load(filePath);
}

void ImageTransform::setType(TRANSFORMTYPE t)
{
	this->type = t;
}

void ImageTransform::triImageTransform()
{
	Wml::Matrix3f homoCoordSrc(this->src[0][0], this->src[1][0], this->src[2][0],
							   this->src[0][1], this->src[1][1], this->src[2][1],
							   this->src[0][2], this->src[1][2], this->src[2][2]);
	
	Wml::Matrix3f homoCoordDst(this->dst[0][0], this->dst[1][0], this->dst[2][0],
							   this->dst[0][1], this->dst[1][1], this->dst[2][1],
							   this->dst[0][2], this->dst[1][2], this->dst[2][2]);
	
	Wml::Matrix3f transMat = homoCoordDst*homoCoordSrc.Inverse();
	
	std::vector<Wml::Vector2f> dstCopy = dst;
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
	else
	{

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
	
}

bool ImageTransform::comparePoint( const Wml::Vector2f& a, const Wml::Vector2f& b )
{
	return a[1] > b[1];
}

void ImageTransform::flatTopTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{
	float dy = dstSort[0][1] - dstSort[2][1];
	float dxdyl = (dstSort[0][0] - dstSort[2][0]) / dy;
	float dxdyr = (dstSort[1][0] - dstSort[2][0]) / dy;

	float x0, x1;
	for (int y = (int)dstSort[2][1]; y < dstSort[0][1]; y++)
	{
		
	}
}

void ImageTransform::flatButtomTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{

}

void ImageTransform::otherTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat)
{

}




