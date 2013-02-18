#include "BaseModel.h"

namespace ProjectData{

BaseModel::BaseModel(ModelType modelType) : mdlType(modelType), mdlSaved(false), mdlOpened(false){}

void BaseModel::setName(QString name){
	mdlName = name;
}

void BaseModel::setOpened(bool state){
	mdlOpened = state;
}

void BaseModel::setSaved(bool state){
	mdlSaved = state;
}

void BaseModel::setProjectPath(QString path){
	prjPath = path;
}

QString BaseModel::projectPath(){
	return prjPath;
}

ModelType BaseModel::type() const{
	return mdlType;
}

QString BaseModel::name() const{
	return mdlName;
}

QString BaseModel::path() const{
	return folder() + "/" + mdlName + ".xml";
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
