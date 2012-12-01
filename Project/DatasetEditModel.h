#ifndef DATASETEDITMODEL_H
#define DATASETEDITMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include "BaseModel.h"

namespace Project{

class DatasetEditModel : public QAbstractItemModel, public BaseModel{
	Q_OBJECT

	public:
		explicit DatasetEditModel(QObject *parent = 0);
		~DatasetEditModel();
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		Qt::ItemFlags flags(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;

	private:
		double*** dataGrid;
		int rows;
		int cols;
};

}

#endif // TRAININGPATTERNMODEL_H
