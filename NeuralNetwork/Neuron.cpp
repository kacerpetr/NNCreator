#include "Neuron.h"
#include "math.h"
#include <sstream>
#include <cassert>
#include "Util/function.h"
#include "Util/Exception.h"

namespace NeuralNetwork{

Neuron::Neuron() : bias(0), slope(1), trFcn(UnarySigmoid){}

Neuron::Neuron(const Neuron& neuron) : bias(neuron.bias), slope(neuron.slope), trFcn(neuron.trFcn){
	weight = neuron.weight;
}

TransferFcn Neuron::getTrFcn() const{
	return trFcn;
}

void Neuron::setTrFcn(TransferFcn trFcn){
	this->trFcn = trFcn;
}

double Neuron::getBias() const{
	return bias;
}

void Neuron::setBias(double bias){
	this->bias = bias;
}

double Neuron::getSlope() const{
	return slope;
}

void Neuron::setSlope(double slope){
	this->slope = slope;
}

QList<double> Neuron::getWeights() const{
	return weight;
}

void Neuron::setWeights(const QList<double>& weights){
	weight = weights;
}

double Neuron::getWeight(int weightIndex) const{
	return weight[weightIndex];
}

void Neuron::setWeight(int weightIndex, double value){
	weight[weightIndex] = value;
}

void Neuron::removeWeight(int weightIndex){
	weight.removeAt(weightIndex);
}

void Neuron::removeLastWeight(){
	weight.removeLast();
}

void Neuron::leaveWeight(int count){
	if(count == 0){
		weight.clear();
	}
	else if(count > weight.length()){
		appendWeights(count - weight.length(), 0.5);
	}
	else if(count < weight.length()){
		int len = weight.length();
		for(int i = 0; i < len-count; i++){
			weight.removeLast();
		}
	}
}

void Neuron::insertWeight(int weightIndex, double value){
	weight.insert(weightIndex, value);
}

void Neuron::appendWeights(int count, double value){
	for(int i = 0; i < count; i++){
		weight.append(value);
	}
}

void Neuron::appendWeight(double value){
	weight.append(value);
}

int Neuron::weightCount() const{
	return weight.length();
}

double Neuron::getOutput(const QList<double>& input) const{
	double sum = bias;
	for(int i = 0; i < input.size(); i++){
		sum += input[i] * weight[i];
	}
	return transferFcn(sum);
}

double Neuron::getOutput(double input) const{
	double sum = bias + input*weight[0];
	return transferFcn(sum);
}

QString Neuron::toString() const{
	QString str;

	str += "bias: " + QString::number(bias) + "\n";
	str += "slope: " + QString::number(slope) + "\n";

	str += "transfer function: ";
	switch(trFcn){
		case BinarySigmoid:
			str += "binary sigmoid\n";
			break;
		case UnarySigmoid:
			str += "unary sigmoid\n";
			break;
	}

	str += "weights: [";
	for(int i = 0; i < weight.size(); i++){
		str += QString::number(weight[i]);
		if(i != weight.size()-1) str+= ", ";
	}
	str += "]\n";

	return str;
}

double& Neuron::operator[](int weightIndex){
	return weight[weightIndex];
}

Neuron& Neuron::operator=(const Neuron& neuron){
	bias = neuron.bias;
	trFcn = neuron.trFcn;
	slope = neuron.slope;
	weight = neuron.weight;
	return *this;
}

Neuron::~Neuron(){}

double Neuron::transferFcn(double x) const{
	switch(trFcn){
		case BinarySigmoid:
			return (1 - exp(-x*slope)) / (1 + exp(-x*slope));

		case UnarySigmoid:
			return 1 / (1 + exp(-x*slope));

		default:
			return x*slope;
	}
}

}
