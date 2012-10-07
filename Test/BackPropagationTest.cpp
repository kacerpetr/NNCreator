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
	pt.appendValue(0, 0, 1);
	pt.appendValue(0, 0, 1);

	pt.appendPattern();
	pt.appendValue(1, 0, 1);
	pt.appendValue(1, 1, 1);

	/*pt.appendPattern();
	pt.appendValue(2, 1, 1);
	pt.appendValue(2, 0, 1);

	pt.appendPattern();
	pt.appendValue(3, 1, 0);
	pt.appendValue(3, 1, 0);*/

	//network
	BasicNetwork net;

	net.insertLayer(0);
	net.appendNeuron(0);
	net.appendNeuron(0);

	net.insertLayer(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);
	net.appendNeuron(1);

	net.insertLayer(2);
	net.appendNeuron(2);
	net.appendNeuron(2);

	net.randomizeWeights();

	//learning
	BackPropagation bp(&net, &pt);
	for(int x = 0; x < 20001; x++){
		double err = 0.0;
		for(int i = 0; i < pt.patternCount(); i++){
			err += bp.iterate(i);
		}
		if(x%1000 == 0) qDebug() << "iteration " << x << ": " << err;
	}
}

}
