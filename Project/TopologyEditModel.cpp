#include "TopologyEditModel.h"
#include "Parser/TopologyMdlParser.h"
using namespace Parser;

namespace ProjectData{

TopologyEditModel::TopologyEditModel() :
	BaseModel(TopologyEdit),
	wgSeed(1),
	wgMin(-0.5),
	wgMax(0.5),
	bsSeed(1),
	bsMin(-0.3),
	bsMax(0.3)
{}

TopologyEditModel::~TopologyEditModel(){}

void TopologyEditModel::save(){
	TopologyMdlParser& parser = TopologyMdlParser::get();
	setSaved(parser.save(this));
}

void TopologyEditModel::randomizeWeights(){
	randomizeWeight(wgSeed, wgMin, wgMax);
}

void TopologyEditModel::randomizeBiases(){
	randomizeBias(bsSeed, bsMin, bsMax);
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

}
