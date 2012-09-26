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
#include <QStringList>
#include "Exception.h"


/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

Layer::Layer(void) : input(false){}

Layer::Layer(const Layer& layer) : neuron(layer.neuron), input(layer.input){}

Layer::Layer(QString str){
	input = false;

	str = str.replace(' ', "").replace('\t', "");

	if(str.isEmpty() || str.isNull()){
		throw(Exception(LayerParseError, "empty string given"));
	}

	QStringList line = str.split('\n');

	if(line.length() == 1 && line[0] != "Layer{}"){
		throw(Exception(LayerParseError, "(invalid syntax in \"" + str + "\", for empty layer expected: \"Layer{})\""));
	}else if(line.length() == 1 && line[0] == "Layer{}"){
		return;
	}

	if(line[0] != "Layer{"){
		throw(Exception(LayerParseError, "(invalid syntax in \"" + QString(line[0]) + "\", expected: \"Layer{)\""));
	}
	if(line[line.length()-1] != "}"){
		throw(Exception(LayerParseError, "(invalid syntax in \"" + QString(line[line.length()-1]) + "\", expected: \"}\")"));
	}

	for(int i = 0; i < line.length(); i++){

	}
}

void Layer::appendNeuron(const Neuron_old& neuron){
	this->neuron.append(neuron);
}

Neuron_old Layer::getNeuron(unsigned int index) const{
	return neuron.at(index);
}

void Layer::setNeuron(unsigned int index, const Neuron_old& neuron){
	this->neuron.replace(index, neuron);
}

void Layer::insertNeuron(unsigned int index, const Neuron_old& neuron){
	this->neuron.insert(index, neuron);
}

Neuron_old Layer::removeNeuron(unsigned int index){
	return neuron.takeAt(index);
}

unsigned int Layer::getCount(){
	return neuron.length();
}

bool Layer::isInput() const{
	return input;
}

void Layer::setInput(const bool input){
	this->input = input;
}

QString Layer::toString(void){
	QString res;
	res += "Layer{\n";
	res += "    Input = " + QString().number(input) + "\n";

	QList<Neuron_old>::iterator neuronIt = neuron.begin();
	while(neuronIt != neuron.end()){
		res += "    Neuron = " + (*neuronIt).toString() + "\n";
		neuronIt++;
	}

	res += "}";
	return res;
}

Layer Layer::fromString(QString str){

}

QList<double> Layer::operator()(QList<double> input){
	QList<double> result;
	QList<Neuron_old>::iterator neuronIt = neuron.begin();

	if(this->input){
		QList<double>::iterator inputIt = input.begin();

		while(neuronIt != neuron.end()){
			result.append((*neuronIt)(*inputIt));
			neuronIt++;
			inputIt++;
		}
	}else{
		while(neuronIt != neuron.end()){
			result.append((*neuronIt)(input));
			neuronIt++;
		}
	}

	return result;
}

}
