#include "BackPropagationTest.h"
#include "NeuralNetwork/Dataset.h"
#include "NeuralNetwork/BasicNetwork.h"
#include "NeuralNetwork/BackPropagation.h"
#include <QDebug>
#include <cmath>
#include <QFile>
#include <QTextStream>

namespace NeuralNetwork{

void BackPropagationTest::xorTest(){
	/*Dataset pt;
	pt.appendPattern();
	pt.appendPattern();
	pt.appendPattern();
	pt.appendPattern();
	pt.appendInput(0, 0);
	pt.appendInput(0, 0);
	pt.appendOutput(0, 0);
	pt.appendInput(1, 0);
	pt.appendInput(1, 1);
	pt.appendOutput(1, 1);
	pt.appendInput(2, 1);
	pt.appendInput(2, 1);
	pt.appendOutput(2, 0);
	pt.appendInput(3, 1);
	pt.appendInput(3, 0);
	pt.appendOutput(3, 1);

	BasicNetwork net;
	net.insertLayer(0);
	net.appendNeuron(0);
	net.appendNeuron(0);
	net.insertLayer(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.insertLayer(2);
	net.appendNeuron(2);

	net.setBias(-0.3378, 1, 0);
	net.setWeight(0.1970, 1, 0, 0);
	net.setWeight(0.3009, 1, 0, 1);

	net.setBias(0.2771, 1, 1);
	net.setWeight(0.3191, 1, 1, 0);
	net.setWeight(0.1904, 1, 1, 1);

	net.setBias(0.2859, 1, 2);
	net.setWeight(-0.1448, 1, 2, 0);
	net.setWeight(-0.0347, 1, 2, 1);

	net.setBias(-0.3329, 1, 3);
	net.setWeight(0.3594, 1, 3, 0);
	net.setWeight(-0.4861, 1, 3, 1);

	net.setBias(-0.1401, 2, 0);
	net.setWeight(0.4919, 2, 0, 0);
	net.setWeight(-0.2913, 2, 0, 1);
	net.setWeight(-0.3979, 2, 0, 2);
	net.setWeight(0.3581, 2, 0, 3);

	qDebug() << net.toString().c_str();

	BackPropagation bp(&net, &pt);
	bp.alpha = 1;
	QString lrn = "";

	for(int x = 0; x < 4300; x++){
		double err = 0.0;
		for(unsigned int i = 0; i < pt.patternCount(); i++){
			err += bp.iterate(i);
		}
		if(x % 50 == 0) qDebug() << "iteration " << x << ": " << err;
		lrn += QString::number(err, 'f', 6).replace(".", ",") + "; " + QString::number(x) + "\n";
		if(err < 0.001) break;
	}

	QFile file1("lrn.csv");
	file1.open(QIODevice::WriteOnly);
	QTextStream ostr2(&file1);
	ostr2 << lrn;
	file1.close();

	std::vector<double> in1;
	in1.push_back(0.0);
	in1.push_back(0.0);

	std::vector<double> in2;
	in2.push_back(0.0);
	in2.push_back(1.0);

	std::vector<double> in3;
	in3.push_back(1.0);
	in3.push_back(0.0);

	std::vector<double> in4;
	in4.push_back(1.0);
	in4.push_back(1.0);

	qDebug() << net(in1)[0] << " " << net(in2)[0] << " " << net(in3)[0] << " " << net(in4)[0];

	QString str = "";

	for(int y = 0; y <= 511; y++){
		for(int x = 0; x <= 511; x++){
			std::vector<double> in;
			in.push_back(x/511.0);
			in.push_back(y/511.0);
			str += QString::number(net(in)[0], 'f', 6);
			if(x < 511) str += "; ";
		}
		str += "\n";
	}

	QFile file("out.csv");
	file.open(QIODevice::WriteOnly);
	QTextStream ostr(&file);
	ostr << str;
	file.close();*/
}

/*void BackPropagationTest::test(){
	//training data
	TrainingPattern pt;

	pt.appendPattern();
	pt.appendInput(0, -1);
	pt.appendInput(0, -1);
	pt.appendOutput(0, -1);

	pt.appendPattern();
	pt.appendInput(1, -1);
	pt.appendInput(1, 1);
	pt.appendOutput(1, 1);

	pt.appendPattern();
	pt.appendInput(2, 1);
	pt.appendInput(2, -1);
	pt.appendOutput(2, 1);

	pt.appendPattern();
	pt.appendInput(3, 1);
	pt.appendInput(3, 1);
	pt.appendOutput(3, 1);

	//network
	BasicNetwork net;

	net.insertLayer(0);
	net.appendNeuron(0);
	net.appendNeuron(0);

	net.insertLayer(1);
	for(int i = 1; i < 40; i++)net.appendNeuron(1);

	net.insertLayer(2);
	net.appendNeuron(2);

	net.randomizeWeights(1, -0.5, 0.5, -0.5, 0.5);

	//learning
	BackPropagation bp(&net, &pt);
	for(int x = 0; x < 5001; x++){
		double err = 0.0;
		for(unsigned int i = 0; i < pt.patternCount(); i++){
			err += bp.iterate(i);
		}
		if(x%1000 == 0) qDebug() << "iteration " << x << ": " << err;
	}

	std::vector<double> i1;
	i1.push_back(-1);
	i1.push_back(-1);

	std::vector<double> i2;
	i2.push_back(1);
	i2.push_back(1);

	qDebug() << (net(i1))[0] << " " << (net(i2))[0];
}

void BackPropagationTest::test2(){
	TrainingPattern pt;
	BasicNetwork net;

	//creates training pattern
	pt.appendPattern();
	pt.appendInput(0, 0.1);
	pt.appendOutput(0, 0.1);

	pt.appendPattern();
	pt.appendInput(1, 0.9);
	pt.appendOutput(1, 0.1);

	pt.appendPattern();
	pt.appendInput(2, 0.5);
	pt.appendOutput(2, 0.9);

	pt.appendPattern();
	pt.appendInput(3, 0.2);
	pt.appendOutput(3, 0.3);

	pt.appendPattern();
	pt.appendInput(4, 0.7);
	pt.appendOutput(4, 0.5);

	pt.appendPattern();
	pt.appendInput(5, 0.3);
	pt.appendOutput(5, 0.5);

	pt.appendPattern();
	pt.appendInput(6, 0.8);
	pt.appendOutput(6, 0.3);

	pt.appendPattern();
	pt.appendInput(7, 0.4);
	pt.appendOutput(7, 0.7);

	pt.appendPattern();
	pt.appendInput(8, 0.6);
	pt.appendOutput(8, 0.7);

	pt.appendPattern();
	pt.appendInput(9, 0.12);
	pt.appendOutput(9, 0.1);

	pt.appendPattern();
	pt.appendInput(10, 0.51);
	pt.appendOutput(10, 0.89);

	pt.appendPattern();
	pt.appendInput(11, 0.9);
	pt.appendOutput(11, 0.098);

	//creates neural network
	net.insertLayer(0);
	net.appendNeuron(0);

	net.insertLayer(1);
	for(int i = 0; i < 8; i++) net.appendNeuron(1);

	net.insertLayer(2);
	net.appendNeuron(2);

	net.randomizeWeights(10101010, -0.5, 0.5, -0.5, 0.5);

	qDebug() << net.toString().c_str();

	//learning
	BackPropagation bp(&net, &pt);
	bp.alpha = 0.5;

	double errp = 0;
	for(int x = 0; x < 5000; x++){
		double err = 0.0;
		for(unsigned int i = 0; i < pt.patternCount(); i++){
			err += bp.iterate(pt.patternCount()-1-i);
		}
		if(x%100 == 0){
			qDebug() << "iteration " << x << ": " << err;
		}
		if(err < 0.1) break;
		errp = err;
	}

	//gets neural net  output
	for(int i = 0; i <= 20; i++){
		float x = (1.0 / 20) * i;
		float y = sin(x);
		std::vector<double> in;
		in.push_back(x);
		qDebug() << x << "   \t" << net(in)[0];
	}
}*/

}
