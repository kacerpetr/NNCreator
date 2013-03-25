#include "DatasetViewModel.h"
#include <QColor>
#include <QBrush>
#include <QDebug>

namespace ProjectData{

/**
 * Class constructor.
 */
DatasetViewModel::DatasetViewModel(QObject* parent, Dataset* dataset):
	QAbstractItemModel(parent),
	dataset(dataset)
{
	Q_ASSERT(dataset != NULL);
}

/**
 * Returns the data stored under the given role for the item referred to by the index.
 */
QVariant DatasetViewModel::data(const QModelIndex &index, int role) const{
	Q_ASSERT(dataset != NULL);
	if (!index.isValid()) return QVariant();

	switch(role){
		case Qt::DisplayRole:
			//no value for rows outside pattern list
			if(index.row()/2 >= dataset->patternCount()) return QVariant();

			//rows that contain input vectors
            if(index.row()%2 == 0 && index.column() < dataset->minInputCount()){
				if(dataset->isInputNull(index.row()/2, index.column())) return QVariant();
				else return QVariant(dataset->input(index.row()/2, index.column()));
			}
			//rows that contain output vectors
            else if(index.row()%2 == 1 && index.column() < dataset->minOutputCount()){
				if(dataset->isOutputNull(index.row()/2, index.column())) return QVariant();
				else return QVariant(dataset->output(index.row()/2, index.column()));
			}

			//to be on the safe side
			return QVariant();

		case Qt::BackgroundRole:
			//rows outside pattern list have 100% transparent background
			if(index.row()/2 >= dataset->minPatternCount())
				return QVariant(QBrush(QColor(200,200,200,0)));

			//rows that contain input vectors
			if(index.row()%2 == 0){
				//cells outside input vectors have 100% transparent background
				if(index.column() >= dataset->minInputCount())
					return QVariant(QBrush(QColor(200,200,200,0)));
				//input vector cells have light green color
				return QVariant(QBrush(QColor(210,250,210)));
			}

			//rows that contain output vectors
			else{
				//cells outside output vectors have 100% transparent background
				if(index.column() >= dataset->minOutputCount())
					return QVariant(QBrush(QColor(200,200,200,0)));
				//input vector cells have light red color
				return QVariant(QBrush(QColor(250,220,220)));
			}

		default:
			return QVariant();
	}
}

/**
 * Returns the data for the given role and section in the header with the specified orientation.
 */
QVariant DatasetViewModel::headerData(int section, Qt::Orientation orientation, int role) const{
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

/**
 * Returns the index of the item in the model specified by the given row, column and parent index.
 */
QModelIndex DatasetViewModel::index(int row, int column, const QModelIndex &parent) const{
	return createIndex(row, column, 0);
}

/**
 * Returns the parent of the model item with the given index.
 * If the item has no parent, an invalid QModelIndex is returned.
 */
QModelIndex DatasetViewModel::parent(const QModelIndex &index) const{
	return QModelIndex();
}

/**
 * Sets the role data for the item at index to value.
 * Returns true if successful; otherwise returns false.
 */
bool DatasetViewModel::setData(const QModelIndex &index, const QVariant &value, int role){
	if(role == Qt::EditRole){
		//entered value must be number
		bool ok;
		double num = value.toDouble(&ok);
		if(!ok) return false; //not successful

		//sets entered value to dataset input or output vector
		if(index.row() % 2 == 0) dataset->setInput(index.row()/2, index.column(), num);
		else dataset->setOutput(index.row()/2, index.column(), num);
	}

	emit dataChanged(QModelIndex(), QModelIndex());

	//successful
	return true;
}

/**
 * Returns the item flags for the given index.
 */
Qt::ItemFlags DatasetViewModel::flags(const QModelIndex &index) const{
	//redundand rows cant be edited or selected
	if(index.row()/2 >= dataset->minPatternCount())
		return Qt::NoItemFlags;

	//cells outside input vector cant be edited or selected
	if(index.row()%2 == 0 && index.column() >= dataset->minInputCount())
		return Qt::NoItemFlags;

	//cells outside output vector cant be edited or selected
	if(index.row()%2 == 1 && index.column() >= dataset->minOutputCount())
		return Qt::NoItemFlags;

	//other cells can be edited or selected
	return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/**
 * Returns the number of rows under the given parent.
 */
int DatasetViewModel::rowCount(const QModelIndex &parent) const{
	//minimal row count is 100 to get more consistent table
	return dataset->patternCount() <= 50 ? 100 : dataset->patternCount() * 2;
}

/**
 * Returns the number of columns for the children of the given parent.
 */
int DatasetViewModel::columnCount(const QModelIndex &parent) const{
    int inCnt = dataset->minInputCount();
    int outCnt = dataset->minOutputCount();
	int cnt = outCnt > inCnt ? outCnt : inCnt;
	//minimal column count is 50 to get more better looking table
	return cnt <= 50 ? 50 : cnt;
}

/**
 * Emits layout changed signal.
 */
void DatasetViewModel::emitLayoutChanged(){
    emit layoutChanged();
}


/**
 * Clears cell at given index.
 */
void DatasetViewModel::clearCell(const QModelIndex &index){
	if(!index.isValid()) return;
	if(index.row() % 2 == 0) dataset->clearInput(index.row()/2, index.column());
	else dataset->clearOutput(index.row()/2, index.column());
}

}
