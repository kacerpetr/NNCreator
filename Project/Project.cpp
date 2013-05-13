/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Project.h"
#include "Parser/ProjectParser.h"
#include "Parser/DatasetMdlParser.h"
#include "Parser/TopologyMdlParser.h"
#include "Parser/LrnConfMdlParser.h"
#include "Parser/DatasetTestMdlParser.h"
#include "Parser/GraphTestMdlParser.h"
#include <QDebug>
#include <QMessageBox>
using namespace Parser;

namespace ProjectData{

/**
 * Class constructor.
 */
Project::Project() : name(QString()), pathVal(QString()){}

/**
 * Class constructor that sets project path nad name.
 */
Project::Project(QString path, QString name) : pathVal(path), name(name){}

/**
 * Class destructor.
 */
Project::~Project(){
	for(int i = 0; i < model.length(); i++) delete model[i];
}

/**
 * Returns name of project.
 */
QString Project::getName() const{
	return name;
}

/**
 * Returns path of project.
 */
QString Project::path() const{
	return pathVal;
}

/**
 * Returns name of project.
 */
void Project::setName(QString name){
	this->name = name;
}

/**
 * Sets path of project.
 */
void Project::setPath(QString path){
	this->pathVal = path;
}

/**
 * Returns model at given index.
 */
BaseModel* Project::getModel(int index){
	return model[index];
}

/**
 * Returns model at given index from imaginary array with models of same type.
 */
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

/**
 * Returns model with given name and type or NULL when model does not exist.
 */
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

/**
 * Returns list of datasets that can be used for network with given name.
 */
QList<BaseModel*> Project::getRelatedDataset(QString networkName){
	BaseModel* netBase = getModel(networkName, TopologyEdit);
	TopologyEditModel* net = (TopologyEditModel*)netBase;

	QList<BaseModel*> list;
	if(net == NULL) return list;

	for(int i = 0; i < count(DatasetEdit); i++){
		BaseModel* setBase = getModel(i, DatasetEdit);
		DatasetEditModel* set = (DatasetEditModel*)setBase;

		if(net->inputCount() == set->minInputCount() && net->outputCount() == set->minOutputCount()){
			list.append(set);
		}
	}

	return list;
}

/**
 * Returns pointer to last created model.
 */
BaseModel* Project::lastModel(){
	return model.last();
}

/**
 * Creates new model of given name and type.
 */
void Project::createModel(QString name, ModelType type){
	BaseModel* mdl = NULL;

	switch(type){
		case DatasetEdit:{
			mdl = new DatasetEditModel();
			break;
		}
		case TopologyEdit:{
			mdl = new TopologyEditModel();
			break;
		}
		case LearningConfig:{
			mdl = new LearningConfigModel();
			break;
		}
		case DatasetTest:{
			mdl = new DatasetTestModel();
			break;
		}
		case GraphTest:{
			mdl = new GraphTestModel();
			break;
		}
	}

	mdl->setName(name);
	mdl->setProject(this);

    BaseModel* mod = getModel(name, type);
    if(mod != NULL){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Create new item"));
        msgBox.setText(tr("Project item can't be created."));
        msgBox.setInformativeText(tr("Name '") + name + tr("' already exists in project."));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

	model.append(mdl);
	mdl->save();
	save();
}

/**
 * Duplicates datasetEdit model.
 */
void Project::duplicateModel(int index, QString copyName, ModelType type){
    if(type != DatasetEdit) return;

    BaseModel* mdl = getModel(index, type);
    DatasetEditModel* daem = (DatasetEditModel*)mdl;
    DatasetEditModel* copyof = new DatasetEditModel(daem);

    BaseModel* mod = getModel(copyName, type);
    if(mod != NULL){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Duplicate dataset"));
        msgBox.setText(tr("Dataset can't be created."));
        msgBox.setInformativeText(tr("Name '") + name + tr("' already exists in project."));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    copyof->setName(copyName);
    copyof->setProject(this);
    model.append(copyof);
    copyof->save();
    save();
}

/**
 * Returns count of models of given type.
 */
int Project::count(const ModelType type) const{
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->type() == type) count++;
	}
	return count;
}

/**
 * Returns count of all models in project.
 */
int Project::count() const{
	return model.length();
}

/**
 * Returns name of model of given type at given index.
 */
QString Project::getModelName(int index, const ModelType type) const{
	Q_ASSERT(index >= 0 && index < model.length());
	int count = 0;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->type() == type){
			if(index == count) return model[i]->name();
			count++;
		}
	}
	return QString();
}

/**
 * Returns list of opened models.
 */
QList<BaseModel*> Project::getOpenedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < model.length(); i++){
		if(model[i]->isOpened()) res.append(model[i]);
	}
	return res;
}

/**
 * Returns list of unsaved models.
 */
QList<BaseModel*> Project::unsavedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < model.length(); i++){
		if(!model[i]->isSaved()) res.append(model[i]);
	}
	return res;
}

/**
 * Opens model of given type at given path.
 */
void Project::openModel(QString path, ModelType type){
	BaseModel* mdl = NULL;

	QString fullPath = this->pathVal + "/" + this->name +"/"+ path;

	switch(type){
		case DatasetEdit:{
			DatasetMdlParser& parser = DatasetMdlParser::get();
			mdl = parser.load(fullPath);
			break;
		}
		case TopologyEdit:{
			TopologyMdlParser& parser = TopologyMdlParser::get();
			mdl = parser.load(fullPath);
			break;
		}
		case LearningConfig:{
			LrnConfMdlParser& parser = LrnConfMdlParser::get();
			mdl = parser.load(fullPath);
			break;
		}
		case DatasetTest:{
			DatasetTestMdlParser& parser = DatasetTestMdlParser::get();
			mdl = parser.load(fullPath);
			break;
		}
		case GraphTest:{
			GraphTestMdlParser& parser = GraphTestMdlParser::get();
			mdl = parser.load(fullPath);
			break;
		}
	}

	if(mdl != NULL){
		mdl->setProject(this);
		model.append(mdl);
		mdl->setSaved(true);
	}
}

/**
 * Saves project (models will not be saved).
 */
bool Project::save(){
	ProjectParser& pp = ProjectParser::get();
	return pp.save(this);
}

/**
 * Emited by BaseModel when its name is changed.
 */
void Project::emitModelRenamed(QString newName, QString oldName, ModelType type){
	emit modelRenamed(newName, oldName, type);
}

/**
 * Removes model and emits relevant signal.
 */
void Project::removeModel(BaseModel* mdl){
	Q_ASSERT(mdl != NULL);
	model.removeOne(mdl);
	emit modelDeleted(mdl->name(), mdl->type());
	save();
}

/**
 * Reloads model from file.
 */
void Project::reloadModel(BaseModel* mdl){
	Q_ASSERT(mdl != NULL);
	QString path = mdl->relPathName();
	ModelType type = mdl->type();
	model.removeOne(mdl);
	delete mdl;
	openModel(path, type);
}

}
