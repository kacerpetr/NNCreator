#include "BasicNetwork.h"
#include <sstream>
#include "Util/Exception.h"
#include "Util/function.h"
#include <iostream>

namespace NeuralNetwork{

BasicNetwork::BasicNetwork() : INeuralNetwork(){}

BasicNetwork::BasicNetwork(const BasicNetwork& obj) : INeuralNetwork(){
	net = obj.net;
}

BasicNetwork::BasicNetwork(const std::string& str) : INeuralNetwork(){
	int state = 0;
	std::string word = "";
	int layer = -1;

	for(unsigned int i = 0; i < str.length(); i++){
		char ch = str[i];

		switch(state){
			case 0:
				if(ch == '\n'){
					if(word=="Layer:"){
						state = 1;
						word = "";
						appendLayer();
						layer++;
					}else{
						throw(Util::Exception(Util::NeuralNetworkParseError, "expected 'Layer:'"));
					}
				}
				break;

			case 1:
				if(ch == 'L'){
					state = 0;
					word = "";
				}else if(ch == '\n'){
					Neuron n(word);
					appendNeuron(n, layer);
					word = "";
				}
				break;
		}

		if(ch != '\n') word = word + ch;
	}
}

BasicNetwork::~BasicNetwork(){}

void BasicNetwork::setWeights(const std::vector<double>& obj, unsigned int layer, unsigned int neuron){
	net[layer][neuron].setWeight(obj);
}

void BasicNetwork::setNeurons(const std::vector<Neuron>& obj, unsigned int layer){
	net[layer] = obj;
}

void BasicNetwork::setWeight(double value, unsigned int layer, unsigned int neuron, unsigned int weight){
	net[layer][neuron].setWeight(value, weight);
}

void BasicNetwork::setNeuron(Neuron obj, unsigned int layer, unsigned int neuron){
	net[layer][neuron] = obj;
}

void BasicNetwork::setBias(double value, unsigned int layer, unsigned int neuron){
	net[layer][neuron].setBias(value);
}

void BasicNetwork::setBias(double value){
	for(unsigned int i = 0; i < net.size(); i++){
		for(unsigned int j = 0; j < net[j].size(); j++){
			net[i][j].setBias(value);
		}
	}
}

void BasicNetwork::addWeight(double value, unsigned int layer, unsigned int neuron, unsigned int weight){
	net[layer][neuron].setWeight(net[layer][neuron].getWeight(weight) + value, weight);
}

void BasicNetwork::addBias(double value, unsigned int layer, unsigned int neuron){
	net[layer][neuron].setBias(net[layer][neuron].getBias() + value);
}

std::vector<double> BasicNetwork::getWeights(unsigned int layer, unsigned int neuron) const{
	return net[layer][neuron].getWeight();
}

std::vector<Neuron> BasicNetwork::getNeurons(unsigned int layer) const{
	return net[layer];
}

double BasicNetwork::getWeight(unsigned int layer, unsigned int neuron, unsigned int weight) const{
	return net[layer][neuron].getWeight(weight);
}

Neuron BasicNetwork::getNeuron(unsigned int layer, unsigned int neuron) const{
	return net[layer][neuron];
}

double BasicNetwork::getBias(unsigned int layer, unsigned int neuron) const{
	return net[layer][neuron].getBias();
}

void BasicNetwork::appendLayer(){
	std::vector<Neuron> layer;
	net.push_back(layer);
}

void BasicNetwork::insertLayer(unsigned int position){
	std::vector<Neuron> layer;

	std::vector< std::vector<Neuron> >::iterator it = net.begin() + position;
	net.insert(it, layer);

	if(position != net.size()-1){
		std::vector<double> weight;
		weight.push_back(0.5);

		for(unsigned int i = 0; i < net[position+1].size(); i++){
			net[position+1][i].setWeight(weight);
		}
	}
}

void BasicNetwork::removeLayer(unsigned int position){
	std::vector< std::vector<Neuron> >::iterator it = net.begin() + position;
	net.erase(it);

	if(position != net.size()-1 || position != 0){
		std::vector<double> weight;
		for(unsigned int i = 0; i < net[position-1].size(); i++) weight.push_back(0.5);
		for(unsigned int i = 0; i < net[position].size(); i++) net[position][i].setWeight(weight);
	}
}

void BasicNetwork::appendNeuron(unsigned int layer){
	Neuron n;

	std::vector<double> weight;
	if(layer != 0){
		for(unsigned int i = 0; i < net[layer-1].size(); i++) weight.push_back(0.5);
	}else{
		weight.push_back(0.5);
	}
	n.setWeight(weight);

	appendNeuron(n, layer);
}

void BasicNetwork::appendNeuron(Neuron obj, unsigned int layer){
	net[layer].push_back(obj);

	if(layer != net.size()-1){
		for(unsigned int i = 0; i < net[layer+1].size(); i++){
			net[layer+1][i].appendWeight(0.5);
		}
	}
}

void BasicNetwork::insertNeuron(unsigned int layer, unsigned int position){
	Neuron n;
	std::vector<double> weight;

	if(layer != 0){
		for(unsigned int i = 0; i < net[layer-1].size(); i++) weight.push_back(0.5);
	}else{
		weight.push_back(0.5);
	}

	n.setWeight(weight);

	net[layer].push_back(n);

	for(unsigned int i = 0; i < net[layer+1].size(); i++){
		net[layer+1][i].insertWeight(0.5,position);
	}
}

void BasicNetwork::removeNeuron(unsigned int layer, unsigned int position){
	std::vector<Neuron>::iterator it = net[layer].begin() + position;
	net[layer].erase(it);

	if(layer != net.size()-1){
		for(unsigned int i = 0; i < net[layer].size(); i++){
			net[layer][i].removeWeight(position);
		}
	}
}

unsigned int BasicNetwork::weightCount(unsigned int layer, unsigned int neuron) const{
	return net[layer][neuron].weightCount();
}

unsigned int BasicNetwork::neuronCount(unsigned int layer) const{
	return net[layer].size();
}

unsigned int BasicNetwork::layerCount() const{
	return net.size();
}

std::vector<double> BasicNetwork::operator()(const std::vector<double>& input){
	std::vector<double> lo;
	std::vector<double> li = input;

	for(unsigned int l = 0; l < net.size(); l++){
		if(l == 0){
			for(unsigned int n = 0; n < net[l].size(); n++){
				lo.push_back(net[l][n](li[n]));
			}
		}else{
			lo.clear();
			for(unsigned int n = 0; n < net[l].size(); n++){
				lo.push_back(net[l][n](li));
			}
		}
		li = lo;
	}

	return lo;
}

void BasicNetwork::operator=(const BasicNetwork& obj){
	this->net = obj.net;
}

void BasicNetwork::randomizeWeights(){
	for(unsigned int l = 0; l < net.size(); l++){
		for(unsigned int n = 0; n < net[l].size(); n++){
			for(int w = 0; w < net[l][n].weightCount(); w++){
				net[l][n].setWeight(Util::random(-0.5,0.5), w);
			}
			net[l][n].setBias(Util::random(-0.5,0.5));
		}
	}
}

std::string BasicNetwork::toString() const{
	std::ostringstream ostr;

	for(unsigned int i = 0; i < net.size(); i++){
		ostr << "Layer:" << '\n';
		for(unsigned int j = 0; j < net[i].size(); j++){
			ostr << net[i][j].toString() << '\n';
		}
	}

	return ostr.str();
}

}
