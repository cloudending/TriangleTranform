#include "glviewer.h"

GLViewer::GLViewer(QWidget *parent)
	: QGLWidget(parent)
{
	
}

GLViewer::~GLViewer()
{

}

void GLViewer::initializeGL()
{

}

void GLViewer::paintGL()
{

}

void GLViewer::resizeGL( int w, int h )
{

}

GLViewer* GLViewer::getInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new GLViewer();
	}
	return m_Instance;
}
