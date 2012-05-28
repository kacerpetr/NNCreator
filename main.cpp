#include <QApplication>
#include "Application/MainWindow.h"

#define TEST

int main(int argc, char *argv[]){
	#ifndef TEST
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
	#else
	// run some tests
	#endif
}
