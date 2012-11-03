#include "NeuralNetworkModel.h"

NeuralNetworkModel::NeuralNetworkModel(){}

void NeuralNetworkModel::setName(QString name){
	this->name = name;
}

QString NeuralNetworkModel::getName() const{
	return name;
}
