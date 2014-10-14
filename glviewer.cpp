#include "gl/glew.h"
#include "glviewer.h"

GLViewer* GLViewer::m_Instance = NULL;
GLViewer::GLViewer(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}

GLViewer::~GLViewer()
{

}

void GLViewer::initializeGL()
{
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glEnable(GL_CULL_FACE); //弃用剔除效果
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK); //禁用多边形背面的光照计算。
	glFrontFace(GL_CCW);
	glShadeModel(GL_SMOOTH);	
}

void GLViewer::paintGL()
{

}

void GLViewer::resizeGL( int w, int h )
{
	if (h == 0)
	{
		h = 1;
	}
	//if(w >= h)
	//	glOrtho(0  * ((GLfloat) w / (GLfloat) h)  , 60 * 3  * ((GLfloat) w / (GLfloat) h) , -30 * 3  , 10 * 3 , -2000 , 2000);
	//else
	//	glOrtho(0 * 3 , 60 * 3, -30 * 3 * ((GLfloat) h / (GLfloat) w), 10 * 3 * ((GLfloat) h / (GLfloat) w), -2000 , 2000);
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1, 200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

GLViewer* GLViewer::getInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new GLViewer();
	}
	return m_Instance;
}
