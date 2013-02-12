#include "DatasetEditModel.h"
#include <QDebug>
#include <QBrush>
#include <QColor>
#include "Parsers/DatasetMdlParser.h"
using namespace Parsers;

namespace Project{

DatasetEditModel::DatasetEditModel(QObject *parent) :
	QAbstractItemModel(parent),
	BaseModel(DatasetEdit)
{
	//default size of new dataset
	dataset.setMinSize(6,2,2);
}

QVariant DatasetEditModel::data(const QModelIndex &index, int role) const{
	if (!index.isValid()) return QVariant();
	switch(role){
		case Qt::DisplayRole:
			//no value for rows outside pattern list
			if(index.row()/2 >= dataset.patternCount()) return QVariant();

			//rows that contain input vectors
			if(index.row()%2 == 0 && index.column() < dataset.inputCount()){
				if(dataset.isInputNull(index.row()/2, index.column())) return QVariant();
				else return QVariant(dataset.input(index.row()/2, index.column()));
			}
			//rows that contain output vectors
			else if(index.row()%2 == 1 && index.column() < dataset.outputCount()){
				if(dataset.isOutputNull(index.row()/2, index.column())) return QVariant();
				else return QVariant(dataset.output(index.row()/2, index.column()));
			}

			//to be on the safe side
			return QVariant();

		case Qt::BackgroundRole:
			//rows outside pattern list have 100% transparent background
			if(index.row()/2 >= dataset.minPatternCount())
				return QVariant(QBrush(QColor(200,200,200,0)));

			//rows that contain input vectors
			if(index.row()%2 == 0){
				//cells outside input vectors have 100% transparent background
				if(index.column() >= dataset.minInputCount())
					return QVariant(QBrush(QColor(200,200,200,0)));
				//input vector cells have light blue color
				return QVariant(QBrush(QColor(235,235,250)));
			}

			//rows that contain output vectors
			else{
				//cells outside output vectors have 100% transparent background
				if(index.column() >= dataset.minOutputCount())
					return QVariant(QBrush(QColor(200,200,200,0)));
				//input vector cells have light yellow color
				return QVariant(QBrush(QColor(250,250,220)));
			}

		default:
			return QVariant();
	}
}

QVariant DatasetEditModel::headerData(int section, Qt::Orientation orientation, int role) const{
	switch(role){
		case Qt::DisplayRole:
			//sets horizontal header value
			if(orientation == Qt::Horizontal){
				QString num = QString::number(section+1);
				return QVariant(num);
			}
			//sets horizontal header value
			else{
				QString num = QString::number((section-section%2)/2+1);
				if(section % 2 == 0) return QVariant("In " + num);
				else return QVariant("Out " + num);
			}

		case Qt::TextAlignmentRole:
			//sets vertical header alignment
			if(orientation == Qt::Vertical){
				return QVariant(Qt::AlignRight);
			}

		default:
			return QVariant();
	}
}

QModelIndex DatasetEditModel::index(int row, int column, const QModelIndex &parent) const{
	return createIndex(row, column, 0);
}

QModelIndex DatasetEditModel::parent(const QModelIndex &index) const{
	return QModelIndex();
}

bool DatasetEditModel::setData(const QModelIndex &index, const QVariant &value, int role){
	if(role == Qt::EditRole){
		//entered value must be number
		bool ok;
		double num = value.toDouble(&ok);
		if(!ok) return false; //not successful

		//sets entered value to dataset input or output vector
		if(index.row() % 2 == 0) dataset.setInput(index.row()/2, index.column(), num);
		else dataset.setOutput(index.row()/2, index.column(), num);
	}

	//successful
	return true;
}

Qt::ItemFlags DatasetEditModel::flags(const QModelIndex &index) const{
	//redundand rows cant be edited or selected
	if(index.row()/2 >= dataset.minPatternCount())
		return Qt::NoItemFlags;

	//cells outside input vector cant be edited or selected
	if(index.row()%2 == 0 && index.column() >= dataset.minInputCount())
		return Qt::NoItemFlags;

	//cells outside output vector cant be edited or selected
	if(index.row()%2 == 1 && index.column() >= dataset.minOutputCount())
		return Qt::NoItemFlags;

	//other cells can be edited or selected
	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

int DatasetEditModel::rowCount(const QModelIndex &parent) const{
	//minimal row count is 100 to get more consistent table
	return dataset.patternCount() <= 50 ? 100 : dataset.patternCount() * 2;
}

int DatasetEditModel::columnCount(const QModelIndex &parent) const{
	int inCnt = dataset.inputCount();
	int outCnt = dataset.outputCount();
	int cnt = outCnt > inCnt ? outCnt : inCnt;
	return cnt <= 50 ? 50 : cnt; //minimal column count is 50 to get more consistent table
}

void DatasetEditModel::setPatternCount(int count){
	dataset.setMinPaternCount(count);
	emit layoutChanged();
}

void DatasetEditModel::setInputCount(int count){
	dataset.setMinInputCount(count);
	emit layoutChanged();
}

void DatasetEditModel::setOutputCount(int count){
	dataset.setMinOutputCount(count);
	emit layoutChanged();
}

int DatasetEditModel::patternCount(){
	return dataset.minPatternCount();
}

int DatasetEditModel::inputCount(){
	return dataset.minInputCount();
}

int DatasetEditModel::outputCount(){
	return dataset.minOutputCount();
}

Dataset* DatasetEditModel::getDataset(){
	return &dataset;
}

void DatasetEditModel::save(){
	DatasetMdlParser& parser = DatasetMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void DatasetEditModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void DatasetEditModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

DatasetEditModel::~DatasetEditModel(){}

}
