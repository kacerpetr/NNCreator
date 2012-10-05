#include "NeuronTest.h"
#include <QtTest/QtTest>
#include <QDebug>
#include "NeuralNetwork/Neuron.h"
#include "Util/Exception.h"
#include "Util/function.h"

namespace NeuralNetwork{

void NeuronTest::stringConstructorTest(){
	std::string str = "1.556, [515.55, 5465.21, 111.22]";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "0, []";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "[515.55]";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "15.52,55.4,6.6";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "15.52";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}

	str = "dfgd,[fgf,dgf]";
	try{
		Neuron n(str);
		qDebug() << n.toString().c_str();
	}catch(Util::Exception& ex){
		qDebug() << ex.toString().c_str();
	}
}

void NeuronTest::outputCalculationTest(){
	std::vector<double> input;
	input.push_back(1.12);
	input.push_back(0.2);
	input.push_back(-0.33);
	input.push_back(-0.88);

	std::vector<double> weight;
	weight.push_back(1.25);
	weight.push_back(-1.25);
	weight.push_back(2.25);
	weight.push_back(-0.58);

	Neuron n;
	n.setBias(0.5);
	n.setWeight(weight);

	QCOMPARE(Util::round(n(input), 6), 0.610018);
}

}
