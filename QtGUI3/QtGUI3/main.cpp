#include "qtgui3.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGUI3 w;
	w.setWindowTitle("BSpline Demo by Zhou Jiehui");
	w.show();
	return a.exec();
}
