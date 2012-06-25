#include <QApplication>
#include "Application/MainWindow.h"
#include "NeuronNetwork/Test.h"

#define TEST

int main(){
	#ifndef TEST
	QApplication a(argc, argv);
	MainWindow w;
	w.showMaximized();
	return a.exec();
	#else
	NeuronNetwork::Test test1;
	QTest::qExec(&test1);
	#endif
}
