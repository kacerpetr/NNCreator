#include "BaseModel.h"

namespace Project{

BaseModel::BaseModel(ModelType modelType) : mdlType(modelType){}

ModelType BaseModel::getModelType() const{
	return mdlType;
}

QString BaseModel::getName() const{
	return mdlName;
}

void BaseModel::setName(QString name){
	mdlName = name;
}

bool BaseModel::isSaved() const{
	return mdlSaved;
}

void BaseModel::setSaved(bool saved){
	mdlSaved = saved;
}

}
