#ifndef PLOT1D_H
#define PLOT1D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QFont>

namespace Application{

class Plot1D : public QGLWidget{
	Q_OBJECT

	public:
		Plot1D(QWidget *parent = NULL);
		virtual ~Plot1D();
		void addPoint(double x, double o);
		void addPoint(Point1D point);
		void setData(QList<Point1D> data);
		void clearGraph();

	private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
		void drawXAxis();
		void drawXGrid();
		void drawXLabel();
		void drawYAxis();
		void drawYGrid();
		void drawYLabel();
		void drawGraph();
		void rendText(float x, float y, QString text);
		void rendTextV(float x, float y, QString text);

	private:
		QList<Point1D> point;
		double xMax;
		double oMax;
		int leftSpace;
		int rightSpace;
		int topSpace;
		int bottomSpace;
		QFont font;
};

}

#endif // PLOT1D_H
