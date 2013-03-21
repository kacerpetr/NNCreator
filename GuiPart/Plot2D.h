#ifndef PLOT2D_H
#define PLOT2D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QImage>

namespace Application{

class Plot2D : public QGLWidget{
	Q_OBJECT

	public:
		Plot2D(QWidget *parent = NULL);
		virtual ~Plot2D();
        void setRes(int xRes, int yRes);
        void setPoint(int x, int y, double val);
        void setRange(double min, double max);
        void setRangeX(double min, double max);
        void setRangeY(double min, double max);
        void setLabelX(QString text);
        void setLabelY(QString text);
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
        QImage* img;
        QString xLabel;
        QString yLabel;
        double scale;
        double xMax;
        double xMin;
        double yMax;
        double yMin;
        double oMax;
        double oMin;
        int leftSpace;
        int rightSpace;
        int topSpace;
        int bottomSpace;
        QFont font;
};

}

#endif // PLOT2D_H
