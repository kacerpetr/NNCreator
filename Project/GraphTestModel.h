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

#ifndef GRAPHTESTMODEL_H
#define GRAPHTESTMODEL_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QGLWidget>

#include "BaseModel.h"
#include "TopologyEditModel.h"
#include "DatasetEditModel.h"
#include "GuiPart/Plot1D.h"
#include "GuiPart/Plot2D.h"
#include "GuiPart/Plot3D.h"
#include "GuiPart/PlotCls.h"
using namespace Application;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Model of test of neural network by output graph.
 */
class GraphTestModel : public BaseModel{
	Q_OBJECT

	public:
		GraphTestModel();
		~GraphTestModel();
		virtual void save();
		int output();
		void setOutput(int output);
        TopologyEditModel* network();
        DatasetEditModel* dataset();
		void drawPlot();
		QWidget* plot();
        bool hasSettings();

    private:
		void draw1D();
		void draw2D();
		void draw3D();
        void drawCl();

	private:
        /** Selected output. */
		int out;
        /** Model's plot pointer. */
		QGLWidget* plt;
};

}

#endif // GRAPHTESTMODEL_H
