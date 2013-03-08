#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include <QString>
#include <QStringList>
#include <QList>

#include "BaseModel.h"
#include "TopologyEditModel.h"

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
		virtual void save();
		QList<Point1D> graph1D();
		QList<Point2D> graph2D();
		QList<Point3D> graph3D();
		int output();
		void setOutput(int output);
		TopologyEditModel* network();

	private:
		int out;
};

}

#endif // GRAPHTESTMODEL_H
