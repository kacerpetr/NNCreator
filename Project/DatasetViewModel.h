#ifndef DATASETVIEWMODEL_H
#define DATASETVIEWMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include "NeuralNetwork/Dataset.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Model for dataset table view.
 * @note Cant be inherited by dataset edit model because BaseModel class inherits QObject.
 */
class DatasetViewModel : public QAbstractItemModel{
	Q_OBJECT

	public:
		DatasetViewModel(QObject *parent, Dataset* dataset);
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		Qt::ItemFlags flags(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
        void emitLayoutChanged();
		void clearCell(const QModelIndex &index);

	private:
		/** Poiter to dataset given in constructor. */
		Dataset* dataset;
};

}

#endif // DATASETVIEWMODEL_H
