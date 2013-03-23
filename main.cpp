#include <QApplication>
#include <QTest>
#include "Application/MainWindow.h"
#include "Test/NeuronTest.h"
#include "Test/MlnNetStTest.h"
#include "Test/BpAlgStTest.h"
#include "Test/DatasetTest.h"
#include "Test/LrnEngineTest.h"
#include <QTranslator>
#include "Util/Settings.h"

void runTests(){
	printf("\n");
	Test::DatasetTest test1;
	QTest::qExec(&test1);

	printf("\n");
	Test::NeuronTest test2;
	QTest::qExec(&test2);

	printf("\n");
	Test::MlnNetStTest test3;
	QTest::qExec(&test3);

	printf("\n");
	Test::BpAlgStTest test4;
	QTest::qExec(&test4);

	printf("\n");
	Test::LrnEngineTest test5;
	QTest::qExec(&test5);
}

int main(int argc, char *argv[]){
	//runs tests when -t parameter given
	if(argc == 2 && strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 't'){
		QApplication a(argc, argv);
		runTests();
		return a.exec();
	}else if(argc >= 2){
		printf("Invalid arguments given.");
		return 0;
	}

	//runs application
	QApplication a(argc, argv);

    Util::Settings& sts = Util::Settings::get();

    QTranslator trr(&a);
    trr.load(sts.language(), "./Translation");
    a.installTranslator(&trr);

	Application::MainWindow w;
	w.show();
	w.showMaximized();
	return a.exec();
}

