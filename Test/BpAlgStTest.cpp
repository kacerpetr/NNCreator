#include "BpAlgStTest.h"
#include <QtTest/QtTest>
#include <QDebug>
#include "NeuralNetwork/Dataset.h"
#include "NeuralNetwork/BpNetSt.h"

namespace Test{

BpAlgStTest::BpAlgStTest(QObject *parent) : QObject(parent){}

void BpAlgStTest::test1(){
	BpAlgSt alg;

	alg.setStopError(0.001);
	QVERIFY(alg.getStopError() == 0.001);

	alg.setStopIteration(15000);
	QVERIFY(alg.getStopIteration() == 15000);

	alg.setStopTime(1956);
	QVERIFY(alg.getStopTime() == 1956);

	alg.setUpdateInterval(58);
	QVERIFY(alg.getUpdateInterval() == 58);

	alg.setUpdateInterval(58);
	QVERIFY(alg.getUpdateInterval() == 58);

	alg.setUpdateInterval(58);
	QVERIFY(alg.getUpdateInterval() == 58);

	Dataset set;
	alg.setDataset(&set);
	QVERIFY(alg.getDataset() == &set);

	BpNetSt net;
	alg.setNetwork(&net);
	QVERIFY(alg.getNetwork() == &net);

	QVERIFY(alg.isRunning() == false);
}

void BpAlgStTest::test2(){
	/* ------------------------- */
	/* testing data and networks */
	/* ------------------------- */

	//training dataset
	Dataset set;
	set.appendPattern();
	set[0].append(-1);
	set(0).append(1);

	//neural network
	BpNetSt net;
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
	BpNetSt net2(net);

	/* ------------------------------------------------------- */
	/* first back propagation iteration to get expected output */
	/* ------------------------------------------------------- */

	//learning coeficient
	double alpha = 1;

	//network output
	QList< QList<double> > out = net.getLayerOutput(set[0]);

	//output neuron delta calculation
	double dOutX1 = net[1][0][0]*out[1][0] + net[1][0][1]*out[1][1] + net[1][0].getBias();
	double dOut = (set(0)[0]-out[2][0]) * net[0][0].trFcnD(dOutX1);

	//first inner neuron delta
	double dInX1 = net[0][0][0]*out[0][0] + net[0][0].getBias();
	double dIn1 = (dOut*net[1][0][0]) * net[0][0].trFcnD(dInX1);

	//second inner neuron delta
	double dInX2 = net[0][1][0]*out[0][0] + net[0][1].getBias();
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
	set.appendPattern(4);
	//inputs
	set[0].append(0);
	set[0].append(0);
	set[1].append(0);
	set[1].append(1);
	set[2].append(1);
	set[2].append(0);
	set[3].append(1);
	set[3].append(1);
	//outputs
	set(0).append(0);
	set(1).append(1);
	set(2).append(1);
	set(3).append(0);

	//neural network
	BpNetSt net;
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
	QVERIFY(alg.getCurrentError() < 0.01);
	QVERIFY(net.getOutput(set[0])[0] < 0.3);
	QVERIFY(net.getOutput(set[1])[0] > 0.7);
	QVERIFY(net.getOutput(set[2])[0] > 0.7);
	QVERIFY(net.getOutput(set[3])[0] < 0.3);
}

}
