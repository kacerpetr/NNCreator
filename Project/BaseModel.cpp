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
	return folder() + "/" + mdlPath + ".xml";
}

QString BaseModel::folder() const{
	QString path;
	switch(mdlType){
		case DatasetEdit:
			path = "Dataset";
			break;

		case TopologyEdit:
			path = "Network";
			break;

		case LearningConfig:
			path = "Learning";
			break;

		case DatasetTest:
			path = "DatasetTest";
			break;

		case GraphTest:
			path = "GraphTest";
			break;

		default:
			path = "unknown";
	}
	return path;
}

bool BaseModel::isSaved() const{
	return mdlSaved;
}

bool BaseModel::isOpened() const{
	return mdlOpened;
}

}
