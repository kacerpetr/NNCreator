#ifndef PLOT3D_H
#define PLOT3D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QImage>

namespace Application{

class Plot3D : public QGLWidget{
	Q_OBJECT

	public:
		Plot3D(QWidget *parent = NULL);
		virtual ~Plot3D();
        void setRes(int xRes, int yRes, int zRes);
        void setPoint(int x, int y, int z, double o);
        void setRange(double min, double max);
        void setRangeX(double min, double max);
        void setRangeY(double min, double max);
        void setRangeZ(double min, double max);

    private slots:
        void contextMenu();
        void clearGraph();
        void saveGraphPng();
        void resetView();

	private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
		void drawGraph();
        void drawGrid();
        void drawLegend();
		void mouseMoveEvent(QMouseEvent* event);
		void mousePressEvent(QMouseEvent* event);
		void mouseReleaseEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);
        void rendText(float x, float y, QString text);

    private:
        //output space layers
        QList<QImage*> layer;

        //graph parameters
        int xMin;
        int xMax;
        int yMin;
        int yMax;
        int zMin;
        int zMax;
        int oMin;
        int oMax;

        //support variables
        int cut;
        double xRot;
        double yRot;
		double scale;
        bool lbPressed;
        bool rbPressed;
		int mouseX;
		int mouseY;
        QFont font;
};

}

#endif // PLOT3D_H
