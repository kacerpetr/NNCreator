#include "BpAlgStTest.h"
#include <QtTest/QtTest>
#include <QDebug>
#include "NeuralNetwork/Dataset.h"
#include "NeuralNetwork/MlnNetSt.h"

namespace Test{

BpAlgStTest::BpAlgStTest(QObject *parent) : QObject(parent){}

void BpAlgStTest::test1(){
	BpAlgSt alg;

	alg.setStopError(0.001);
	QVERIFY(alg.stopError() == 0.001);

	alg.setStopIteration(15000);
	QVERIFY(alg.stopIteration() == 15000);

	alg.setStopTime(1956);
	QVERIFY(alg.stopTime() == 1956);

	alg.setUpdateInterval(58);
	QVERIFY(alg.updateInterval() == 58);

	Dataset set;
	alg.setDataset(&set);
	QVERIFY(alg.dataset() == &set);

	MlnNetSt net;
	alg.setNetwork(&net);
	QVERIFY(alg.network() == &net);

	QVERIFY(alg.isRunning() == false);
}

void BpAlgStTest::test2(){
	/* ------------------------- */
	/* testing data and networks */
	/* ------------------------- */

	//training dataset
	Dataset set;
	set.setMinSize(1,1,1);
	set.setInput(0,0,-1);
	set.setOutput(0,0,1);

	//neural network
	MlnNetSt net;
	net.setInputCount(1);
	net.appendLayer();
	net.appendNeuron(0);

	//first inner layer neuron
	net[0][0][0] = 0.55;
	net[0][0].setBias(0.25);

	//second inner layer neuron
	net[0][1][0] = -0.48;
	net[0][1].setBias(-0.3);

	//output layer neuron
	net[1][0][0] = 0.12;
	net[1][0][1] = -0.18;
	net[1][0].setBias(0.1);

	//copy of neural network
	MlnNetSt net2(net);

	/* ------------------------------------------------------- */
	/* first back propagation iteration to get expected output */
	/* ------------------------------------------------------- */

	//learning coeficient
	double alpha = 1;

	//network output
	QList< QList<double> > out = net.layerOutput(set.inputVector(0));

	//output neuron delta calculation
	double dOutX1 = net[1][0][0]*out[1][0] + net[1][0][1]*out[1][1] + net[1][0].bias();
	double dOut = (set.output(0,0)-out[2][0]) * net[0][0].trFcnD(dOutX1);

	//first inner neuron delta
	double dInX1 = net[0][0][0]*out[0][0] + net[0][0].bias();
	double dIn1 = (dOut*net[1][0][0]) * net[0][0].trFcnD(dInX1);

	//second inner neuron delta
	double dInX2 = net[0][1][0]*out[0][0] + net[0][1].bias();
	double dIn2 = (dOut*net[1][0][1]) * net[0][0].trFcnD(dInX2);

	//output neuron weight adaptation
	net[1][0][0] += alpha * dOut * out[1][0];
	net[1][0][1] += alpha * dOut * out[1][1];
	net[1][0].addBias(alpha * dOut);

	//first inner layer neuron
	net[0][0][0] += alpha * dIn1 * out[0][0];
	net[0][0].addBias(alpha * dIn1);

	//second inner layer neuron
	net[0][1][0] += alpha * dIn2 * out[0][0];
	net[0][1].addBias(alpha * dIn2);

	/* ------------------------------------------------------- */
	/* one back propagation iteration by implemented algorithm */
	/* ------------------------------------------------------- */

	BpAlgSt alg;
	alg.setDataset(&set);
	alg.setNetwork(&net2);
	alg.setAlpha(alpha);
	alg.setStopIteration(1);
	alg.start();

	/* -------------------------------------------------------- */
	/* compares neural networks after one iteration of learning */
	/* -------------------------------------------------------- */

	QCOMPARE(net.toString(), net2.toString());
}

void BpAlgStTest::test3(){
	//training dataset
	Dataset set;
	set.setMinSize(4,2,1);
	//inputs
	set.setInput(0, 0, 0);
	set.setInput(0, 1, 0);
	set.setInput(1, 0, 0);
	set.setInput(1, 1, 1);
	set.setInput(2, 0, 1);
	set.setInput(2, 1, 0);
	set.setInput(3, 0, 1);
	set.setInput(3, 1, 1);
	//outputs
	set.setOutput(0, 0, 0);
	set.setOutput(1, 0, 1);
	set.setOutput(2, 0, 1);
	set.setOutput(3, 0, 0);

	//neural network
	MlnNetSt net;
	net.setInputCount(2);
	net.appendLayer();
	//inner layer
	net.appendNeuron(0, 3);
	net[0][0][0] = 0.1970;
	net[0][0][1] = 0.3009;
	net[0][0].setBias(-0.3378);
	net[0][1][0] = 0.3191;
	net[0][1][1] = 0.1904;
	net[0][1].setBias(0.2771);
	net[0][2][0] = -0.1448;
	net[0][2][1] = -0.0347;
	net[0][2].setBias(0.2859);
	net[0][3][0] = 0.3594;
	net[0][3][1] = -0.4861;
	net[0][3].setBias(-0.3329);
	//output layer
	net[1][0][0] = 0.4919;
	net[1][0][1] = -0.2913;
	net[1][0][2] = -0.3979;
	net[1][0][3] = 0.3581;
	net[1][0].setBias(-0.1401);

	//learning
	BpAlgSt alg;
	alg.setDataset(&set);
	alg.setNetwork(&net);
	alg.setAlpha(0.2);
	alg.setStopError(0.01);
	alg.setStopTime(2500);
	alg.setStopIteration(50000);
	alg.start();

	//checks network
	QVERIFY(alg.currentError() < 0.01);
	QVERIFY(net.output(set.inputVector(0))[0] < 0.3);
	QVERIFY(net.output(set.inputVector(1))[0] > 0.7);
	QVERIFY(net.output(set.inputVector(2))[0] > 0.7);
	QVERIFY(net.output(set.inputVector(3))[0] < 0.3);
}

}
