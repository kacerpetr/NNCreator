#ifndef PLOT2D_H
#define PLOT2D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>

namespace Application{

class Plot2D : public QGLWidget{
	Q_OBJECT

	public:
		Plot2D(QWidget *parent = NULL);
		virtual ~Plot2D();
		void addPoint(double x, double y, double o);
		void clearGraph();

	private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
		void drawXAxis();
		void drawYAxis();
		void drawGraph();

	private:
		QList<Point2D> point;
		double xMax;
		double yMax;
		double oMax;
};

}

#endif // PLOT2D_H
