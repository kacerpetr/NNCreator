#include "Neuron.h"
#include "math.h"
#include <sstream>
#include <cassert>
#include "Util/function.h"
#include "Util/Exception.h"

namespace NeuralNetwork{

Neuron::Neuron() :
	biasVal(0),
	slopeVal(1),
	trFcnType(UnarySigmoid)
{}

Neuron::Neuron(const Neuron& neuron) :
	biasVal(neuron.biasVal),
	slopeVal(neuron.slopeVal),
	trFcnType(neuron.trFcnType),
	weight(neuron.weight)
{}

TransferFcn Neuron::trFcn() const{
	return trFcnType;
}

void Neuron::setTrFcn(TransferFcn trFcn){
	trFcnType = trFcn;
}

double Neuron::bias() const{
	return biasVal;
}

void Neuron::setBias(double bias){
	biasVal = bias;
}

void Neuron::addBias(double value){
	biasVal += value;
}

double Neuron::slope() const{
	return slopeVal;
}

void Neuron::setSlope(double slope){
	slopeVal = slope;
}

QList<double> Neuron::weights() const{
	return weight;
}

void Neuron::setWeights(const QList<double>& weights){
	weight = weights;
}

void Neuron::removeWeight(int weightIndex){
	Q_ASSERT(weightIndex >= 0 && weightIndex < weight.length());
	weight.removeAt(weightIndex);
}

void Neuron::removeLastWeight(){
	Q_ASSERT(!weight.empty());
	weight.removeLast();
}

void Neuron::leaveWeight(int count){
	Q_ASSERT(count >= 0);
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
	Q_ASSERT(weightIndex >= 0 && weightIndex <= weight.length());
	weight.insert(weightIndex, value);
}

void Neuron::appendWeights(int count, double value){
	Q_ASSERT(count >= 0);
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

double Neuron::output(const QList<double>& input) const{
	Q_ASSERT(input.length() == weight.length());
	double sum = biasVal;
	for(int i = 0; i < input.size(); i++){
		sum += input[i] * weight[i];
	}
	return trFcn(sum);
}

double Neuron::output(double input) const{
	Q_ASSERT(weight.length() == 1);
	double sum = biasVal + input*weight[0];
	return trFcn(sum);
}

QString Neuron::toString() const{
	QString str;

	str += "bias: " + QString::number(biasVal) + "\n";
	str += "slope: " + QString::number(slopeVal) + "\n";

	str += "transfer function: ";
	switch(trFcnType){
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
	Q_ASSERT(weightIndex >= 0 && weightIndex < weight.length());
	return weight[weightIndex];
}

Neuron& Neuron::operator=(const Neuron& neuron){
	biasVal = neuron.biasVal;
	trFcnType = neuron.trFcnType;
	slopeVal = neuron.slopeVal;
	weight = neuron.weight;
	return *this;
}

double Neuron::trFcn(double x) const{
	switch(trFcnType){
		case BinarySigmoid:
			return (1 - exp(-x*slopeVal)) / (1 + exp(-x*slopeVal));

		case UnarySigmoid:
			return 1 / (1 + exp(-x*slopeVal));

		default:
			return x*slopeVal;
	}
}

double Neuron::trFcnD(double x) const{
	switch(trFcnType){
		case BinarySigmoid:
			return 2*exp(-x) / ((1 + exp(-x))*(1 + exp(-x)));

		case UnarySigmoid:
			return exp(-x) / ((1 + exp(-x))*(1 + exp(-x)));

		default:
			return x*slopeVal;
	}
}

Neuron::~Neuron(){}

}
