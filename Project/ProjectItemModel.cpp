#include "ProjectItemModel.h"
#include <QDebug>
#include <QSize>
#include <QIcon>

namespace Project{

ProjectItemModel::ProjectItemModel(QObject* parent) : QAbstractItemModel(parent){

}

ProjectItemModel::~ProjectItemModel(){

}

QVariant ProjectItemModel::data(const QModelIndex &index, int role) const{
	if (!index.isValid()) return QVariant();

	switch(role){
		case Qt::DisplayRole:
			switch(index.internalId()){
				case 1:
					return QVariant("Training patterns");
				case 2:
					return QVariant("Topology");
				case 3:
					return QVariant("Graphs");
				default:
					return QVariant("item");
			}

		case Qt::DecorationRole:
			switch(index.internalId()){
				case 1:
					return QVariant(QIcon(":trainingPatternIcon32"));
				case 2:
					return QVariant(QIcon(":topologyIcon32"));
				case 3:
					return QVariant(QIcon(":graphIcon32"));
			}

		default:
			return QVariant();
	}
}

QModelIndex ProjectItemModel::index(int row, int column, const QModelIndex &parent) const{
	switch(parent.internalId()){
		case 0:
			return createIndex(row, column, row+1);

		case 1:
			return createIndex(row, column, (row+1)*10 + 1);

		case 2:
			return createIndex(row, column, (row+1)*10 + 2);

		case 3:
			return createIndex(row, column, (row+1)*10 + 3);
	}

	return QModelIndex();
}

QModelIndex ProjectItemModel::parent(const QModelIndex &index) const{
	switch(index.internalId()){
		case 1:
			return QModelIndex();

		case 2:
			return QModelIndex();

		case 3:
			return QModelIndex();
	}
	return createIndex((int)index.internalId()%10, 1, (int)index.internalId()%10);
}

int ProjectItemModel::rowCount(const QModelIndex &parent) const{
	if(parent.internalId() > 3) return 0;
	switch(parent.internalId()){
		case 1:
			return 2;
		case 2:
			return 4;
		case 3:
			return 5;
		default:
			return 3;
	}
}

int ProjectItemModel::columnCount(const QModelIndex &parent) const{
	return 1;
}

/*QVariant ProjectItemModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (role != Qt::DisplayRole) return QVariant();
	return QVariant(QString("Project files"));
}*/

}
