#include "TrainingPatternModel.h"
#include <QDebug>
#include <QBrush>
#include <QColor>

namespace Project{

TrainingPatternModel::TrainingPatternModel(QObject *parent) : QAbstractItemModel(parent), rows(1000), cols(500), dataGrid(NULL){
	dataGrid = new double**[rows];
	for(int r = 0; r < rows; r++){
		dataGrid[r] = new double*[cols];
	}
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			dataGrid[r][c] = NULL;
		}
	}
}

TrainingPatternModel::~TrainingPatternModel(){
	for(int r = 0; r < rows; r++){
		for(int c = 0; c < cols; c++){
			delete dataGrid[r][c];
			dataGrid[r][c] = NULL;
		}
		delete[] dataGrid[r];
		dataGrid[r] = NULL;
	}
	delete[] dataGrid;
	dataGrid = NULL;
}

QVariant TrainingPatternModel::data(const QModelIndex &index, int role) const{
	if (!index.isValid()) return QVariant();
	switch(role){
		case Qt::DisplayRole:
			if(dataGrid[index.row()][index.column()] != NULL){
				return QVariant(*dataGrid[index.row()][index.column()]);
			}
			return QVariant();

		case Qt::BackgroundRole:
			if((index.row()+1) % 4 == 0 || (index.row()+2) % 4 == 0){
				return QVariant(QBrush(QColor(250,250,210)));
			}
			return QVariant(QBrush(Qt::white));

		default:
			return QVariant();
	}
}

QVariant TrainingPatternModel::headerData(int section, Qt::Orientation orientation, int role) const{
	switch(role){
		case Qt::DisplayRole:
			if(orientation == Qt::Horizontal){
				QString num = QString::number(section);
				return QVariant(num);
			}else{
				QString num = QString::number((section-section%2)/2+1);
				if(section % 2 == 0) return QVariant("In "+num);
				return QVariant("Out "+num);
			}

		case Qt::TextAlignmentRole:
			if(orientation == Qt::Vertical){
				return QVariant(Qt::AlignRight);
			}

		default:
			return QVariant();
	}
}

QModelIndex TrainingPatternModel::index(int row, int column, const QModelIndex &parent) const{
	return createIndex(row, column, row+1000000*column);
}

QModelIndex TrainingPatternModel::parent(const QModelIndex &index) const{
	return QModelIndex();
}

bool TrainingPatternModel::setData(const QModelIndex &index, const QVariant &value, int role){
	if(role == Qt::EditRole){
		bool ok;
		double num = value.toDouble(&ok);
		if(!ok) return true;

		if(dataGrid[index.row()][index.column()] != NULL){
			delete dataGrid[index.row()][index.column()];
		}

		dataGrid[index.row()][index.column()] = new double;
		*dataGrid[index.row()][index.column()] = num;
	}
	return true;
}

Qt::ItemFlags TrainingPatternModel::flags(const QModelIndex &index) const{
	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

int TrainingPatternModel::rowCount(const QModelIndex &parent) const{
	return rows;
}

int TrainingPatternModel::columnCount(const QModelIndex &parent) const{
	return cols;
}

void TrainingPatternModel::setName(QString name){
	this->name = name;
}

QString TrainingPatternModel::getName() const{
	return name;
}

}
