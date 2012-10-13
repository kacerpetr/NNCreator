#include "BackPropagationTest.h"
#include "NeuralNetwork/TrainingPattern.h"
#include "NeuralNetwork/BasicNetwork.h"
#include "NeuralNetwork/BackPropagation.h"
#include <QDebug>

namespace NeuralNetwork{

void BackPropagationTest::test(){
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
	for(int i = 0; i < 40; i++)net.appendNeuron(1);

	net.insertLayer(2);
	net.appendNeuron(2);

	net.randomizeWeights();

	//learning
	BackPropagation bp(&net, &pt);
	for(int x = 0; x < 1001; x++){
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

}
