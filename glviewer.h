#ifndef GLVIEWER_H
#define GLVIEWER_H

#include <QGLWidget>
#include <iostream>
class GLViewer : public QGLWidget
{
	Q_OBJECT

public:
	//GLViewer(QWidget *parent);
	~GLViewer();
	static GLViewer* getInstance();
private:

	static GLViewer* m_Instance;
	GLViewer(QWidget *parent = 0);

	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (GLViewer::m_Instance)
			{
				delete GLViewer::m_Instance;
			}
		}
	};
	static CGarbo garbo;
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
};

#endif // GLVIEWER_H
