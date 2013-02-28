#ifndef DATASETTESTMODEL_H
#define DATASETTESTMODEL_H

#include "DatasetEditModel.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

class DatasetEditModel;

/**
 * Model of dataset test screen.
 */
class DatasetTestModel : public BaseModel{
	Q_OBJECT

	public:
		DatasetTestModel();
		void save();

		QString networkName();
		QString datasetName();
		void setNetworkName(QString name);
		void setDatasetName(QString name);

		QList<QList<double> > runTest(long& time, double& err);
		DatasetEditModel* dataset();

		QStringList networkList();
		QStringList datasetList(QString name);

	private:
		QString trSet;
		QString mlNet;

};

}

#endif // DATASETTESTMODEL_H
