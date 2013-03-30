#ifndef PLOT2D_H
#define PLOT2D_H

#include "Util/Globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QImage>

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Plot for f(x,y) function.
 */
class Plot2D : public QGLWidget{
	Q_OBJECT

	public:
		Plot2D(QWidget *parent = NULL);
		virtual ~Plot2D();
        void setRes(int xRes, int yRes);
        void setPoint(int x, int y, double val);
        void setPoint(int x, int y, QColor clr);
        void setRange(double min, double max);
        void setRangeX(double min, double max);
        void setRangeY(double min, double max);
        void setLabelX(QString text);
        void setLabelY(QString text);
        void setSmoothTex(bool enable);
        QImage* image();

    private slots:
        void contextMenu();
        void clearGraph();
        void saveGraphPng();

    private:
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int w, int h);
        void drawGraph();
		void drawXAxis();
        void drawYAxis();
        void rendText(float x, float y, QString text);
        void rendTextV(float x, float y, QString text);

	private:
        /** Plot image pointer. */
        QImage* img;
        /** Label of X axis. */
        QString xLabel;
        /** Label of Y axis */
        QString yLabel;
        /** Scale of output values based on range. */
        double scale;
        /** Maximal x value. */
        double xMax;
        /** Minimal x value. */
        double xMin;
        /** Maximal y value. */
        double yMax;
        /** Minimal y value. */
        double yMin;
        /** Maximal output value. */
        double oMax;
        /** Minimal output value. */
        double oMin;
        /** Left indentation of plot. */
        int leftSpace;
        /** Right indentation of plot. */
        int rightSpace;
        /** Top indentation of plot. */
        int topSpace;
        /** Bottom indentation of plot. */
        int bottomSpace;
        /** Font of all texts in plot. */
        QFont font;
        /** Determines if texture filtering is enabled. */
        bool smoothTex;
};

}

#endif // PLOT2D_H
