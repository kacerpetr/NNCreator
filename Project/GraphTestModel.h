#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include <QString>
#include <QStringList>
#include <QList>

#include "BaseModel.h"

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Model of test of neural network by output graph.
 */
class GraphTestModel : public BaseModel{
	Q_OBJECT

	public:
		GraphTestModel();
		void save();

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

	private:
		int out;
		QString trSet;
		QString mlNet;

};

}

#endif // GRAPHTESTMODEL_H
