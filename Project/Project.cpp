#include "Project.h"
#include "Parsers/XmlFactory.h"
using namespace Parsers;

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
		if(model[i]->type() == type){
			if(index == count){
				return model[i];
			}
			count++;
		}
	}
	return NULL;
}

BaseModel* Project::lastModel(){
	return model.last();
}

void Project::createModel(QString name, QString path, ModelType type){
	switch(type){
		case DatasetEdit:{
			DatasetEditModel* mdl = new DatasetEditModel();
			mdl->setName(name);
			mdl->setPath(path);
			model.append(mdl);
			break;
		}
		case TopologyEdit:{
			TopologyEditModel* mdl = new TopologyEditModel();
			mdl->setName(name);
			mdl->setPath(path);
			model.append(mdl);
			break;
		}
		case LearningConfig:{
			LearningConfigModel* mdl = new LearningConfigModel();
			mdl->setName(name);
			mdl->setPath(path);
			model.append(mdl);
			break;
		}
		case DatasetTest:{
			DatasetTestModel* mdl = new DatasetTestModel();
			mdl->setName(name);
			mdl->setPath(path);
			model.append(mdl);
			break;
		}
		case GraphTest:{
			GraphTestModel* mdl = new GraphTestModel();
			mdl->setName(name);
			mdl->setPath(path);
			model.append(mdl);
			break;
		}
	}
	model.last()->setName(name);
}

void Project::removeModel(int index){

}

int Project::count(const ModelType type) const{
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->type() == type) count++;
	}
	return count;
}

QString Project::getModelName(int index, const ModelType type) const{
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->type() == type){
			if(index == count) return model[i]->name();
			count++;
		}
	}
	return QString("");
}

QList<BaseModel*> Project::getOpenedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->isOpened()) res.append(model[i]);
	}
	return res;
}

}
