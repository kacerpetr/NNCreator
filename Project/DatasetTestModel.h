#ifndef DATASETTESTMODEL_H
#define DATASETTESTMODEL_H

#include "BaseModel.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include "BaseModel.h"
#include "Project.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

class Project;

/**
 * Model of dataset test screen.
 */
class DatasetTestModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		DatasetTestModel();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

		void setProject(Project* prj);

		QString networkName();
		QString datasetName();
		void setNetworkName(QString name);
		void setDatasetName(QString name);

		QList<QList<double> > runTest(long& time, double& err);
		DatasetEditModel* dataset();

		QStringList networkList();
		QStringList datasetList(QString name);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

	private:
		Project* prj;
		QString trSet;
		QString mlNet;

};

}

#endif // DATASETTESTMODEL_H
