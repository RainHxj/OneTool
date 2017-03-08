#include "onetool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OneTool w;
	w.show();
	return a.exec();
}
