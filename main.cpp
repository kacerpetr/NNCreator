#include <QApplication>
#include "Application/MainWindow.h"
#include "NeuronNetwork/Test.h"

#define TEST

int main(int argc, char *argv[]){
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
