#include "BaseModel.h"

namespace Project{

BaseModel::BaseModel(ModelType modelType) : mdlType(modelType), mdlSaved(false), mdlOpened(false){}

void BaseModel::setName(QString name){
	mdlName = name;
}

void BaseModel::setPath(QString path){
	mdlPath = path;
}

void BaseModel::setOpened(bool state){
	mdlOpened = state;
}

void BaseModel::setSaved(bool state){
	mdlSaved = state;
}

ModelType BaseModel::type() const{
	return mdlType;
}

QString BaseModel::name() const{
	return mdlName;
}

QString BaseModel::path() const{
	return mdlPath;
}

bool BaseModel::isSaved() const{
	return mdlSaved;
}

bool BaseModel::isOpened() const{
	return mdlOpened;
}

}
