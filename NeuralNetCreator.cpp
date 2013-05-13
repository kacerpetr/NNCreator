/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QTest>
#include <QTranslator>
#include "Application/MainWindow.h"
#include "Test/NeuronTest.h"
#include "Test/MlnNetStTest.h"
#include "Test/BpAlgStTest.h"
#include "Test/DatasetTest.h"
#include "Test/LrnEngineTest.h"
#include "Util/Settings.h"

/**
 * Runs unit tests.
 */
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

/**
 * Main function.
 */
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

    Settings& sts = Settings::get();

    QTranslator trr(&a);
    trr.load(sts.language(), "./Translation");
    a.installTranslator(&trr);

	Application::MainWindow w;
	w.show();
	w.showMaximized();
	return a.exec();
}

