#ifndef PROJECTITEMMODEL_H
#define PROJECTITEMMODEL_H

#include <QAbstractItemModel>
#include "Project/Project.h"

namespace Project{

class ProjectItemModel : public QAbstractItemModel{
	Q_OBJECT

	public:
		ProjectItemModel(QObject* parent = 0);
		~ProjectItemModel();

		QVariant data(const QModelIndex &index, int role) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		//QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
};

}

#endif // PROJECTITEMMODEL_H
