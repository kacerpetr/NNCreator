#include "BasicNetworkTest.h"
#include "NeuralNetwork/BasicNetwork.h"
#include <QtTest/QtTest>
#include <QDebug>

namespace NeuralNetwork{

void BasicNetworkTest::stringConstructorTest(){
	/*std::string str(
		"Layer:\n"
		"0.56, [154.545]\n"
		"1.11, [0.5]\n"
		"Layer:\n"
		"0.12, [0.5, 0.5]\n"
		"7.22, [0.5, 0.5]\n"
		"0, [0.5, 0.5]\n"
		"5.66, [0.5, 44.5]\n"
		"Layer:\n"
		"0.123, [0.5, 1.5, 0.5, 0.5, 0.5]\n"
		"0, [0.5, 0.5, 1.5, 0.5, 0.5]\n"
		"0.5, [4.554, 0.5, 0.5, 1.5, 0.5]\n"
		"Layer:\n"
		"1, [0.8, 0.5, 5.5]\n"
		"4, [0.5, 1.5, 10.555]\n"
	);

	BasicNetwork net(str);
	QCOMPARE(net.toString().c_str(), str.c_str());*/
}

void BasicNetworkTest::insertLayerTest(){
	/*BasicNetwork net;

	QCOMPARE(net.toString().c_str(), "");

	net.insertLayer(0);
	QCOMPARE(net.toString().c_str(), "Layer:\n");

	net.insertLayer(0);
	QCOMPARE(net.toString().c_str(), "Layer:\nLayer:\n");

	net.insertLayer(1);
	QCOMPARE(net.toString().c_str(), "Layer:\nLayer:\nLayer:\n");

	net.insertLayer(3);
	QCOMPARE(net.toString().c_str(), "Layer:\nLayer:\nLayer:\nLayer:\n");*/
}

void BasicNetworkTest::appendNeuronTest(){
	/*BasicNetwork net;

	net.insertLayer(0);
	net.appendNeuron(0);
	net.appendNeuron(0);

	net.insertLayer(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);

	net.insertLayer(2);
	net.appendNeuron(2);
	net.appendNeuron(2);

	net.insertLayer(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);

	std::string res(
		"Layer:\n"
		"0, [0.5]\n"
		"0, [0.5]\n"
		"Layer:\n"
		"0, [0.5, 0.5]\n"
		"0, [0.5, 0.5]\n"
		"0, [0.5, 0.5]\n"
		"0, [0.5, 0.5]\n"
		"Layer:\n"
		"0, [0.5, 0.5, 0.5, 0.5, 0.5]\n"
		"0, [0.5, 0.5, 0.5, 0.5, 0.5]\n"
		"0, [0.5, 0.5, 0.5, 0.5, 0.5]\n"
		"Layer:\n"
		"0, [0.5, 0.5, 0.5]\n"
		"0, [0.5, 0.5, 0.5]\n"
	);

	QCOMPARE(net.toString().c_str(), res.c_str());

	net.randomizeWeights(1, -0.5, 0.5, -0.5, 0.5);
	qDebug() << net.toString().c_str();*/
}

void BasicNetworkTest::noLayerOutputTest(){

}

void BasicNetworkTest::oneLayerOutputTest(){
	/*BasicNetwork net;

	net.appendLayer();
	net.appendNeuron(0);
	net.appendNeuron(0);
	net.appendNeuron(0);

	std::vector<double> input;
	input.push_back(0.6);
	input.push_back(0.2);
	input.push_back(0.8);

	std::vector<double> output = net(input);
	qDebug() << output[0] << " " << output[1] << " " << output[2];*/
}

void BasicNetworkTest::twoLayersOutputTest(){

}

void BasicNetworkTest::threeLayersOutputTest(){

}

}
