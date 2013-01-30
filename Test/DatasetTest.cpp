#include <QtTest/QtTest>
#include <QDebug>
#include "DatasetTest.h"

namespace Test{

DatasetTest::DatasetTest(QObject *parent) : QObject(parent){}

void DatasetTest::test1(){
	//empty dataset
	Dataset set;

	//single pattern deletion
	set.appendPattern();
	QVERIFY(set.patternCount() == 1);
	set.removePattern(0);
	QVERIFY(set.patternCount() == 0);

	//random pattern deletion
	set.appendPattern();
	set.appendPattern();
	set.appendPattern();
	QVERIFY(set.patternCount() == 3);
	set.removePattern(1);
	QVERIFY(set.patternCount() == 2);
}

void DatasetTest::test2(){
	//empty dataset
	Dataset set;

	//appends single input and output to first pattern
	set.appendPattern();
	set.appendInput(0, 6.13);
	set.appendOutput(0, 7.18);

	//appends single input and output to second pattern
	set.appendPattern();
	set.appendInputs(1, 4, 1.11);
	set.appendOutputs(1, 4, 2.12);

	//checks dataset lengths
	QVERIFY(set.patternCount() == 2);
	QVERIFY(set.inputCount(0) == 1);
	QVERIFY(set.outputCount(0) == 1);
	QVERIFY(set.inputCount(1) == 4);
	QVERIFY(set.outputCount(1) == 4);

	//checks dataset values
	QVERIFY(set.getInput(0,0) == 6.13);
	QVERIFY(set.getOutput(0,0) == 7.18);
	QVERIFY(set.getInput(1,2) == 1.11);
	QVERIFY(set.getOutput(1,2) == 2.12);

	//clears patterns in dataset
	set.clearPattern(0);
	set.clearInputs(1);
	set.clearOutputs(1);

	//checks dataset lengths
	QVERIFY(set.patternCount() == 2);
	QVERIFY(set.inputCount(0) == 0);
	QVERIFY(set.outputCount(0) == 0);
	QVERIFY(set.inputCount(1) == 0);
	QVERIFY(set.outputCount(1) == 0);
}

void DatasetTest::test3(){
	//empty dataset
	Dataset set;

	//original input
	QList<double> in1;
	in1.append(1.22);
	in1.append(7.62);
	in1.append(3.29);

	//input after dataset changes
	QList<double> in2;
	in2.append(1.22);
	in2.append(4.62);
	in2.append(3.29);

	//original output
	QList<double> out1;
	out1.append(0.22);
	out1.append(4.62);
	out1.append(8.29);

	//output after dataset changes
	QList<double> out2;
	out2.append(0.22);
	out2.append(4.62);
	out2.append(1.29);

	//sets pattern vectors to first pattern
	set.appendPattern();
	set.setInputVector(0, in1);
	set.setOutputVector(0, out1);

	//changes values in dataset
	set.setInput(0, 1, 4.62);
	set.setOutput(0, 2, 1.29);

	//checks vectors stored in dataset
	QCOMPARE(in2, set.getInputVector(0));
	QCOMPARE(out2, set.getOutputVector(0));
}

void DatasetTest::test4(){
	//empty datasets
	Dataset set1;

	//input vector 1
	QList<double> in1;
	in1.append(1.22);
	in1.append(7.62);
	in1.append(3.29);

	//input vector 2
	QList<double> in2;
	in2.append(1.22);
	in2.append(4.62);
	in2.append(3.29);

	//output vector 1
	QList<double> out1;
	out1.append(1.22);
	out1.append(0.62);
	out1.append(2.29);

	//output vector 2
	QList<double> out2;
	out2.append(4.22);
	out2.append(4.44);
	out2.append(14.4);

	//fills dataset
	set1.appendPattern();
	set1.appendPattern();
	set1.setInputVector(0, in1);
	set1.setInputVector(1, in2);
	set1.setOutputVector(0, out1);
	set1.setOutputVector(1, out2);

	//prints dataset to console
	qDebug() << set1.toString();

	//creates copy of dataset
	Dataset set2(set1);

	//compares string representations of dataset and its copy
	QCOMPARE(set1.toString(), set2.toString());
}

}
