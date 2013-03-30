#include "Neuron.h"
#include "math.h"
#include <sstream>
#include <cassert>
#include "Util/Globaldef.h"

namespace NeuralNetwork{

/**
 * Creates neuron without weights and with bias of zero value.
 */
Neuron::Neuron() :
	biasVal(0),
	slopeVal(1),
	trFcnType(UnarySigmoid)
{}

/**
 * Creates copy of given neuron.
 */
Neuron::Neuron(const Neuron& neuron) :
	biasVal(neuron.biasVal),
	slopeVal(neuron.slopeVal),
	trFcnType(neuron.trFcnType),
	weight(neuron.weight)
{}

/**
 * Transfer function getter.
 * @see TransferFcn
 * @return type of neuron transfer function
 */
TransferFcn Neuron::trFcn() const{
	return trFcnType;
}

/**
 * Transfer function setter.
 * @see TransferFcn
 * @param trFcn new transfer function of neuron
 */
void Neuron::setTrFcn(TransferFcn trFcn){
	trFcnType = trFcn;
}


/**
 * Returns neuron bias value.
 */
double Neuron::bias() const{
	return biasVal;
}

/**
 * Sets neuron bias value.
 */
void Neuron::setBias(double bias){
	biasVal = bias;
}

/**
 * Adds given value to exiting neuron bias.
 */
void Neuron::addBias(double value){
	biasVal += value;
}

/**
 * Returns slope of neuron transfer function.
 */
double Neuron::slope() const{
	return slopeVal;
}

/**
 * Sets slope of neuron transfer function.
 */
void Neuron::setSlope(double slope){
	slopeVal = slope;
}

/**
 * Returns list of neuron weights.
 */
QList<double> Neuron::weights() const{
	return weight;
}

/**
 * Replaces actual weight list by given weight list.
 */
void Neuron::setWeights(const QList<double>& weights){
	weight = weights;
}

/**
 * Removes weight of neuron.
 * @param weightIndex index of weight between 0 and weightCount.
 */
void Neuron::removeWeight(int weightIndex){
	Q_ASSERT(weightIndex >= 0 && weightIndex < weight.length());
	weight.removeAt(weightIndex);
}

/**
 * Removes weight of neuron with highest index.
 */
void Neuron::removeLastWeight(){
	Q_ASSERT(!weight.empty());
	weight.removeLast();
}

/**
 * Removes or adds weights so neuron will have count weights.
 */
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

/**
 * Inserts weight of given value at position given by index.
 */
void Neuron::insertWeight(int weightIndex, double value){
	Q_ASSERT(weightIndex >= 0 && weightIndex <= weight.length());
	weight.insert(weightIndex, value);
}

/**
 * Appends count weights of given value.
 */
void Neuron::appendWeights(int count, double value){
	Q_ASSERT(count >= 0);
	for(int i = 0; i < count; i++){
		weight.append(value);
	}
}

/**
 * Appends weight of given value.
 */
void Neuron::appendWeight(double value){
	weight.append(value);
}

/**
 * Returns actual count of neuron weights.
 */
int Neuron::weightCount() const{
	return weight.length();
}

/**
 * Returns output of neuron.
 * @param input must be same length as weight count
 */
double Neuron::output(const QList<double>& input) const{
	Q_ASSERT(input.length() == weight.length());
	double sum = biasVal;
	for(int i = 0; i < input.size(); i++){
		sum += input[i] * weight[i];
	}
	return trFcn(sum);
}

/**
 * Returns output of neuron, can be used in case of one input.
 */
double Neuron::output(double input) const{
	Q_ASSERT(weight.length() == 1);
	double sum = biasVal + input*weight[0];
	return trFcn(sum);
}

/**
 * Returns string representation of neuron.
 */
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

/**
 * Returns reference to weight value at given index.
 */
double& Neuron::operator[](int weightIndex){
	Q_ASSERT(weightIndex >= 0 && weightIndex < weight.length());
	return weight[weightIndex];
}

/**
 * Assigns given neuron to this neuron.
 * @return reference to this neuron
 */
Neuron& Neuron::operator=(const Neuron& neuron){
	biasVal = neuron.biasVal;
	trFcnType = neuron.trFcnType;
	slopeVal = neuron.slopeVal;
	weight = neuron.weight;
	return *this;
}

/**
 * Calculates value of transfer function.
 */
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

/**
 * Calculates value of derived transfer function.
 */
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

/**
 * Class destructor
 */
Neuron::~Neuron(){}

}
