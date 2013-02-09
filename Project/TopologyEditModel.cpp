#include "TopologyEditModel.h"

namespace Project{

TopologyEditModel::TopologyEditModel() : BaseModel(TopologyEdit){}

void TopologyEditModel::save(){
	mdlSaved = true;
}

void TopologyEditModel::duplicateLayer(int layer){

}

void TopologyEditModel::removeLayer(int layer){

}

void TopologyEditModel::appendLayer(){

}

void TopologyEditModel::setNeuronCount(int layer, int count){

}

int TopologyEditModel::neuronCount(int layer){

}

void TopologyEditModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void TopologyEditModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}


}
