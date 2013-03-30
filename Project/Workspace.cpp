#include <QIcon>
#include <QFont>
#include "Workspace.h"
#include <QDebug>
#include "Parser/ProjectParser.h"
#include <QDir>
#include <QMessageBox>
#include "Util/Settings.h"
using namespace Parser;

namespace ProjectData{

/**
 * Class constructor.
 */
Workspace::Workspace(QObject* parent) : QAbstractItemModel(parent){

}

/**
 * Class destructor.
 */
Workspace::~Workspace(){
    for(int i = 0; i < prj.length(); i++){
        delete prj[i];
    }
}

////////////////////////////////////////////////////////////////
//////// AbstractItemModel methods /////////////////////////////
////////////////////////////////////////////////////////////////

/**
 * Returns the data stored under the given role for the item referred to by the index.
 */
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
                        return tr("Datasets");
					case TopologyEdit:
                        return tr("Neural networks");
					case LearningConfig:
                        return tr("Learning configurations");
					case DatasetTest:
                        return tr("Dataset tests");
					case GraphTest:
                        return tr("Graph tests");
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

/**
 * Returns the index of the item in the model specified by the given row, column and parent index.
 */
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

/**
 * Returns the parent of the model item with the given index.
 */
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

/**
 * Returns the number of rows under the given parent.
 */
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

/**
 * Returns the number of columns for the children of the given parent.
 */
int Workspace::columnCount(const QModelIndex &parent) const{
	if(!parent.isValid()) return 1;
	return 1;
}

////////////////////////////////////////////////////////////////
//////// Workspace management methods //////////////////////////
////////////////////////////////////////////////////////////////

/**
 * Creates new empty project of given name at given path.
 */
void Workspace::createProject(QString path, QString name){
	Project *project = new Project(path, name);
	if(project->save()){
		prj.append(project);
		Settings& settings = Settings::get();
		settings.registerProject(project->getName(), project->path() + project->getName() + "/project.xml");
	}
	emit layoutChanged();
}

/**
 * Creates new dataset in project given by model index.
 */
void Workspace::createDataset(const QModelIndex& index, QString name){
    prj[getProjectId(index)]->createModel(name, DatasetEdit);
    emit layoutChanged();
}

/**
 * Creates new neural network in project given by model index.
 */
void Workspace::createNeuralNetwork(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, TopologyEdit);
	emit layoutChanged();
}

/**
 * Creates new learning configuration in project given by model index.
 */
void Workspace::createLearningConfig(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, LearningConfig);
	emit layoutChanged();
}

/**
 * Creates new dataset test in project given by model index.
 */
void Workspace::createDatasetTest(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, DatasetTest);
	emit layoutChanged();
}

/**
 * Creates new graph test in project given by model index.
 */
void Workspace::createGraphTest(const QModelIndex& index, QString name){
	prj[getProjectId(index)]->createModel(name, GraphTest);
	emit layoutChanged();
}

/**
 * Returns model determined by given model index.
 */
BaseModel* Workspace::getModel(const QModelIndex& index){
	return prj[getProjectId(index)]->getModel(getItemId(index), (ModelType)getCategoryId(index));
}

/**
 * Returns list of opened items.
 */
QList<BaseModel*> Workspace::getOpenedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < prj.length(); i++){
		res.append(prj[i]->getOpenedItems());
	}
	return res;
}

/**
 * Returns list of unsaved items.
 */
QList<BaseModel*> Workspace::unsavedItems(){
	QList<BaseModel*> res;
	for(int i = 0; i < prj.length(); i++){
		res.append(prj[i]->unsavedItems());
	}
	return res;
}

/**
 * Returns model first at list of opened models.
 */
BaseModel* Workspace::firstOpened(){
	QList<BaseModel*> list = getOpenedItems();
	if(list.isEmpty()) return NULL;
	return list.first();
}

/**
 * Opens given project file.
 */
bool Workspace::openProject(QString file){
	Q_ASSERT(!file.isEmpty());

    for(int i = 0; i < prj.length(); i++){
        if(file == prj[i]->path()+"/"+prj[i]->getName()+"/project.xml"){
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Open project"));
            msgBox.setText(tr("Project is already opened !!!"));
            msgBox.setInformativeText(file);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return true;
        }
    }

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

/**
 * Returns pointer to project with given model index.
 */
Project* Workspace::project(QModelIndex& index){
	if(isProjectIndex(index))
		return prj[getProjectId(index)];
	return NULL;
}

/**
 * Closes project with given project index.
 */
void Workspace::closeProject(QModelIndex& index){
	if(isProjectIndex(index)){
		if(prj.length() == 1) prj.clear();
		else prj.removeAt(getProjectId(index));
		emit layoutChanged();
	}
}

/**
 * Removes model with given index.
 */
void Workspace::removeModel(QModelIndex& index){
	BaseModel* mdl = getModel(index);
	Q_ASSERT(mdl != NULL);
	if(mdl->remove()) delete mdl;
	emit layoutChanged();
}

/**
 * Reloads model with given index.
 */
void Workspace::reloadModel(BaseModel* mdl){
	mdl->reload();
	emit layoutChanged();
}

////////////////////////////////////////////////////////////////
//////// Static metods /////////////////////////////////////////
////////////////////////////////////////////////////////////////

/**
 * Returns true if index is index of project.
 */
bool Workspace::isProjectIndex(const QModelIndex& index){
	return index.internalId() >= 1 && index.internalId() < 10000;
}

/**
 * Returns true if index is index of model category.
 */
bool Workspace::isCategoryIndex(const QModelIndex& index){
	return index.internalId() >= 10001 && index.internalId() < 110001;
}

/**
 * Returns true if index is index of model.
 */
bool Workspace::isItemIndex(const QModelIndex& index){
	return index.internalId() >= 110001;
}

/**
 * Returns id of project calculated from index internalId.
 */
int Workspace::getProjectId(const QModelIndex& index){
	return index.internalId() % 10000 - 1;
}

/**
 * Returns id of model category calculated from index internalId.
 */
int Workspace::getCategoryId(const QModelIndex& index){
	return (index.internalId() % 100000) / 10000 - 1;
}

/**
 * Returns id of model calculated from index internalId.
 */
int Workspace::getItemId(const QModelIndex& index){
	return index.internalId() / 100000 - 1;
}

}
