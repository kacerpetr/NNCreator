#include "Neuron.h"

Neuron::Neuron() : bias(0){}

Neuron::Neuron(const Neuron& obj) : bias(obj.bias), weight(obj.weight), input(obj.input){}

Neuron::Neuron(const string& obj){
	//TODO
}

int Neuron::inputCount() const{
	return input.size();
}

double Neuron::getInput(int input) const{

}

double Neuron::setInput(double value, int input){

}

int Neuron::weightCount() const{
	return weight.size();
}

double Neuron::getWeight(int weight) const{

}

void Neuron::setWeight(int value, double weight){

}

double Neuron::removeWeight(int weight){

}

void Neuron::insertWeight(double value, int weight){

}

void Neuron::appendWeight(double value){

}

string Neuron::toString(){

}

double Neuron::operator()() const{

}
