#include "Project.h"
#include "Parsers/ProjectParser.h"
using namespace Parsers;

namespace ProjectData{

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

BaseModel* Project::getModel(QString name, const ModelType type){
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->type() == type){
			if(name == model[i]->name()){
				return model[i];
			}
			count++;
		}
	}
	return NULL;
}

QList<DatasetEditModel*> Project::getRelatedDataset(QString networkName){
	BaseModel* netBase = getModel(networkName, TopologyEdit);
	TopologyEditModel* net = (TopologyEditModel*)netBase;

	QList<DatasetEditModel*> list;
	if(net == NULL) return list;

	for(int i = 0; i < count(DatasetEdit); i++){
		BaseModel* setBase = getModel(i, DatasetEdit);
		DatasetEditModel* set = (DatasetEditModel*)setBase;

		if(net->inputCount() == set->inputCount() && net->outputCount() == set->outputCount()){
			list.append(set);
		}
	}

	return list;
}

BaseModel* Project::lastModel(){
	return model.last();
}

void Project::createModel(QString name, ModelType type){
	switch(type){
		case DatasetEdit:{
			DatasetEditModel* mdl = new DatasetEditModel();
			mdl->setName(name);
			mdl->setPath(name);
			mdl->setProjectPath(path);
			model.append(mdl);
			break;
		}
		case TopologyEdit:{
			TopologyEditModel* mdl = new TopologyEditModel();
			mdl->setName(name);
			mdl->setPath(name);
			mdl->setProjectPath(path);
			model.append(mdl);
			break;
		}
		case LearningConfig:{
			LearningConfigModel* mdl = new LearningConfigModel();
			mdl->setProject(this);
			mdl->setName(name);
			mdl->setPath(name);
			mdl->setProjectPath(path);
			model.append(mdl);
			break;
		}
		case DatasetTest:{
			DatasetTestModel* mdl = new DatasetTestModel();
			mdl->setName(name);
			mdl->setPath(name);
			mdl->setProjectPath(path);
			model.append(mdl);
			break;
		}
		case GraphTest:{
			GraphTestModel* mdl = new GraphTestModel();
			mdl->setName(name);
			mdl->setPath(name);
			mdl->setProjectPath(path);
			model.append(mdl);
			break;
		}
	}
	model.last()->setName(name);
	save();
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

int Project::count() const{
	return model.length();
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

QList<BaseModel*> Project::unsavedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < model.length(); i++){
		if(!model[i]->isSaved()) res.append(model[i]);
	}
	return res;
}

void Project::save(){
	ProjectParser& pp = ProjectParser::get();
	pp.save(this);
}

}
