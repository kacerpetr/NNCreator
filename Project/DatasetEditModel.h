#ifndef DATASETEDITMODEL_H
#define DATASETEDITMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include "NeuralNetwork/Dataset.h"
#include "BaseModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Data model for editor of training and testing datasets.
 */
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
		int rowCount(const QModelIndex &parent) const;
		int columnCount(const QModelIndex &parent) const;
		void setPatternCount(int count);
		void setInputCount(int count);
		void setOutputCount(int count);
		int patternCount();
		int inputCount();
		int outputCount();
		Dataset* getDataset();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);


	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

	private:
		Dataset dataset;
};

}

#endif // TRAININGPATTERNMODEL_H
