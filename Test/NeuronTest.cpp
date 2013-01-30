#include <QtTest/QtTest>
#include <QDebug>
#include "NeuronTest.h"

namespace Test{

NeuronTest::NeuronTest(QObject *parent) : QObject(parent){}

void NeuronTest::test1(){
	//newly created neuron
	Neuron n;

	//checks initial values
	QVERIFY(n.weightCount() == 0);
	QVERIFY(n.getSlope() == 1);
	QVERIFY(n.getBias() == 0);
	QVERIFY(n.getTrFcn() == UnarySigmoid);

	//changes initial values, adds weight
	n.setTrFcn(BinarySigmoid);
	n.setBias(1.55);
	n.setSlope(2.23);
	n.appendWeight(0.215);

	//checks changed values
	QVERIFY(n.weightCount() == 1);
	QVERIFY(n.getWeight(0) == 0.215);
	QVERIFY(n.getSlope() == 2.23);
	QVERIFY(n.getBias() == 1.55);
	QVERIFY(n.getTrFcn() == BinarySigmoid);
}

void NeuronTest::test2(){
	//newly created neuron
	Neuron n;

	//inserts some weights
	n.insertWeight(0, 10);
	n.insertWeight(0, 15);
	n.appendWeight(22);
	n.setWeight(2, 26);

	//checks weights
	QVERIFY(n.weightCount() == 3);
	QVERIFY(n[0] == 15);
	QVERIFY(n[1] == 10);
	QVERIFY(n[2] == 26);

	//removes second weight
	n.removeWeight(1);

	//rechecks remaining weights
	QVERIFY(n.weightCount() == 2);
	QVERIFY(n[0] == 15);
	QVERIFY(n[1] == 26);
}

void NeuronTest::test3(){
	//newly created neuron
	Neuron n1;

	//changes initial values, adds weight
	n1.setTrFcn(BinarySigmoid);
	n1.setBias(1.55);
	n1.setSlope(2.23);
	n1.appendWeight(0.215);
	n1.appendWeight(1.54);

	//checks changed values
	QVERIFY(n1.weightCount() == 2);
	QVERIFY(n1.getWeight(0) == 0.215);
	QVERIFY(n1.getWeight(1) == 1.54);
	QVERIFY(n1.getSlope() == 2.23);
	QVERIFY(n1.getBias() == 1.55);
	QVERIFY(n1.getTrFcn() == BinarySigmoid);

	//creates copy of neuron
	Neuron n2(n1);

	//checks copy of neuron
	QVERIFY(n2.weightCount() == 2);
	QVERIFY(n2.getWeight(0) == 0.215);
	QVERIFY(n2.getWeight(1) == 1.54);
	QVERIFY(n2.getSlope() == 2.23);
	QVERIFY(n2.getBias() == 1.55);
	QVERIFY(n2.getTrFcn() == BinarySigmoid);
}

void NeuronTest::test4(){
	//neuron weight values
	QList<double> weights;
	weights.append(0.856);
	weights.append(-0.22);
	weights.append(-0.569);

	//newly created neuron
	Neuron n;
	n.setWeights(weights);
	n.setBias(0.1);
	n.setSlope(0.9);

	//checks neuron weights
	QCOMPARE(weights, n.getWeights());

	//test input values
	QList<double> inputs;
	inputs.append(0.564);
	inputs.append(-0.235);
	inputs.append(0.895);

	//calculates expected output
	double wsum = 0.856*0.564 + 0.22*0.235 - 0.569*0.895 + 0.1;
	double out = 1 / (1 + exp(-wsum*0.9));

	//compares expected and actual output
	QCOMPARE(out, n.getOutput(inputs));

	//prints neuron to console
	qDebug() << n.toString();
}

void NeuronTest::test5(){
	//creates and fills neuron
	Neuron n;
	n.appendWeight(0.25);
	n.setBias(0.1);
	n.setSlope(0.6);

	//calculates expected output
	double out = 1 / (1 + exp(-(0.25*5+0.1)*0.6));

	//compares expected and actual output
	QCOMPARE(out, n.getOutput(5));
}

}
