#include "stdafx.h"
#include "ShareLib.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ShareLib w;
	w.show();
	return a.exec();
}
