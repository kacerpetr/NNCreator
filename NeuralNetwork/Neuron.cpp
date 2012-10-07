#include "Neuron.h"
#include "math.h"
#include <sstream>
#include <cassert>
#include "Util/function.h"
#include "Util/Exception.h"

namespace NeuralNetwork{

Neuron::Neuron() : bias(0){}

Neuron::Neuron(const Neuron& neuron) : bias(neuron.bias), weight(neuron.weight){}

Neuron::Neuron(std::string str) : bias(0){
	int state = 0;
	std::string num = "";

	for(unsigned int i = 0; i < str.length(); i++){
		char ch = str[i];
		if(ch == ' ') continue;
		if(ch != ' ' && state == 0) state = 1;

		switch(state){
			//bias
			case 1:
				if(ch == ','){
					bias = Util::stringToDouble(num);
					state = 2;
					num = "";
				}else{
					num = num + ch;
				}
				break;

			//brace check
			case 2:
				if(ch == '[') state = 3;
				else throw(Util::Exception(Util::NeuronParseError, "expected '['"));
				break;

			//weights
			case 3:
				if(ch == ','){
					if(!num.empty()) weight.push_back(Util::stringToDouble(num));
					num = "";
				}else if(ch == ']'){
					if(!num.empty()) weight.push_back(Util::stringToDouble(num));
					num = "";
					state = 4;
				}else{
					num = num + ch;
				}
				break;
		}
	}

	if(state == 0) throw(Util::Exception(Util::NeuronParseError, "empty string given"));
	if(state == 1) throw(Util::Exception(Util::NeuronParseError, "expected ',' before '['"));
	if(state == 2) throw(Util::Exception(Util::NeuronParseError, "expected '['"));
	if(state == 3) throw(Util::Exception(Util::NeuronParseError, "expected ']'"));
}

void Neuron::setWeight(const std::vector<double>& weight){
	this->weight = weight;
}

std::vector<double> Neuron::getWeight() const{
	return weight;
}

int Neuron::weightCount() const{
	return weight.size();
}

double Neuron::getWeight(int index) const{
	return this->weight[index];
}

void Neuron::setWeight(double value, int index){
	this->weight[index] = value;
}

void Neuron::removeWeight(int index){
	std::vector<double>::iterator it = this->weight.begin() + index;
	this->weight.erase(it);
}

void Neuron::insertWeight(double value, int index){
	std::vector<double>::iterator it = this->weight.begin() + index;
	this->weight.insert(it, value);
}

void Neuron::appendWeight(double value){
	this->weight.push_back(value);
}

void Neuron::setBias(double bias){
	this->bias = bias;
}

double Neuron::getBias() const{
	return bias;
}

double Neuron::transferFcn(double x) const{
	//hyperbolic tangens
	return (1 - exp(-x)) / (1 + exp(-x));
}

double Neuron::operator()(double input) const{
	assert(weight.size() == 1);
	double sum = bias + input*weight[0];
	return transferFcn(sum);
}

double Neuron::operator()(const std::vector<double>& input) const{
	assert(input.size() == weight.size());
	double sum = bias;
	for(unsigned int i = 0; i < input.size(); i++)	sum += input[i] * weight[i];
	return transferFcn(sum);
}

void Neuron::operator=(const Neuron& neuron){
	bias = neuron.bias;
	weight = neuron.weight;
}

std::string Neuron::toString() const{
	std::ostringstream ostr;
	ostr << bias << ", ";
	ostr << "[";
	for(unsigned int i = 0; i < weight.size(); i++){
		ostr << weight[i];
		if(i != weight.size()-1) ostr << ", ";
	}
	ostr << "]";
	return ostr.str();
}

}
