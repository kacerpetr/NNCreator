#include "BackPropagation.h"
#include <cassert>
#include <cmath>
#include <iostream>

namespace NeuralNetwork{

BackPropagation::BackPropagation(INeuralNetwork* neuralNetwork, TrainingPattern* trainingPattern) : alpha(0.5){
	assert(neuralNetwork != NULL && trainingPattern != NULL);
	this->neuralNetwork = neuralNetwork;
	this->trainingPattern = trainingPattern;

	for(unsigned int l = 0; l < neuralNetwork->layerCount(); l++){
		delta.push_back(std::vector<double>());
		output.push_back(std::vector<double>());
		for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
			delta[l].push_back(0.0);
			output[l].push_back(0.0);
		}
	}
}

double BackPropagation::iterate(unsigned int pattern){
	//feedforward
	std::vector<double> li = trainingPattern->getInput(pattern);
	for(unsigned int l = 0; l < neuralNetwork->layerCount(); l++){
		if(l == 0){
			for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
				output[l][n] = neuralNetwork->getNeuron(l,n)(li[n]);
			}
		}else{
			for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
				output[l][n] = neuralNetwork->getNeuron(l,n)(output[l-1]);
			}
		}
	}

	//delta calculation - output layer
	unsigned int l = neuralNetwork->layerCount()-1;
	for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
		double sum = 0.0;
		for(unsigned int i = 0; i < neuralNetwork->weightCount(l,n); i++){
			sum += output[l-1][i] * neuralNetwork->getWeight(l,n,i);
		}
		sum += neuralNetwork->getBias(l, n);
		delta[l][n] = (trainingPattern->getOutput(pattern, n) - output[l-1][n]) * transferFcnD(sum);
	}

	//delta calculation - inner layers
	for(unsigned int l = neuralNetwork->layerCount()-2; l >= 1; l--){
		for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
			double sum = 0.0;
			for(unsigned int i = 0; i < neuralNetwork->weightCount(l,n); i++){
				sum += output[l-1][i] * neuralNetwork->getWeight(l,n,i);
			}
			sum += neuralNetwork->getBias(l, n);

			double sum2 = 0.0;
			for(unsigned int m = 0; m < neuralNetwork->neuronCount(l+1); m++){
				sum2 += delta[l+1][m] * neuralNetwork->getWeight(l+1, m, n);
			}

			delta[l][n] = sum2*transferFcnD(sum);
		}
	}

	//delta calculation - input layer
	l = 0;
	for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
		double sum = 0.0;
		for(unsigned int i = 0; i < neuralNetwork->weightCount(l,n); i++){
			sum += trainingPattern->getInput(pattern, i) * neuralNetwork->getWeight(l,n,i);
		}
		sum += neuralNetwork->getBias(l, n);

		double sum2 = 0.0;
		for(unsigned int m = 0; m < neuralNetwork->neuronCount(l+1); m++){
			sum2 += delta[l+1][m] * neuralNetwork->getWeight(l+1, m, n);
		}

		delta[l][n] = sum2*transferFcnD(sum);
	}

	//weight adjustment - output layer and inner layers
	for(unsigned int l = neuralNetwork->layerCount()-1; l >= 1; l--){
		for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
			double k = delta[l][n] * alpha;
			for(unsigned int i = 0; i < neuralNetwork->weightCount(l,n); i++){
				neuralNetwork->addWeight(k * output[l-1][i], l, n, i);
			}
			neuralNetwork->addBias(k, l, n);
		}
	}

	//weight adjustment - input layer
	for(unsigned int n = 0; n < neuralNetwork->neuronCount(l); n++){
		double k = delta[l][n] * alpha;
		for(unsigned int i = 0; i < neuralNetwork->weightCount(l,n); i++){
			neuralNetwork->addWeight(k * trainingPattern->getInput(pattern, i), l, n, i);
		}
		neuralNetwork->addBias(k, l, n);
	}

	//partial error calculation
	double err = 0.0;
	std::vector<double> out = (*neuralNetwork)(trainingPattern->getInput(pattern));
	for(unsigned int i = 0; i < out.size(); i++){
		double val = out[i] - trainingPattern->getOutput(pattern, i);
		err += val*val;
	}
	return err / 2.0;
}

double BackPropagation::transferFcnD(double x) const{
	//derivation of hyperbolic tangens
	return 2*exp(-x) / ((1 + exp(-x))*(1 + exp(-x)));
}

}
