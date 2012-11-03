#ifndef TRAININGPATTERNMODEL_H
#define TRAININGPATTERNMODEL_H

#include <QAbstractItemModel>
#include <QVector>

namespace Project{

class TrainingPatternModel : public QAbstractItemModel{
	Q_OBJECT

	public:
		explicit TrainingPatternModel(QObject *parent = 0);
		~TrainingPatternModel();
		QVariant data(const QModelIndex &index, int role) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
		QModelIndex parent(const QModelIndex &index) const;
		bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		Qt::ItemFlags flags(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent = QModelIndex()) const;
		int columnCount(const QModelIndex &parent = QModelIndex()) const;
		void setName(QString name);
		QString getName() const;

	private:
		QString name;
		double*** dataGrid;
		int rows;
		int cols;
};

}

#endif // TRAININGPATTERNMODEL_H
