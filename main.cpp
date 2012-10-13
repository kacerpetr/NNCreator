#include <QApplication>
#include "Application/MainWindow.h"

#include "Test/NeuronTest.h"
#include "Test/BasicNetworkTest.h"
#include "Test/BackPropagationTest.h"
#include "Test/ProjectItemModelTest.h"


void runTests(){
	NeuralNetwork::NeuronTest test2;
	QTest::qExec(&test2);

	printf("\n");
	NeuralNetwork::BasicNetworkTest test3;
	QTest::qExec(&test3);

	printf("\n");
	NeuralNetwork::BackPropagationTest test4;
	QTest::qExec(&test4);

	printf("\n");
	Util::ProjectItemModelTest test5;
	QTest::qExec(&test5);
}


int main(int argc, char *argv[]){
	//run tests when -t parameter given
	if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 't'){
		runTests();
		return 0;
	}else if(argc >= 2){
		printf("Invalid arguments given.");
		return 0;
	}

	//run application
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}

