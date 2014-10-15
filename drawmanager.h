#pragma once
#include  "gl/glew.h"
#include <QGLWidget>
#include <QString>
class DrawManger
{
public:
	DrawManger();
	~DrawManger();
	void loadImage();
	void init();
private:
	GLuint* texName;
};