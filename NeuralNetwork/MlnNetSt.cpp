/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MlnNetSt.h"
#include "Util/Globaldef.h"

namespace NeuralNetwork{

/**
 * Creates neural network with one input and one neuron in output layer.
 */
MlnNetSt::MlnNetSt() : AbstractMlnNet(), trFcn(UnarySigmoid), inCnt(1){
	appendLayer();
}

/**
 * Creates copy of given neural network.
 */
MlnNetSt::MlnNetSt(const MlnNetSt& obj) : AbstractMlnNet(), inCnt(obj.inCnt){
	net = obj.net;
}

void MlnNetSt::setInputCount(int count){
	Q_ASSERT(count > 0);
	Q_ASSERT(net.length() > 0);
	inCnt = count;
	for(int i = 0; i < net[0].length(); i++){
		net[0][i].leaveWeight(inCnt);
	}
}

void MlnNetSt::appendLayer(){
	QList<Neuron> layer;
	if(net.length() == 0){
		Neuron n;
        n.setTrFcn(trFcn);
		n.appendWeight(0.5);
		layer.append(n);
	}else{
		Neuron n;
        n.setTrFcn(trFcn);
		n.appendWeights(net.last().length(), 0.5);
		layer.append(n);
	}
	net.append(layer);
}

void MlnNetSt::insertLayer(int position){
	Q_ASSERT(position >= 0 && position <= net.length());
	if(net.length() == 0 || position == net.length()){
		appendLayer();
	}else{
		QList<Neuron> layer;
		if(position == 0){
			Neuron n;
            n.setTrFcn(trFcn);
			n.appendWeights(inCnt, 0.5);
			layer.append(n);
		}else{
			Neuron n;
            n.setTrFcn(trFcn);
			n.appendWeights(net[position-1].length(), 0.5);
			layer.append(n);
		}
		for(int i = 0; i < net[position].length(); i++){
			net[position][i].leaveWeight(1);
		}
		net.insert(position, layer);
	}
}

void MlnNetSt::removeLayer(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(net.length() > 1);
	if(layer == 0){
		net.removeAt(0);
		for(int i = 0; i < net[0].length(); i++){
			net[0][i].leaveWeight(inCnt);
		}
	}else if(layer == net.length()-1){
		net.removeAt(layer);
	}else{
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].leaveWeight(net[layer-1].length());
		}
		net.removeAt(layer);
	}
}

void MlnNetSt::duplicateLayer(int layer){
	Q_ASSERT(layer >= -1 && layer < net.length());
	if(layer == -1){
		net.insert(0, QList<Neuron>());
		while(net[0].length() < inCnt){
			Neuron n;
			n.appendWeights(inCnt, 0.5);
			net[0].append(n);
		}
	}
	else{
		net.insert(layer, net[layer]);
		for(int i = 0; i < net[layer].length(); i++){
			net[layer+1][i].leaveWeight(net[layer].length());
		}
	}
}

void MlnNetSt::appendNeuron(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Neuron n;
    n.setTrFcn(trFcn);
	if(layer != 0) n.appendWeights(net[layer-1].length(), 0.5);
	else n.appendWeights(inCnt, 0.5);
	appendNeuron(layer, n);
}

void MlnNetSt::appendNeuron(int layer, int count){
	Q_ASSERT(layer >= 0 && layer < net.length());
	for(int i = 0; i < count; i++) appendNeuron(layer);
}

void MlnNetSt::appendNeuron(int layer, const Neuron& neuron){
	Q_ASSERT(layer >= 0 && layer < net.length());
	net[layer].append(Neuron(neuron));
	if(layer != net.size()-1){
		for(int i = 0; i < net[layer+1].size(); i++){
			net[layer+1][i].appendWeight(0.5);
		}
	}
}

void MlnNetSt::removeLastNeuron(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(net[layer].length() >= 1);
	if(layer != net.length()-1){
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].removeLastWeight();
		}
	}
	net[layer].removeLast();
}

void MlnNetSt::insertNeuron(int layer, int position){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(position >= 0 && position <= net[layer].length());
	if(layer == 0){
		Neuron n;
        n.setTrFcn(trFcn);
		n.appendWeights(inCnt, 0.5);
		net[layer].insert(position, n);
	}else if(layer == net.length()-1){
		Neuron n;
        n.setTrFcn(trFcn);
		n.appendWeights(net[layer-1].length(), 0.5);
		net[layer].insert(position, n);
	}else{
		Neuron n;
        n.setTrFcn(trFcn);
		n.appendWeights(net[layer-1].length(), 0.5);
		net[layer].insert(position, n);
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].leaveWeight(net[layer].length());
		}
	}

}

