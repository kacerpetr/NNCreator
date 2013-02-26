#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include "Util/globaldef.h"
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
 * Model of test of neural network by output graph.
 */
class GraphTestModel : public QObject, public BaseModel{
	Q_OBJECT

	public:
		GraphTestModel();
		void save();
		virtual void setOpened(bool state);
		virtual void setSaved(bool state);

		void setProject(Project* prj);

		QString networkName();
		QString datasetName();
		void setNetworkName(QString name);
		void setDatasetName(QString name);

		AbstractMlnNet* network();
		Dataset* dataset();

		QStringList networkList();
		QStringList datasetList(QString name);

		QList<Point1D> graph1D();
		QList<Point2D> graph2D();
		QList<Point3D> graph3D();

		int output();
		void setOutput(int output);

	signals:
		void opened(BaseModel*);
		void saved(BaseModel*);

	private:
		int out;
		Project* prj;
		QString trSet;
		QString mlNet;

};

}

#endif // GRAPHTESTMODEL_H
