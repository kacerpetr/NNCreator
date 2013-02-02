#include "BpNetStTest.h"
#include <QtTest/QtTest>
#include <QDebug>

namespace Test{

BpNetStTest::BpNetStTest(QObject *parent) : QObject(parent){}

void BpNetStTest::test1(){
	BpNetSt net;

	net.setInputCount(5);
	QVERIFY(net.getInputCount() == 5);
	QVERIFY(net.getLayerCount() == 1);
	QVERIFY(net[0][0].weightCount() == 5);

	net.appendLayer();
	QVERIFY(net.getLayerCount() == 2);
	QVERIFY(net[1][0].weightCount() == 1);

	net.appendNeuron(0);
	QVERIFY(net.getNeuronCount(0) == 2);
	QVERIFY(net[0][1].weightCount() == 5);

	net.insertLayer(1);
	QVERIFY(net.getLayerCount() == 3);
	QVERIFY(net[1][0].weightCount() == 2);

	net.appendNeuron(1, 3);
	QVERIFY(net.getNeuronCount(1) == 4);
	QVERIFY(net[2][0].weightCount() == 4);

	net[1][1][0] = -0.25;
	QVERIFY(net[1][1][0] == -0.25);

	net.removeNeuron(1,1);
	QVERIFY(net.getNeuronCount(1) == 3);
	QVERIFY(net[2][0].weightCount() == 3);

	net.removeLayer(1);
	QVERIFY(net.getLayerCount() == 2);
	QVERIFY(net[1][0].weightCount() == 2);

	net.setInputCount(3);
	QVERIFY(net[0][0].weightCount() == 3);

	net.removeLayer(0);
	QVERIFY(net.getLayerCount() == 1);
	QVERIFY(net.getNeuronCount(0) == 1);
	QVERIFY(net[0][0].weightCount() == 3);
}

void BpNetStTest::test2(){
	BpNetSt net;

	net.setInputCount(3);
	net.duplicateLayer(-1);
	net.duplicateLayer(0);
	QVERIFY(net.getLayerCount() == 3);
	QVERIFY(net.getNeuronCount(0) == 3);
	QVERIFY(net[0][1].weightCount() == 3);
	QVERIFY(net.getNeuronCount(1) == 3);
	QVERIFY(net[1][1].weightCount() == 3);
	QVERIFY(net.getNeuronCount(2) == 1);
	QVERIFY(net[2][0].weightCount() == 3);

	net.duplicateLayer(2);
	QVERIFY(net.getLayerCount() == 4);
	QVERIFY(net.getNeuronCount(2) == 1);
	QVERIFY(net[2][0].weightCount() == 3);
	QVERIFY(net.getNeuronCount(3) == 1);
	QVERIFY(net[3][0].weightCount() == 1);

	net.insertNeuron(2, 0);
	net.insertNeuron(2, net.getNeuronCount(2)-1);
	net.insertNeuron(2, 1);
	QVERIFY(net.getNeuronCount(2) == 4);
	QVERIFY(net[2][1].weightCount() == 3);
	QVERIFY(net[3][0].weightCount() == 4);

	net.removeLastNeuron(2);
	net.removeLastNeuron(2);
	net.removeLastNeuron(2);
	QVERIFY(net.getNeuronCount(2) == 1);
	QVERIFY(net[2][0].weightCount() == 3);
	QVERIFY(net[3][0].weightCount() == 1);
	QVERIFY(net.getWeightCount() == 22);
	QVERIFY(net.getNeuronCount() == 8);

	net.setBias(0.156);
	QVERIFY(net[0][2].getBias() == 0.156);
	QVERIFY(net[1][1].getBias() == 0.156);
	QVERIFY(net[2][0].getBias() == 0.156);
	QVERIFY(net[3][0].getBias() == 0.156);

	BpNetSt netCopy(net);
	QCOMPARE(net.toString(), netCopy.toString());
}

void BpNetStTest::test3(){
	//creates network and initiates weights
	BpNetSt net;
	net.setInputCount(2);
	net.appendLayer();
	net.appendNeuron(0,2);
	net.appendNeuron(1,1);
	net.setTransferFunction(BinarySigmoid);
	net.randomizeWeight(15154564, -0.5, 0.5);
	net.randomizeBias(51545, -0.2, 0.2);

	//prints network to console
	//qDebug() << net.toString();

	//input values
	QList<double> input;
	input.append(0.895);
	input.append(-0.45);

	//first inner layer output
	QList<double> out1;
	out1.append(net[0][0].getOutput(input));
	out1.append(net[0][1].getOutput(input));
	out1.append(net[0][2].getOutput(input));

	//output layer output
	QList<double> out2;
	out2.append(net[1][0].getOutput(out1));
	out2.append(net[1][1].getOutput(out1));

	//test of getOutput()
	QList<double> netOut = net.getOutput(input);
	QCOMPARE(netOut, out2);

	//test of getLayerOutput()
	QList< QList<double> > allOut = net.getLayerOutput(input);
	QCOMPARE(allOut[0], input);
	QCOMPARE(allOut[1], out1);
	QCOMPARE(allOut[2], out2);
}

void BpNetStTest::test4(){
	BpNetSt net;

	net.setInputCount(3);
	net.appendNeuron(0, 3);
	QVERIFY(net.getLayerCount() == 1);
	QVERIFY(net.getNeuronCount(0) == 4);
	QVERIFY(net[0][1].weightCount() == 3);

	net.insertLayer(0);
	QVERIFY(net.getLayerCount() == 2);
	QVERIFY(net.getNeuronCount(0) == 1);
	QVERIFY(net[0][0].weightCount() == 3);
	QVERIFY(net.getNeuronCount(1) == 4);
	QVERIFY(net[1][1].weightCount() == 1);

	net.appendNeuron(0, 5);
	QVERIFY(net.getLayerCount() == 2);
	QVERIFY(net.getNeuronCount(0) == 6);
	QVERIFY(net[0][1].weightCount() == 3);
	QVERIFY(net.getNeuronCount(1) == 4);
	QVERIFY(net[1][1].weightCount() == 6);

	net.insertLayer(1);
	QVERIFY(net.getLayerCount() == 3);
	QVERIFY(net.getNeuronCount(1) == 1);
	QVERIFY(net[1][0].weightCount() == 6);
	QVERIFY(net.getNeuronCount(2) == 4);
	QVERIFY(net[2][3].weightCount() == 1);

	net.appendNeuron(1, 2);
	QVERIFY(net.getLayerCount() == 3);
	QVERIFY(net.getNeuronCount(1) == 3);
	QVERIFY(net[1][1].weightCount() == 6);
	QVERIFY(net.getNeuronCount(2) == 4);
	QVERIFY(net[2][2].weightCount() == 3);

	net.removeLayer(1);
	QVERIFY(net.getLayerCount() == 2);
	QVERIFY(net.getNeuronCount(1) == 4);
	QVERIFY(net[1][1].weightCount() == 6);

	net.removeLayer(0);
	QVERIFY(net.getLayerCount() == 1);
	QVERIFY(net.getNeuronCount(0) == 4);
	QVERIFY(net[0][1].weightCount() == 3);
}

}
