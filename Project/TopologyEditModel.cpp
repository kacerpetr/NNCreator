#include "TopologyEditModel.h"
#include "Parser/TopologyMdlParser.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

/**
 * Class constructor.
 */
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

/**
 * Class destructor.
 */
TopologyEditModel::~TopologyEditModel(){}

/**
 * Saves model to file.
 */
void TopologyEditModel::save(){
	TopologyMdlParser& parser = TopologyMdlParser::get();
	setSaved(parser.save(this));
}

/**
 * Randomizes weights of all neurons in neural network.
 */
void TopologyEditModel::randomizeWeights(){
	randomizeWeight(wgSeed, wgMin, wgMax);
	modelChanged(WeightChange);
	setSaved(false);
}

/**
 * Randomizes biases of all neurons in neural network.
 */
void TopologyEditModel::randomizeBiases(){
	randomizeBias(bsSeed, bsMin, bsMax);
	modelChanged(WeightChange);
	setSaved(false);
}

/**
 * Randomizes biases of all neurons in neural network.
 */
void TopologyEditModel::randomizeSlopes(){
    randomizeSlope(slpSeed, slpMin, slpMax);
    modelChanged(WeightChange);
    setSaved(false);
}

/**
 * Sets seed for random weight generation.
 */
void TopologyEditModel::setWeightSeed(int value){
	wgSeed = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Sets minimal random weight value.
 */
void TopologyEditModel::setWeightMin(double value){
	wgMin = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Sets maximal random weight value.
 */
void TopologyEditModel::setWeightMax(double value){
	wgMax = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Sets seed for random bias generation.
 */
void TopologyEditModel::setBiasSeed(int value){
	bsSeed = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Sets minimal random bias value.
 */
void TopologyEditModel::setBiasMin(double value){
	bsMin= value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Sets maximal random bias value.
 */
void TopologyEditModel::setBiasMax(double value){
	bsMax = value;
	modelChanged(NetParamChange);
	setSaved(false);
}

/**
 * Returns seed for random weight generation.
 */
int TopologyEditModel::weightSeed() const{
	return wgSeed;
}

/**
 * Returns minimal random weight value.
 */
double TopologyEditModel::weightMin() const{
	return wgMin;
}

/**
 * Returns maximal random weight value.
 */
double TopologyEditModel::weightMax() const{
	return wgMax;
}

/**
 * Returns seed for random bias generation.
 */
int TopologyEditModel::biasSeed() const{
	return bsSeed;
}

/**
 * Returns minimal random bias value.
 */
double TopologyEditModel::biasMin() const{
	return bsMin;
}

/**
 * Returns maximal random bias value.
 */
double TopologyEditModel::biasMax() const{
	return bsMax;
}

/**
 * Sets seed for random slope generation.
 */
void TopologyEditModel::setSlopeSeed(int value){
    slpSeed = value;
}

/**
 * Returns seed for random slope generation.
 */
int TopologyEditModel::slopeSeed() const{
    return slpSeed;
}

/**
 * Sets minimal random slope value.
 */
void TopologyEditModel::setSlopeMin(double value){
    slpMin = value;
}

/**
 * Returns minimal random slope value.
 */
double TopologyEditModel::slopeMin() const{
    return slpMin;
}

/**
 * Sets maximal random slope value.
 */
void TopologyEditModel::setSlopeMax(double value){
    slpMax = value;
}

/**
 * Returns maximal random slope value.
 */
double TopologyEditModel::slopeMax() const{
    return slpMax;
}

/**
 * Sets selected layer id.
 */
void TopologyEditModel::setSelectedLayer(int layer){
	this->layer = layer;
	setSaved(false);
}

/**
 * Returns selected layer's id.
 */
int TopologyEditModel::selectedLayer() const{
	return layer;
}

/**
 * Returns common transfer function of neurons.
 */
TransferFcn TopologyEditModel::transferFunction(){
	return (*this)[0][0].trFcn();
}

}
