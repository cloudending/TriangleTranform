#include "triangletransform.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TriangleTransform w;
	w.show();
	return a.exec();
}
