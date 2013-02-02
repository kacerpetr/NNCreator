#include "BpNetSt.h"
#include "Util/function.h"

namespace NeuralNetwork{


BpNetSt::BpNetSt() : AbstractBpNet(), inputCount(1){
	appendLayer();
}

BpNetSt::BpNetSt(const BpNetSt& obj) : AbstractBpNet(), inputCount(obj.inputCount){
	net = obj.net;
}

void BpNetSt::setInputCount(int count){
	Q_ASSERT(count > 0);
	Q_ASSERT(net.length() > 0);
	inputCount = count;
	for(int i = 0; i < net[0].length(); i++){
		net[0][i].leaveWeight(inputCount);
	}
}

void BpNetSt::appendLayer(){
	QList<Neuron> layer;
	if(net.length() == 0){
		Neuron n;
		n.appendWeight(0.5);
		layer.append(n);
	}else{
		Neuron n;
		n.appendWeights(net.last().length(), 0.5);
		layer.append(n);
	}
	net.append(layer);
}

void BpNetSt::insertLayer(int position){
	Q_ASSERT(position >= 0 && position <= net.length());
	if(net.length() == 0 || position == net.length()){
		appendLayer();
	}else{
		QList<Neuron> layer;
		if(position == 0){
			Neuron n;
			n.appendWeights(inputCount, 0.5);
			layer.append(n);
		}else{
			Neuron n;
			n.appendWeights(net[position-1].length(), 0.5);
			layer.append(n);
		}
		for(int i = 0; i < net[position].length(); i++){
			net[position][i].leaveWeight(1);
		}
		net.insert(position, layer);
	}
}

void BpNetSt::removeLayer(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(net.length() > 1);
	if(layer == 0){
		net.removeAt(0);
		for(int i = 0; i < net[0].length(); i++){
			net[0][i].leaveWeight(inputCount);
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

void BpNetSt::duplicateLayer(int layer){
	Q_ASSERT(layer >= -1 && layer < net.length());
	if(layer == -1){
		net.insert(0, QList<Neuron>());
		while(net[0].length() < inputCount){
			Neuron n;
			n.appendWeights(inputCount, 0.5);
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

void BpNetSt::appendNeuron(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Neuron n;
	if(layer != 0) n.appendWeights(net[layer-1].length(), 0.5);
	else n.appendWeights(inputCount, 0.5);
	appendNeuron(layer, n);
}

void BpNetSt::appendNeuron(int layer, int count){
	Q_ASSERT(layer >= 0 && layer < net.length());
	for(int i = 0; i < count; i++) appendNeuron(layer);
}

void BpNetSt::appendNeuron(int layer, const Neuron& neuron){
	Q_ASSERT(layer >= 0 && layer < net.length());
	net[layer].append(Neuron(neuron));
	if(layer != net.size()-1){
		for(int i = 0; i < net[layer+1].size(); i++){
			net[layer+1][i].appendWeight(0.5);
		}
	}
}

void BpNetSt::removeLastNeuron(int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(net[layer].length() > 1);
	if(layer != net.length()-1){
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].removeLastWeight();
		}
	}
	net[layer].removeLast();
}

void BpNetSt::insertNeuron(int layer, int position){
	Q_ASSERT(layer >= 0 && layer < net.length());
	Q_ASSERT(position >= 0 && position <= net[layer].length());
	if(layer == 0){
		Neuron n;
		n.appendWeights(inputCount, 0.5);
		net[layer].insert(position, n);
	}else if(layer == net.length()-1){
		Neuron n;
		n.appendWeights(net[layer-1].length(), 0.5);
		net[layer].insert(position, n);
	}else{
		Neuron n;
		n.appendWeights(net[layer-1].length(), 0.5);
		net[layer].insert(position, n);
		for(int i = 0; i < net[layer+1].length(); i++){
			net[layer+1][i].leaveWeight(net[layer].length());
		}
	}

}

void BpNetSt::removeNeuron(int layer, int position){
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

int BpNetSt::getInputCount() const{
	return inputCount;
}

int BpNetSt::getLayerCount() const{
	return net.length();
}

int BpNetSt::getNeuronCount() const{
	int sum = 0;
	for(int i = 0; i < net.length(); i++){
		sum += net[i].length();
	}
	return sum;
}

int BpNetSt::getWeightCount() const{
	int sum = 0;
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			sum += net[i][j].weightCount();
		}
	}
	return sum;
}

int BpNetSt::getNeuronCount(int layer) const{
	Q_ASSERT(layer >= 0 && layer < net.length());
	return net[layer].length();
}

void BpNetSt::setBias(double value){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			net[i][j].setBias(value);
		}
	}
}

void BpNetSt::randomizeWeight(int seed, double min, double max){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			for(int k = 0; k < net[i][j].weightCount(); k++){
				net[i][j][k] = Util::random(seed, min, max);
				seed++;
			}
		}
	}
}

void BpNetSt::randomizeBias(int seed, double min, double max){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			net[i][j].setBias(Util::random(seed, min, max));
			seed++;
		}
	}
}

void BpNetSt::setTransferFunction(TransferFcn trFcn){
	for(int i = 0; i < net.length(); i++){
		for(int j = 0; j < net[i].length(); j++){
			net[i][j].setTrFcn(trFcn);
		}
	}
}

QList<double> BpNetSt::getOutput(const QList<double>& input) const{
	Q_ASSERT(input.length() == inputCount);
	QList<double> layerOut = input;
	for(int i = 0; i < net.length(); i++){
		QList<double> neuronOut;
		for(int j = 0; j < net[i].size(); j++){
			neuronOut.append(net[i][j].getOutput(layerOut));
		}
		layerOut = neuronOut;
	}
	return layerOut;
}

QList< QList<double> > BpNetSt::getLayerOutput(const QList<double>& input) const{
	Q_ASSERT(input.length() == inputCount);
	QList< QList<double> > layerOut;
	layerOut.append(input);
	for(int i = 0; i < net.length(); i++){
		QList<double> neuronOut;
		for(int j = 0; j < net[i].size(); j++){
			neuronOut.append(net[i][j].getOutput(layerOut[i]));
		}
		layerOut.append(neuronOut);
	}
	return layerOut;
}

QList<Neuron>& BpNetSt::operator[](int layer){
	Q_ASSERT(layer >= 0 && layer < net.length());
	return net[layer];
}

QString BpNetSt::toString() const{
	QString str = "Multilayer neural network (single thread implementation):";
	str += "\n\nInput layer: " + QString::number(inputCount) + " input neurons.\n";
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

BpNetSt::~BpNetSt(){}

}
