#include <QApplication>
#include "Application/MainWindow.h"
#include "NeuralNetwork/Test.h"

int main(int argc, char *argv[]){
	//run tests when -t parameter given
	if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 't'){
		printf("Testing ...\n");
		NeuralNetwork::Test test1;
		QTest::qExec(&test1);
		return 0;
	}else if(argc >= 2){
		printf("Invalid arguments given.");
		return 0;
	}
	//run application
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	w.showMaximized();
	return a.exec();
}

