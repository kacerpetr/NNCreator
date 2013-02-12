#include "TopologyEditModel.h"
#include "Parsers/TopologyMdlParser.h"
using namespace Parsers;

namespace Project{

TopologyEditModel::TopologyEditModel() :
	BaseModel(TopologyEdit),
	wgMin(-0.5),
	wgMax(0.5),
	wgSeed(1),
	bsMin(-0.3),
	bsMax(0.3),
	bsSeed(1)
{}

void TopologyEditModel::save(){
	TopologyMdlParser& parser = TopologyMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void TopologyEditModel::duplicateLayer(int layer){
	net.duplicateLayer(layer);
}

void TopologyEditModel::removeLayer(int layer){
	net.removeLayer(layer);
}

void TopologyEditModel::appendLayer(){
	net.appendLayer();
}

void TopologyEditModel::setNeuronCount(int layer, int count){
	if(layer == -1) net.setInputCount(count);
	else net.setNeuronCount(layer, count);
}

int TopologyEditModel::weightCount(int layer){
	return net.weightCount(layer);
}

int TopologyEditModel::neuronCount(int layer){
	return net.neuronCount(layer);
}

QList<double> TopologyEditModel::weights(int layer, int neuron){
	return net[layer][neuron].weights();
}

int TopologyEditModel::inputCount(){
	return net.inputCount();
}

int TopologyEditModel::layerCount(){
	return net.layerCount();
}

void TopologyEditModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void TopologyEditModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

void TopologyEditModel::randomizeWeights(){
	net.randomizeWeight(wgSeed, wgMin, wgMax);
}

void TopologyEditModel::randomizeBias(){
	net.randomizeBias(bsSeed, bsMin, bsMax);
}

void TopologyEditModel::setWeightSeed(int value){
	wgSeed = value;
}

void TopologyEditModel::setWeightMin(double value){
	wgMin = value;
}

void TopologyEditModel::setWeightMax(double value){
	wgMax = value;
}

void TopologyEditModel::setBiasSeed(int value){
	bsSeed = value;
}

void TopologyEditModel::setBiasMin(double value){
	bsSeed = value;
}

void TopologyEditModel::setBiasMax(double value){
	bsMax = value;
}

int TopologyEditModel::weightSeed() const{
	return wgSeed;
}

double TopologyEditModel::weightMin() const{
	return wgMin;
}

double TopologyEditModel::weightMax() const{
	return wgMax;
}

int TopologyEditModel::biasSeed() const{
	return bsSeed;
}

double TopologyEditModel::biasMin() const{
	return bsMin;
}

double TopologyEditModel::biasMax() const{
	return bsMax;
}

int TopologyEditModel::weightCount() const{
	return net.weightCount();
}

int TopologyEditModel::neuronCount() const{
	return net.neuronCount();
}

int TopologyEditModel::outputCount() const{
	return net.outputCount();
}

}
