#include <QApplication>
#include <QTest>
#include "Application/MainWindow.h"
#include "Test/NeuronTest.h"
#include "Test/BpNetStTest.h"
#include "Test/BpAlgStTest.h"
#include "Test/DatasetTest.h"

void runTests(){
	printf("\n");
	Test::DatasetTest test1;
	QTest::qExec(&test1);

	printf("\n");
	Test::NeuronTest test2;
	QTest::qExec(&test2);

	printf("\n");
	Test::BpNetStTest test3;
	QTest::qExec(&test3);

	printf("\n");
	Test::BpAlgStTest test4;
	QTest::qExec(&test4);
}

int main(int argc, char *argv[]){
	//runs tests when -t parameter given
	if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 't'){
		runTests();
		return 0;
	}else if(argc >= 2){
		printf("Invalid arguments given.");
		return 0;
	}

	//runs application
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	w.showMaximized();
	return a.exec();
}

