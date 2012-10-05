#include <QApplication>
#include "Application/MainWindow.h"
#include "Test/NeuronTest.h"
#include "Test/BasicNetworkTest.h"

int main(int argc, char *argv[]){
	//run tests when -t parameter given
	if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 't'){
		NeuralNetwork::NeuronTest test2;
		QTest::qExec(&test2);
		printf("\n");
		NeuralNetwork::BasicNetworkTest test3;
		QTest::qExec(&test3);
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

