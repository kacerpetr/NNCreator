#include <QIcon>
#include <QFont>
#include "Workspace.h"
#include <QDebug>

namespace Project{

Workspace::Workspace(QObject* parent) : QAbstractItemModel(parent){

}

Workspace::~Workspace(){

}

////////////////////////////////////////////////////////////////
//////// AbstractItemModel methods /////////////////////////////
////////////////////////////////////////////////////////////////

QVariant Workspace::data(const QModelIndex &index, int role) const{
	if (!index.isValid()) return QVariant();

	switch(role){
		case Qt::DisplayRole:
			if(index.internalId() < 10000){
				return project[index.internalId()-1].getName();
			}else if(index.internalId() >= 10000 && index.internalId() < 100000){
				switch((int)(index.internalId()/10000)){
					case 1:
						return "Training patterns";
					case 2:
						return "Neural networks";
					case 3:
						return "Learning configurations";
					case 4:
						return "Testing scenarios";
				}
			}else{
				switch((int)((index.internalId()%100000)/10000)){
					case 1:
						return project[index.internalId()%10000-1].getTrainingPatternName(index.internalId()/100000-1);
					case 2:
						return project[index.internalId()%10000-1].getNeuralNetworkName(index.internalId()/100000-1);
					case 3:
						return project[index.internalId()%10000-1].getLearningConfigName(index.internalId()/100000-1);
					case 4:
						return project[index.internalId()%10000-1].getTestingScenarioName(index.internalId()/100000-1);
				}
			}

		case Qt::DecorationRole:
			if(index.internalId() >= 10000 && index.internalId() < 100000){
				switch((int)(index.internalId()/10000)){
					case 1:
						return QVariant(QIcon(":trainingPatternIcon32"));
					case 2:
						return QVariant(QIcon(":topologyIcon32"));
					case 3:
						return QVariant(QIcon(":learningIcon32"));
					case 4:
						return QVariant(QIcon(":testingIcon32"));
				}
			}
			return QVariant();

		case Qt::FontRole:
			if(index.internalId() < 10000){
				QFont font;
				font.setBold(true);
				return QVariant(font);
			}else if(index.internalId() >= 10000 && index.internalId() < 100000){
				QFont font;
				font.setItalic(true);
				return QVariant(font);
			}else{
				return QVariant(QFont());
			}

		default:
			return QVariant();
	}
}

QModelIndex Workspace::index(int row, int column, const QModelIndex &parent) const{
	if(!parent.isValid()){
		return createIndex(row, column, row+1);
	}else if(parent.internalId() < 10000){
		return createIndex(row, column, (int)(parent.internalId()+10000*(row+1)));
	}else if(parent.internalId() >= 10000 && parent.internalId() < 100000){
		return createIndex(row, column, (int)(parent.internalId()+100000*(row+1)));
	}
	return QModelIndex();
}

QModelIndex Workspace::parent(const QModelIndex &index) const{
	if(!index.isValid()){
		return QModelIndex();
	}else if(index.internalId() < 10000){
		return QModelIndex();
	}else if(index.internalId() >= 10000 && index.internalId() < 100000){
		return createIndex((int)(index.internalId()%10000)-1, 0, (int)(index.internalId()%10000));
	}else if(index.internalId() >= 100000){
		return createIndex((int)(index.internalId()%100000)/10000-1, 0, (int)(index.internalId()%100000));
	}
	return QModelIndex();
}

int Workspace::rowCount(const QModelIndex &parent) const{
	if(!parent.isValid()){
		return project.length();
	}else if(parent.internalId() < 10000){
		return 4;
	}else if(parent.internalId() >= 10000 && parent.internalId() < 100000){
		switch(parent.internalId()/10000){
			case 1:
				return project[parent.internalId()%10000-1].getTrainingPatternCount();
			case 2:
				return project[parent.internalId()%10000-1].getNeuralNetworkCount();
			case 3:
				return project[parent.internalId()%10000-1].getLearningConfigCount();
			case 4:
				return project[parent.internalId()%10000-1].getTestingScenarioCount();
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
	project.append(Project(path, name));
	emit layoutChanged();
}

void Workspace::createTrainingPattern(const QModelIndex& index, QString name){
	project[index.internalId()%10000-1].createTrainingPattern(name);
	emit layoutChanged();
}

void Workspace::createNeuralNetwork(const QModelIndex& index, QString name){
	project[index.internalId()%10000-1].createNeuralNetwork(name);
	emit layoutChanged();
}

void Workspace::createLearningConfig(const QModelIndex& index, QString name){
	project[index.internalId()%10000-1].createLearningConfig(name);
	emit layoutChanged();
}

void Workspace::createTestingScenario(const QModelIndex& index, QString name, TestingScenarioType type){
	project[index.internalId()%10000-1].createTestingScenario(name, type);
	emit layoutChanged();
}

Project& Workspace::getProject(int index){
	return project[index];
}

int Workspace::getProjectCount(){
	return project.length();
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
