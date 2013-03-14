#include "TopologyEditModel.h"
#include "Parser/TopologyMdlParser.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

TopologyEditModel::TopologyEditModel() :
	BaseModel(TopologyEdit),
    wgSeed(-46814),
	wgMin(-0.5),
	wgMax(0.5),
    bsSeed(4452687),
	bsMin(-0.3),
	bsMax(0.3),
    slpSeed(964874),
    slpMin(0.5),
    slpMax(1),
	layer(1)
{}

TopologyEditModel::~TopologyEditModel(){}

void TopologyEditModel::save(){
	TopologyMdlParser& parser = TopologyMdlParser::get();
	setSaved(parser.save(this));
}

void TopologyEditModel::randomizeWeights(){
	randomizeWeight(wgSeed, wgMin, wgMax);
	modelChanged(WeightChange);
	setSaved(false);
}

void TopologyEditModel::randomizeBiases(){
	randomizeBias(bsSeed, bsMin, bsMax);
	modelChanged(WeightChange);
	setSaved(false);
}

void TopologyEditModel::randomizeSlopes(){
    randomizeSlope(slpSeed, slpMin, slpMax);
    modelChanged(WeightChange);
    setSaved(false);
}

void TopologyEditModel::setWeightSeed(int value){
	wgSeed = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

void TopologyEditModel::setWeightMin(double value){
	wgMin = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

void TopologyEditModel::setWeightMax(double value){
	wgMax = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

void TopologyEditModel::setBiasSeed(int value){
	bsSeed = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

void TopologyEditModel::setBiasMin(double value){
	bsMin= value;
	modelChanged(NetParamChange);
	setSaved(false);
}

void TopologyEditModel::setBiasMax(double value){
	bsMax = value;
	modelChanged(NetParamChange);
	setSaved(false);
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

void TopologyEditModel::setSlopeSeed(int value){
    slpSeed = value;
}

int TopologyEditModel::slopeSeed() const{
    return slpSeed;
}

void TopologyEditModel::setSlopeMin(double value){
    slpMin = value;
}

double TopologyEditModel::slopeMin() const{
    return slpMin;
}

void TopologyEditModel::setSlopeMax(double value){
    slpMax = value;
}

double TopologyEditModel::slopeMax() const{
    return slpMax;
}

void TopologyEditModel::setSelectedLayer(int layer){
	this->layer = layer;
	setSaved(false);
}

int TopologyEditModel::selectedLayer() const{
	return layer;
}

TransferFcn TopologyEditModel::transferFunction(){
	return (*this)[0][0].trFcn();
}

}
