/*
 * This file is part of neuron network experimental implementation.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2012 Petr Kacer (kacerpetr@gmail.com)
 */

#include "Layer.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

Layer::Layer(void){}

Layer::Layer(const Layer& layer) : neuron(layer.neuron){}

void Layer::appendNeuron(const Neuron& neuron){
	this->neuron.append(neuron);
}

Neuron Layer::getNeuron(unsigned int index) const{
	return neuron.at(index);
}

void Layer::setNeuron(unsigned int index, const Neuron& neuron){
	this->neuron.replace(index, neuron);
}

void Layer::insertNeuron(unsigned int index, const Neuron& neuron){
	this->neuron.insert(index, neuron);
}

Neuron Layer::removeNeuron(unsigned int index){
	return neuron.takeAt(index);
}

unsigned int Layer::getCount(){
	return neuron.length();
}

QString Layer::toString(void){

}

Layer Layer::fromString(QString str){

}

QList<double> Layer::operator()(QList<double> input){
	// if(input.length() != neuron.length());

	QList<double> result;
	QList<Neuron>::iterator it = neuron.begin();

	while(it != neuron.end()){
		result.append((*it)(input));
		it++;
	}

	return result;
}

}
