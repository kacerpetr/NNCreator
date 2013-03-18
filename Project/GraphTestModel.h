#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QGLWidget>

#include "BaseModel.h"
#include "TopologyEditModel.h"
#include "GuiPart/Plot1D.h"
#include "GuiPart/Plot2D.h"
#include "GuiPart/Plot3D.h"
using namespace Application;

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
		~GraphTestModel();
		virtual void save();
		int output();
		void setOutput(int output);
        TopologyEditModel* network();
		void drawPlot();
		QWidget* plot();

    private:
		void draw1D();
		void draw2D();
		void draw3D();
        void drawCl();


	private:
		int out;
		QGLWidget* plt;
};

}

#endif // GRAPHTESTMODEL_H
