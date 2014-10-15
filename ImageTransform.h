#pragma once
#include "WmlMathLib.h"
#include <vector>
#include <QString>
#include <QImage>
enum TRANSFORMTYPE
{
	TRIANGLETRANS,
	QUADTRANS
};
typedef struct boundingBox
{
	Wml::Vector2f offset;
	float height;
	float width;
}BoundingBox;
class ImageTransform
{
public:
	ImageTransform();
	ImageTransform(QString filePath);
	~ImageTransform();
	void setType(TRANSFORMTYPE t);
	void setTriangleTransPoint(std::vector<Wml::Vector2f>& s, std::vector<Wml::Vector2f>& d);
	void doTransform();
private:
	TRANSFORMTYPE type;
	static bool comparePoint(const Wml::Vector2f& a, const Wml::Vector2f& b);
	std::vector<Wml::Vector2f> src;
	std::vector<Wml::Vector2f> dst;
	QImage srcImage;
	void triImageTransform();
	void flatTopTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
	void flatButtomTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
	void otherTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
};

