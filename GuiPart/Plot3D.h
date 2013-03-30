#ifndef PLOT3D_H
#define PLOT3D_H

#include "Util/Globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QImage>

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Plot for f(x,y,z) function.
 */
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
        /** Output space layers. */
        QList<QImage*> layer;

        //graph parameters

        /** Minimal x value. */
        int xMin;
        /** Maximal x value. */
        int xMax;
        /** Minimal y value. */
        int yMin;
        /** Maximal y value. */
        int yMax;
        /** Minimal z value. */
        int zMin;
        /** Maximal z value. */
        int zMax;
        /** Minimal output value. */
        int oMin;
        /** Maximal output value. */
        int oMax;

        //support variables

        /** Number of layers hidden in cut. */
        int cut;
        /** Plot rotation around X axis. */
        double xRot;
        /** Plot rotation around Y axis. */
        double yRot;
        /** Value of plot scale. */
		double scale;
        /** True if left mouse button is pressed. */
        bool lbPressed;
        /** False if left mouse button is pressed. */
        bool rbPressed;
        /** Mouse X position. */
		int mouseX;
        /** Mouse Y position. */
		int mouseY;
        /** Font of all texts in plot. */
        QFont font;
};

}

#endif // PLOT3D_H
