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
typedef struct boxPartImage
{
	Wml::Vector3i offset;

	QImage* img;
}BoxPartImage;

class ImageTransform
{
public:
	ImageTransform();
	ImageTransform(QString filePath);
	~ImageTransform();
	void setType(TRANSFORMTYPE t); //step 1
	void setTriangleTransPoint(std::vector<Wml::Vector2f>& s, std::vector<Wml::Vector2f>& d); //step 2
	void doTransform();
	void testCopyToDstImg();
	BoxPartImage& getBoxPartImage();
private:
	TRANSFORMTYPE type;
	static bool comparePoint(const Wml::Vector2f& a, const Wml::Vector2f& b);
	std::vector<Wml::Vector2f> src;
	std::vector<Wml::Vector2f> dst;
	QImage srcImage;

	BoxPartImage dstImage;
	void triImageTransform();
	void flatTopTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
	void flatButtomTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
	void otherTriTrans(std::vector<Wml::Vector2f>& dstSort, Wml::Matrix3f& transMat);
	void drawLine(int x0, int x1, int y, Wml::Matrix3f& transMat);
	void interPolation(Wml::Vector3i v0, Wml::Vector3i v1, Wml::Vector3i v2, 
		Wml::Vector3i v3, Wml::Vector3f outPos, int numChannels, int channel, unsigned char& outData);
	unsigned char getData(Wml::Vector3i pos, int Numchannel, int channel);
	void sortPoint(std::vector<Wml::Vector2f>& dstCopy);
	void showMatrix3(Wml::Matrix3f m);
};

