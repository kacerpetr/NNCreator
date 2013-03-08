#include <QIcon>
#include <QFont>
#include "Workspace.h"
#include <QDebug>
#include "Parser/ProjectParser.h"
#include <QDir>
#include <QMessageBox>
#include "Util/Settings.h"
using namespace Parser;
using namespace Util;

namespace ProjectData{

Workspace::Workspace(QObject* parent) : QAbstractItemModel(parent){

}

Workspace::~Workspace(){
	// TODO !!!
}

////////////////////////////////////////////////////////////////
//////// AbstractItemModel methods /////////////////////////////
////////////////////////////////////////////////////////////////

QVariant Workspace::data(const QModelIndex &index, int role) const{
	if (!index.isValid()) return QVariant();

	switch(role){
		case Qt::DisplayRole:
			//project name
			if(isProjectIndex(index)){
				return prj[index.internalId()-1]->getName();
			}
			//item category name
			else if(isCategoryIndex(index)){
				switch(getCategoryId(index)){
					case DatasetEdit:
						return "Datasets";
					case TopologyEdit:
						return "Neural networks";
					case LearningConfig:
						return "Learning configurations";
					case DatasetTest:
						return "Dataset test";
					case GraphTest:
						return "Graph test";
				}
			}
			//model name
			else{
				ModelType mdlType = (ModelType)getCategoryId(index);
				BaseModel* mdl = prj[getProjectId(index)]->getModel(getItemId(index), mdlType);
				return QVariant(mdl->name());
			}

		case Qt::DecorationRole:
			if(isCategoryIndex(index)){
				switch(getCategoryId(index)){
					case DatasetEdit:
						return QVariant(QIcon(":datasetIcon32"));
					case TopologyEdit:
						return QVariant(QIcon(":topologyIcon32"));
					case LearningConfig:
						return QVariant(QIcon(":learningIcon32"));
					case DatasetTest:
						return QVariant(QIcon(":datasetTestIcon32"));
					case GraphTest:
						return QVariant(QIcon(":testingIcon32"));
				}
			}
			return QVariant();

		case Qt::FontRole:
			//project name font
			if(isProjectIndex(index)){
				QFont font;
				font.setBold(true);
				return QVariant(font);
			}
			//project category font
			else if(isCategoryIndex(index)){
				QFont font;
				font.setItalic(true);
				return QVariant(font);
			}
			//item name font
			else{
				return QVariant(QFont());
			}

		default:
			return QVariant();
	}
}

QModelIndex Workspace::index(int row, int column, const QModelIndex &parent) const{
	if(!parent.isValid()){
		return createIndex(row, column, row+1);
	}
	else if(isProjectIndex(parent)){
		return createIndex(row, column, (int)(parent.internalId()+10000*(row+1)));
	}
	else if(isCategoryIndex(parent)){
		return createIndex(row, column, (int)(parent.internalId()+100000*(row+1)));
	}
	return QModelIndex();
}

QModelIndex Workspace::parent(const QModelIndex &index) const{
	if(!index.isValid()){
		return QModelIndex();
	}
	else if(isProjectIndex(index)){
		return QModelIndex();
	}
	else if(isCategoryIndex(index)){
		return createIndex((int)(index.internalId()%10000)-1, 0, (int)(index.internalId()%10000));
	}
	else if(isItemIndex(index)){
		return createIndex((int)(index.internalId()%100000)/10000-1, 0, (int)(index.internalId()%100000));
	}
	return QModelIndex();
}

int Workspace::rowCount(const QModelIndex &parent) const{
	if(!parent.isValid()){
		return prj.length();
	}
	else if(isProjectIndex(parent)){
		return 5;
	}
	else if(isCategoryIndex(parent)){
		switch(getCategoryId(parent)){
			case DatasetEdit:
				return prj[getProjectId(parent)]->count(DatasetEdit);
			case TopologyEdit:
				return prj[getProjectId(parent)]->count(TopologyEdit);
			case LearningConfig:
				return prj[getProjectId(parent)]->count(LearningConfig);
			case DatasetTest:
				return prj[getProjectId(parent)]->count(DatasetTest);
			case GraphTest:
				return prj[getProjectId(parent)]->count(GraphTest);
		}
	}
	return 0;
}

int Workspace::columnCount(const QModelIndex &parent) const{
	if(!parent.isValid()) return 1;
	return 1;
}

////////////////////////////////////////////////////////////////
//////// Workspace management methods //////////////////////////
////////////////////////////////////////////////////////////////

void Workspace::createProject(QString path, QString name){
	Project *project = new Project(path, name);
	if(project->save()){
		prj.append(project);
		Settings& settings = Settings::get();
		settings.registerProject(project->getName(), project->path() + project->getName() + "/project.xml");
	}
	emit layoutChanged();
}

void Workspace::createDataset(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, DatasetEdit);
	emit layoutChanged();
}

