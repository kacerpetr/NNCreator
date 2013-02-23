#ifndef PLOT1D_H
#define PLOT1D_H

#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QPointF>

namespace Application{

class Plot1D : public QGLWidget{
	Q_OBJECT

	public:
		Plot1D(QWidget *parent);
		void addPoint(double x, double y);

	private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
		void drawXAxis();
		void drawYAxis();
		void drawGraph();

	private:
		QList<QPointF> point;
		double xMax;
		double yMax;
};

}

#endif // PLOT1D_H
