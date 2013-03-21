#ifndef PLOT1D_H
#define PLOT1D_H

#include "Util/globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QFont>
#include <QString>

namespace Application{

class Plot1D : public QGLWidget{
	Q_OBJECT

	public:
		Plot1D(QWidget *parent = NULL);
        Plot1D(QString data, QWidget *parent = NULL);
        virtual ~Plot1D();
        void addPoint(double x, double o);
        QString toString();
        void fromString(QString data);
        void setAutorange(bool enabled);
        void setRange(double min, double max);
        void setRangeX(double min, double max);
        double maxX();
        double maxO();
        void setLabelX(QString label);
        void setLabelY(QString label);

    private slots:
        void contextMenu();
        void clearGraph();
        void saveGraphCsv();
        void saveGraphPng();

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
        double graphWidth();
        double graphHeight();

	private:
		QList<Point1D> point;
        bool autorange;
        double xrMin;
        double xrMax;
        double orMin;
        double orMax;
        double xMin;
        double xMax;
        double oMin;
		double oMax;
		int leftSpace;
		int rightSpace;
		int topSpace;
		int bottomSpace;
		QFont font;
        QString xLbl;
        QString yLbl;
};

}

#endif // PLOT1D_H
