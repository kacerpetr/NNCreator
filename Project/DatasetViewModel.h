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
		/** Class constructor */
		DatasetViewModel(QObject *parent, Dataset* dataset);

		/** Returns the data stored under the given role for the item referred to by the index. */
		QVariant data(const QModelIndex &index, int role) const;

		/** Returns the data for the given role and section in the header with the specified orientation. */
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		/** Returns the index of the item in the model specified by the given row, column and parent index.*/
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

		/**
		 * Returns the parent of the model item with the given index.
		 * If the item has no parent, an invalid QModelIndex is returned.
		 */
		QModelIndex parent(const QModelIndex &index) const;

		/**
		 * Sets the role data for the item at index to value.
		 * Returns true if successful; otherwise returns false.
		 */
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

		/** Returns the item flags for the given index. */
		Qt::ItemFlags flags(const QModelIndex &index) const;

		/** Returns the number of rows under the given parent. */
		int rowCount(const QModelIndex &parent) const;

		/** Returns the number of columns for the children of the given parent. */
		int columnCount(const QModelIndex &parent) const;

		/** Emits layout changed signal. */
		void emitLayoutChanged();

		/** Clears cell at given index. */
		void clearCell(const QModelIndex &index);

	private:
		/** Poiter to dataset given in constructor. */
		Dataset* dataset;
};

}

#endif // DATASETVIEWMODEL_H
