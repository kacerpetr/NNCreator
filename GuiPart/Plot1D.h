/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLOT1D_H
#define PLOT1D_H

#include "Util/Globaldef.h"
#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QFont>
#include <QString>
#include <Project/LearningConfigModel.h>

namespace ProjectData{
    class LearningConfigModel;
}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Plot for f(x) function.
 */
class Plot1D : public QGLWidget{
	Q_OBJECT

	public:
		Plot1D(QWidget *parent = NULL);
        Plot1D(QString data, QWidget *parent = NULL);
        virtual ~Plot1D();
        void setModel(ProjectData::LearningConfigModel* model);
        void addPoint(double x, double o);
        QString toString();
        void fromString(QString data);
        void setAutorange(bool enabled);
        void setMinAutorangeO(double val);
        void setRange(double min, double max);
        void setRangeX(double min, double max);
        double maxX();
        double maxO();
        void setLabelX(QString label);
        void setLabelY(QString label);
        void addPlot(Plot1D* plot);
        void clearGraph();

    private slots:
        void contextMenu();
        void saveGraphCsv();
        void saveGraphPng();
        void removePlot(QString name);

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
        /** List of graph lines. */
        QList<QList<Point1D> > point;
        /** Names of additional lines. */
        QStringList additional;
        /** Determines if range of axis is calculated automaticaly. */
        bool autorange;
        /** Minimal x value used when autorange is false. */
        double xrMin;
        /** Maximal x value used when autorange is false. */
        double xrMax;
        /** Minimal y value used when autorange is false. */
        double orMin;
        /** Maximal y value used when autorange is false. */
        double orMax;
        /** Minimal x value used when autorange is true. */
        double xMin;
        /** Maximal x value used when autorange is true. */
        double xMax;
        /** Minimal y value used when autorange is true. */
        double oMin;
        /** Maximal y value used when autorange is true. */
		double oMax;
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
        /** X axis label. */
        QString xLbl;
        /** Y axis label. */
        QString yLbl;
        /** Learning config model pointer. */
        ProjectData::LearningConfigModel* mdl;
};

}

#endif // PLOT1D_H
