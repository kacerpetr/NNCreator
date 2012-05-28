#include "Network.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

Network::Network(void){}

Network::Network(const Network& network) : layer(network.layer){}

void Network::appendLayer(const Layer& layer){
	this->layer.append(layer);
}

Layer Network::getLayer(unsigned int index) const{
	return layer.at(index);
}

void Network::setLayer(unsigned int index, const Layer& layer){
	this->layer.replace(index, layer);
}

void Network::insertLayer(unsigned int index, const Layer& layer){
	this->layer.insert(index, layer);
}

Layer Network::removeLayer(unsigned int index){
	return layer.takeAt(index);
}

unsigned int Network::getCount(){
	return layer.length();
}

QString Network::toString(void){

}

Layer Network::fromString(QString str){

}

QList<double> Network::operator()(const QList<double>& input){
	QList<double> result;
	QList<Layer>::iterator it = layer.begin();

	result = (*it)(input);
	while(it != layer.end()){
		result = (*it)(result);
		it++;
	}

	return result;
}

}
