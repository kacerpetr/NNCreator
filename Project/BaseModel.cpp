#include "BaseModel.h"
#include <QMessageBox>
#include <QDebug>

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
	return path() + "/" + fileName();
}

QString BaseModel::fileName() const{
	return mdlName + ".xml";
}

QString BaseModel::relPathName() const{
	return folder() + "/" + fileName();
}

QString BaseModel::path() const{
	Q_ASSERT(prj != NULL);
	return projectPath() + "/" + folder();
}

QString BaseModel::projectPath() const{
	Q_ASSERT(prj != NULL);
	return prj->path() + "/" + prj->getName();
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

QStringList BaseModel::otherPlot(){
    QStringList list;
    int count = prj->count(LearningConfig);
    for(int i = 0; i < count; i++){ 
        list.append(prj->getModel(i, LearningConfig)->name());
    }
    return list;
}

void BaseModel::modelChanged(ChangeType type){
	emit changed(type);
	setSaved(false);
}

void BaseModel::reload(){
	prj->reloadModel(this);
}

///// selection of network or dataset, that are needed by some models to work /////

QString BaseModel::selectedNetworkName(){
	return selNet;
}

QString BaseModel::selectedDatasetName(){
	return selSet;
}

BaseModel* BaseModel::selectedNetwork(){
	Q_ASSERT(!selNet.isEmpty());
	Q_ASSERT(prj != NULL);
	return prj->getModel(selNet, TopologyEdit);
}

BaseModel* BaseModel::selectedDataset(){
	Q_ASSERT(!selSet.isEmpty());
	Q_ASSERT(prj != NULL);
	return prj->getModel(selSet, DatasetEdit);
}

void BaseModel::selectNetwork(QString name){
	selNet = name;
	setSaved(false);
}

void BaseModel::selectDataset(QString name){
	selSet = name;
	setSaved(false);
}

QStringList BaseModel::networkList(){
	Q_ASSERT(prj != NULL);

	QStringList lst;

	for(int i = 0; i < prj->count(TopologyEdit); i++){
		QString mdlName = prj->getModelName(i, TopologyEdit);
		if(!mdlName.isEmpty()) lst.append(mdlName);
	}

	return lst;
}

QStringList BaseModel::datasetList(QString name){
	Q_ASSERT(prj != NULL);

	QList<BaseModel*> sets = prj->getRelatedDataset(name);
	QStringList lst;

	for(int i = 0; i < sets.length(); i++){
		lst.append(sets[i]->name());
	}

	return lst;
}

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
