#include "Project.h"

namespace Project{

Project::Project() : path(QString()), name(QString()){}

Project::Project(QString path, QString name) : path(path), name(name){}

Project::~Project(){
	for(int i = 0; i < model.length(); i++) delete model[i];
}

QString Project::getName() const{
	return name;
}

QString Project::getPath() const{
	return path;
}

void Project::setName(QString name){
	this->name = name;
}

void Project::setPath(QString path){
	this->path = path;
}

BaseModel* Project::getModel(int index){
	return model[index];
}

BaseModel* Project::getModel(int index, const ModelType type){
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->getModelType() == type){
			if(index == count) return model[i];
			count++;
		}
	}
	return NULL;
}

void Project::createModel(QString name, ModelType type){
	switch(type){
		case DatasetEdit:
			model.append(new DatasetEditModel());
			break;

		case TopologyEdit:
			model.append(new TopologyEditModel());
			break;

		case LearningConfig:
			model.append(new LearningConfigModel());
			break;

		case DatasetTest:
			model.append(new DatasetTestModel());
			break;

		case GraphTest:
			model.append(new GraphTestModel());
			break;
	}
	model.last()->setName(name);
}

void Project::removeModel(int index){

}

int Project::count(const ModelType type) const{
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->getModelType() == type) count++;
	}
	return count;
}

QString Project::getModelName(int index, const ModelType type) const{
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->getModelType() == type){
			if(index == count) return model[i]->getName();
			count++;
		}
	}
	return QString("");
}

}