void Workspace::createNeuralNetwork(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, TopologyEdit);
	emit layoutChanged();
}

void Workspace::createLearningConfig(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, LearningConfig);
	emit layoutChanged();
}

void Workspace::createDatasetTest(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, DatasetTest);
	emit layoutChanged();
}

void Workspace::createGraphTest(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, GraphTest);
	emit layoutChanged();
}

BaseModel* Workspace::getModel(const QModelIndex& index){
	return prj[getProjectId(index)]->getModel(getItemId(index), (ModelType)getCategoryId(index));
}

QList<BaseModel*> Workspace::getOpenedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < prj.length(); i++){
		res.append(prj[i]->getOpenedItems());
	}
	return res;
}

QList<BaseModel*> Workspace::unsavedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < prj.length(); i++){
		res.append(prj[i]->unsavedItems());
	}
	return res;
}

BaseModel* Workspace::firstOpened(){
	QList<BaseModel*> list = getOpenedItems();
	if(list.isEmpty()) return NULL;
	return list.first();
}

bool Workspace::openProject(QString file){
	Q_ASSERT(!file.isEmpty());
	ProjectParser& pp = ProjectParser::get();
	Project* project = pp.load(file);
	if(project != NULL){
		Settings& settings = Settings::get();
		settings.registerProject(project->getName(), project->path() + "/" + project->getName() + "/project.xml");
		prj.append(project);
		emit layoutChanged();
		return true;
	}else{
		emit layoutChanged();
		return false;
	}
}

Project* Workspace::project(QModelIndex& index){
	if(isProjectIndex(index))
		return prj[getProjectId(index)];
	return NULL;
}

void Workspace::closeProject(QModelIndex& index){
	if(isProjectIndex(index)){
		if(prj.length() == 1) prj.clear();
		else prj.removeAt(getProjectId(index));
		emit layoutChanged();
	}
}

void Workspace::removeModel(QModelIndex& index){
	BaseModel* mdl = getModel(index);
	Q_ASSERT(mdl != NULL);
	if(mdl->remove()) delete mdl;
	emit layoutChanged();
}

////////////////////////////////////////////////////////////////
//////// Static Metods /////////////////////////////////////////
////////////////////////////////////////////////////////////////

bool Workspace::isProjectIndex(const QModelIndex& index){
	return index.internalId() >= 1 && index.internalId() < 10000;
}

bool Workspace::isCategoryIndex(const QModelIndex& index){
	return index.internalId() >= 10001 && index.internalId() < 110001;
}

bool Workspace::isItemIndex(const QModelIndex& index){
	return index.internalId() >= 110001;
}

int Workspace::getProjectId(const QModelIndex& index){
	return index.internalId() % 10000 - 1;
}

int Workspace::getCategoryId(const QModelIndex& index){
	return (index.internalId() % 100000) / 10000 - 1;
}

int Workspace::getItemId(const QModelIndex& index){
	return index.internalId() / 100000 - 1;
}

}
