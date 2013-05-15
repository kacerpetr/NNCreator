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

#include "BaseModel.h"
#include <QMessageBox>
#include <QDebug>

namespace ProjectData{

/**
 * Class constructor.
 */
BaseModel::BaseModel(ModelType modelType) :
	prj(NULL),
	mdlSaved(false),
	mdlOpened(false),
	mdlType(modelType),
	mdlName("unnamed")
{}

/**
 * Returns information about type of descendant.
 */
ModelType BaseModel::type() const{
	return mdlType;
}

/**
 * Sets name of model.
 */
void BaseModel::setName(QString name){
	mdlName = name;
}

/**
 * Returns name of model.
 */
QString BaseModel::name() const{
	return mdlName;
}

/**
 * Sets pointer to model's project.
 */
void BaseModel::setProject(Project* prj){
	Q_ASSERT(this->prj == NULL);
	Q_ASSERT(prj != NULL);
	this->prj = prj;

	connect(
		this->prj,
		SIGNAL(modelRenamed(QString, QString, ModelType)),
		this,
		SLOT(selectedModelRenamed(QString, QString, ModelType))
	);

	connect(
		this->prj,
		SIGNAL(modelDeleted(QString, ModelType)),
		this,
		SLOT(selectedModelDeleted(QString, ModelType))
	);
}

/**
 * Returns pointer to model's project.
 */
Project* BaseModel::project(){
	return prj;
}

/**
 * Sets project to opened or closed state.
 */
void BaseModel::setOpened(bool state){
	mdlOpened = state;
    if(state) emit opened(this);
}

/**
 * Checks if project is in opened or closed state.
 */
bool BaseModel::isOpened() const{
	return mdlOpened;
}

/**
 * Sets project to saved or unsaved state.
 */
void BaseModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

/**
 * Checks if project is in saved or unsaved state.
 */
bool BaseModel::isSaved() const{
	return mdlSaved;
}

/**
 * Returns absolute path to model file.
 */
QString BaseModel::pathName() const{
	Q_ASSERT(prj != NULL);
	return path() + "/" + fileName();
}

/**
 * Retruns file name of model.
 */
QString BaseModel::fileName() const{
	return mdlName + ".xml";
}

/**
 * Returns relative path to model file from model folder.
 */
QString BaseModel::relPathName() const{
	return folder() + "/" + fileName();
}

/**
 * Returns absolute path of folder where model will be saved.
 */
QString BaseModel::path() const{
	Q_ASSERT(prj != NULL);
	return projectPath() + "/" + folder();
}

/**
 * Returns absolute path of model's project folder.
 */
QString BaseModel::projectPath() const{
	Q_ASSERT(prj != NULL);
	return prj->path() + "/" + prj->getName();
}

/**
 * Returns name of folder of models with current model's type.
 */
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

/**
 * Sets new model name, renames model file end emits rename signal.
 */
void BaseModel::rename(QString name){
	bool succ = QFile::rename(pathName(), path() + "/" + name + ".xml");

	if(succ){
		QString oldName = mdlName;
		mdlName = name;
		save();
		prj->save();
		prj->emitModelRenamed(mdlName, oldName, mdlType);
		emit changed(ModelRenamed);
		return;
	}

	QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Rename"));
    msgBox.setText(tr("File can't be renamed."));
	msgBox.setInformativeText(pathName() + " -> " + path() + "/" + name + ".xml");
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
}

/**
 * Removes model from project and deletes its file.
 */
bool BaseModel::remove(){
	bool succ = QFile::remove(pathName());

	if(succ){
		prj->removeModel(this);
		return true;
	}
	else if(!QFile::exists(pathName())){
		prj->removeModel(this);
		return true;
	}

	QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Delete"));
    msgBox.setText(tr("File can't be deleted."));
	msgBox.setInformativeText(pathName());
	msgBox.setIcon(QMessageBox::Critical);
	msgBox.exec();
	return false;
}

/**
 * Returns list of other learningConfigModel names than this.
 */
QStringList BaseModel::otherPlot(){
    QStringList list;
    int count = prj->count(LearningConfig);
    for(int i = 0; i < count; i++){ 
        list.append(prj->getModel(i, LearningConfig)->name());
    }
    return list;
}

/**
 * Emits changed signal.
 */
void BaseModel::modelChanged(ChangeType type){
	emit changed(type);
	setSaved(false);
}

/**
 * Reloads current model, used for discarding changes when closing model.
 */
void BaseModel::reload(){
	prj->reloadModel(this);
}

///// selection of network or dataset, that are needed by some models to work /////

/**
 * Returns name of selected neural network.
 */
QString BaseModel::selectedNetworkName(){
	return selNet;
}

/**
 * Returns name of selected dataset.
 */
QString BaseModel::selectedDatasetName(){
	return selSet;
}

/**
 * Returns pointer of selected neural network.
 */
BaseModel* BaseModel::selectedNetwork(){
	Q_ASSERT(!selNet.isEmpty());
	Q_ASSERT(prj != NULL);
	return prj->getModel(selNet, TopologyEdit);
}

/**
 * Returns pointer of selected dataset.
 */
BaseModel* BaseModel::selectedDataset(){
	Q_ASSERT(!selSet.isEmpty());
	Q_ASSERT(prj != NULL);
	return prj->getModel(selSet, DatasetEdit);
}

/**
 * Selects network with given name.
 */
void BaseModel::selectNetwork(QString name){
	selNet = name;
	setSaved(false);
}

/**
 * Selects dataset with given name.
 */
void BaseModel::selectDataset(QString name){
	selSet = name;
	setSaved(false);
}

/**
 * Returns list of names of selectable neural networks.
 */
QStringList BaseModel::networkList(){
	Q_ASSERT(prj != NULL);

	QStringList lst;

	for(int i = 0; i < prj->count(TopologyEdit); i++){
		QString mdlName = prj->getModelName(i, TopologyEdit);
		if(!mdlName.isEmpty()) lst.append(mdlName);
	}

	return lst;
}

/**
 * Returns list of names of selectable datasets determined by selected network.
 */
QStringList BaseModel::datasetList(QString name){
	Q_ASSERT(prj != NULL);

	QList<BaseModel*> sets = prj->getRelatedDataset(name);
	QStringList lst;

	for(int i = 0; i < sets.length(); i++){
		lst.append(sets[i]->name());
	}

	return lst;
}

/**
 * Handles part of renaming process of selected model.
 */
void BaseModel::selectedModelRenamed(QString newName, QString oldName, ModelType type){
	if(type == DatasetEdit){
		if(selSet == oldName){
			selectDataset(newName);
			emit changed(SelectedDatasetRenamed);
		}
	}
	else if(type == TopologyEdit){
		if(selNet == oldName){
			selectNetwork(newName);
			emit changed(SelectedNetworkRenamed);
		}
	}
}

/**
 * Handles part of deleting process of selected model.
 */
void BaseModel::selectedModelDeleted(QString name, ModelType type){
	if(type == DatasetEdit){
		if(selSet == name){
			selectDataset(QString());
			emit changed(SelectedDatasetDeleted);
		}
	}
	else if(type == TopologyEdit){
		if(selNet == name){
			selectNetwork(QString());
			emit changed(SelectedNetworkDeleted);
		}
	}
}

}
