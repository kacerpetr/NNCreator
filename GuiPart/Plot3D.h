#ifndef PLOT3D_H
#define PLOT3D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QMouseEvent>
#include <QWheelEvent>

namespace Application{

class Plot3D : public QGLWidget{
	Q_OBJECT

	public:
		Plot3D(QWidget *parent = NULL);
		virtual ~Plot3D();
		void addPoint(double x, double y, double z, double o);
		void clearGraph();

	private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
		void drawXAxis();
		void drawYAxis();
		void drawZAxis();
		void drawGraph();
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);

	private:
		QList<Point3D> point;
		double xMax;
		double yMax;
		double zMax;
		double oMax;
		double rotX;
		double rotY;
		double scale;
		bool pressed;
		int mouseX;
		int mouseY;
};

}

#endif // PLOT3D_H