void MlnNetSt::removeNeuron(int layer, int position){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(position >= 0 && position <= net[layer].length());
	Q_ASSERT(net[layer].length() > 1);
	if(layer != net.length()-1){
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].removeWeight(position);
		}
	}
	net[layer].removeAt(position);
}

void MlnNetSt::setNeuronCount(int layer, int count){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(count > 0);
	if(net[layer].length() == count){
		return;
	}
	else if(count < net[layer].length()){
		for(int i = 0; i < net[layer].length()-count; i++){
			removeLastNeuron(layer);
		}
	}
	else
	{
		appendNeuron(layer, count-net[layer].length());
	}

}

int MlnNetSt::inputCount() const{
	return inCnt;
}

int MlnNetSt::layerCount() const{
	return net.length();
}

int MlnNetSt::neuronCount() const{
	int sum = 0;
	for(int i = 0; i < net.length(); i++){
		sum += net[i].length();
	}
	return sum;
}

int MlnNetSt::neuronCount(int layer) const{
	Q_ASSERT(layer >= 0 && layer < net.length());
	return net[layer].length();
}

int MlnNetSt::weightCount() const{
	int sum = 0;
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			sum += net[i][j].weightCount();
		}
	}

    sum += neuronCount(); //bias count
    return sum;
}

int MlnNetSt::weightCount(int layer) const{
	Q_ASSERT(layer >= 0 && layer < net.length());
	return net[layer][0].weightCount();
}

int MlnNetSt::outputCount() const{
	return net.last().length();
}

void MlnNetSt::setBias(double value){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			net[i][j].setBias(value);
		}
	}
}

void MlnNetSt::randomizeWeight(int seed, double min, double max){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			for(int k = 0; k < net[i][j].weightCount(); k++){
                net[i][j][k] = random(seed, min, max);
				seed++;
			}
		}
	}
}

void MlnNetSt::randomizeBias(int seed, double min, double max){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
            net[i][j].setBias(random(seed, min, max));
			seed++;
		}
	}
}

void MlnNetSt::randomizeSlope(int seed, double min, double max){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
            net[i][j].setSlope(random(seed, min, max));
			seed++;
		}
	}
}

void MlnNetSt::setTransferFunction(TransferFcn trFcn){
    this->trFcn = trFcn;
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			net[i][j].setTrFcn(trFcn);
		}
	}
}

TransferFcn MlnNetSt::transferFunction() const{
    return trFcn;
}

QList<double> MlnNetSt::output(const QList<double>& input) const{
	Q_ASSERT(input.length() == inCnt);
	QList<double> layerOut = input;
	for(int i = 0; i < net.length(); i++){
		QList<double> neuronOut;
		for(int j = 0; j < net[i].size(); j++){
			neuronOut.append(net[i][j].output(layerOut));
		}
		layerOut = neuronOut;
	}
	return layerOut;
}

QList< QList<double> > MlnNetSt::layerOutput(const QList<double>& input) const{
	Q_ASSERT(input.length() == inCnt);
	QList< QList<double> > layerOut;
	layerOut.append(input);
	for(int i = 0; i < net.length(); i++){
		QList<double> neuronOut;
		for(int j = 0; j < net[i].size(); j++){
			neuronOut.append(net[i][j].output(layerOut[i]));
		}
		layerOut.append(neuronOut);
	}
	return layerOut;
}

QList<Neuron>& MlnNetSt::operator[](int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	return net[layer];
}

QString MlnNetSt::toString() const{
	QString str = "Multilayer neural network (single thread implementation):";
	str += "\n\nInput layer: " + QString::number(inCnt) + " input neurons.\n";
	for(int i = 0; i < net.length(); i++){
		if(i < net.length()-1){
			str += "\nInner layer " + QString::number(i) + ":";
		}else{
			str += "\nOutput layer " + QString::number(i) + ":";
		}
		for(int j = 0; j < net[i].length(); j++){
			str += "\n  Neuron " + QString::number(j) + ":\n";
			str += "    " +(net[i][j].toString().replace("\n", "\n    ")).trimmed();
		}
		if(i < net.length()-1) str += "\n";
	}
	return str.trimmed();
}

/**
 * Class destructor.
 */
MlnNetSt::~MlnNetSt(){}

}
