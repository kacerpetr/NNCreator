#include <QIcon>
#include <QFont>
#include "Workspace.h"

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
						return "Topologies";
					case 3:
						return "Graphs";
				}
			}
			return QVariant(QString("item"));

		case Qt::DecorationRole:
			if(index.internalId() >= 10000 && index.internalId() < 100000){
				switch((int)(index.internalId()/10000)){
					case 1:
						return QVariant(QIcon(":trainingPatternIcon32"));
					case 2:
						return QVariant(QIcon(":topologyIcon32"));
					case 3:
						return QVariant(QIcon(":graphIcon32"));
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
		return 3;
	}else if(parent.internalId() >= 10000 && parent.internalId() < 100000){
		switch(parent.internalId()/10000){
			case 1:
				return project[parent.internalId()%10000-1].getTrainingPatternCount();
			case 2:
				return project[parent.internalId()%10000-1].getNeuralNetworkCount();
			case 3:
				return project[parent.internalId()%10000-1].getGraphCount();
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
}

Project& Workspace::getProject(int index){
	return project[index];
}

int Workspace::getProjectCount(){
	return project.length();
}

Project& Workspace::operator[](int index){
	return project[index];
}

}
