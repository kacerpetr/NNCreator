#include "BaseModel.h"

namespace ProjectData{

BaseModel::BaseModel(ModelType modelType) :
	prj(NULL),
	mdlSaved(false),
	mdlOpened(false),
	mdlType(modelType),
	mdlName("unnamed")
{}

ModelType BaseModel::type() const{
	return mdlType;
}

void BaseModel::setName(QString name){
	mdlName = name;
}

QString BaseModel::name() const{
	return mdlName;
}

void BaseModel::setProject(Project* prj){
	this->prj = prj;
}

Project* BaseModel::project(){
	return prj;
}

void BaseModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

bool BaseModel::isOpened() const{
	return mdlOpened;
}

void BaseModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

bool BaseModel::isSaved() const{
	return mdlSaved;
}

QString BaseModel::pathName() const{
	Q_ASSERT(prj != NULL);
	return prj->path() + "/"  + folder() + "/" + fileName();
}

QString BaseModel::fileName() const{
	return mdlName + ".xml";
}

QString BaseModel::relPathName() const{
	return folder() + "/" + fileName();
}

QString BaseModel::path() const{
	Q_ASSERT(prj != NULL);
	return prj->path() + "/"  + folder();
}

QString BaseModel::projectPath() const{
	Q_ASSERT(prj != NULL);
	return prj->path();
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


void BaseModel::modelChanged(ChangeType changeType){
	emit changed(changeType);
}

}
