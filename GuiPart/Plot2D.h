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
        void addPoint(Point2D pt);
        void clearPoints();

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
        void drawPoints();
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
        /** Points to show in plot */
        QList<Point2D> point;
};

}

#endif // PLOT2D_H
