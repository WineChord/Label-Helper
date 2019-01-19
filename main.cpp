#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

#include <QDebug>
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGuiApplication1 w;
	w.setWindowTitle("Label Helper");
	w.show();
	qDebug() << "Hello!";
	return a.exec();
}
