#include "GraphTestModel.h"

namespace Project{

GraphTestModel::GraphTestModel() : BaseModel(GraphTest){}

void GraphTestModel::save(){
	setSaved(true);
}

void GraphTestModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void GraphTestModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

}
