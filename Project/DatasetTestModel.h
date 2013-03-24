#ifndef DATASETTESTMODEL_H
#define DATASETTESTMODEL_H

#include "DatasetEditModel.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

//forward declaration of DatasetEditModel
class DatasetEditModel;

/**
 * Model of dataset test screen.
 */
class DatasetTestModel : public BaseModel{
	Q_OBJECT

	public:
		DatasetTestModel();
		virtual void save();
		QList<QList<double> > runTest(long& time, double& err);
};

}

#endif // DATASETTESTMODEL_H
