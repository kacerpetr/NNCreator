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

#include "GraphTestModel.h"
#include "Parser/GraphTestMdlParser.h"
#include <QDebug>
#include "Util/Settings.h"
using namespace Parser;

namespace ProjectData{

/**
 * Class constructor.
 */
GraphTestModel::GraphTestModel() : BaseModel(GraphTest),
	out(1),
	plt(NULL)
{}

/**
 * Class destructor.
 */
GraphTestModel::~GraphTestModel(){
	delete plt;
	plt = NULL;
}

/**
 * Returns pointer to model's plot widget.
 */
QWidget* GraphTestModel::plot(){
	return plt;
}

/**
 * Draws plot according to selected network and selected output.
 */
void GraphTestModel::drawPlot(){
	Q_ASSERT(network()->inputCount() >= 1);
	Q_ASSERT(network()->inputCount() <= 3);

	setSaved(false);

	delete plt;
	plt = NULL;

    if(network()->inputCount() == 2 && out == 0) drawCl(); else
    if(network()->inputCount() == 1 && out >  0) draw1D(); else
    if(network()->inputCount() == 2 && out >  0) draw2D(); else
    if(network()->inputCount() == 3 && out >  0) draw3D();
}

/**
 * Draws output plot of network with one input.
 */
void GraphTestModel::draw1D(){
	Plot1D* pl = new Plot1D();
    pl->setLabelX(tr("Input"));
    pl->setLabelY(tr("Output"));
    pl->setAutorange(false);

    Settings& settings = Settings::get();
    int res = settings.outPlot1DRes();
    double step = 1.0/res;

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0,1);
        pl->setRangeX(0,1);
        for(double i = 0; i <= res; i += 1){
            QList<double> input;
            input.append(i*step);
            QList<double> out = network()->output(input);
            pl->addPoint(i*step, out[this->out-1]);
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1,1);
        pl->setRangeX(-1,1);
        for(double i = 0; i <= res; i += 1){
            QList<double> input;
            input.append((i-res/2)*step*2);
            QList<double> out = network()->output(input);
            pl->addPoint((i-res/2)*step*2, out[this->out-1]);
        }
    }

	plt = pl;
}

/**
 * Draws output plot of network with two inputs.
 */
void GraphTestModel::draw2D(){
    Plot2D* pl = new Plot2D();
    pl->setLabelX(tr("First input"));
    pl->setLabelY(tr("Second input"));

    Settings& settings = Settings::get();
    int resX = settings.outPlot2DResX();
    int resY = settings.outPlot2DResY();
    double stepX = 1.0/resX;
    double stepY = 1.0/resY;

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0, 1);
        pl->setRangeX(0, 1);
        pl->setRangeY(0, 1);
        pl->setRes(resX, resY);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append(x * stepX);
                input.append(y * stepY);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1, 1);
        pl->setRangeX(-1, 1);
        pl->setRangeY(-1, 1);
        pl->setRes(resX, resY);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append((x-resX/2) * stepX * 2);
                input.append((y-resY/2) * stepY * 2);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }

    plt = pl;
}

/**
 * Draws output plot of network with three inputs.
 */
void GraphTestModel::draw3D(){
	Plot3D* pl = new Plot3D();

    Settings& settings = Settings::get();
    int resX = settings.outPlot3DResX();
    int resY = settings.outPlot3DResY();
    int resZ = settings.outPlot3DResZ();
    double stepX = 1.0/resX;
    double stepY = 1.0/resY;
    double stepZ = 1.0/resZ;

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0, 1);
        pl->setRangeX(0, 1);
        pl->setRangeY(0, 1);
        pl->setRangeZ(0, 1);
        pl->setRes(resX, resY, resZ);
        for(int x = 0; x < resX; x++){
            for(int y = 0; y < resY; y++){
                for(int z = 0; z < resZ; z++){
                    QList<double> input;
                    input.append(x * stepX);
                    input.append(y * stepY);
                    input.append(z * stepZ);
                    QList<double> out = network()->output(input);
                    pl->setPoint(x, y, z, out[this->out-1]);
                }
            }
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1, 1);
        pl->setRangeX(-1, 1);
        pl->setRangeY(-1, 1);
        pl->setRangeZ(-1, 1);
        pl->setRes(resX, resY, resZ);
        for(int x = 0; x < resX; x++){
            for(int y = 0; y < resY; y++){
                for(int z = 0; z < resZ; z++){
                    QList<double> input;
                    input.append((x-resX/2) * stepX * 2);
                    input.append((y-resY/2) * stepY * 2);
                    input.append((z-resZ/2) * stepZ * 2);
                    QList<double> out = network()->output(input);
                    pl->setPoint(x, y, z, out[this->out-1]);
                }
            }
        }
    }

	plt = pl;
}

/**
 * Draws classification diagram.
 */
void GraphTestModel::drawCl(){
    PlotCls* pl = new PlotCls();
    pl->setLabelX(tr("First input"));
    pl->setLabelY(tr("Second input"));
    pl->setSmoothTex(false);

    Settings& settings = Settings::get();
    int resX = settings.classifDiagResX();
    int resY = settings.classifDiagResY();
    double stepX = 1.0/resX;
    double stepY = 1.0/resY;

    //draws classification diagram
    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0, 1);
        pl->setRangeX(0, 1);
        pl->setRangeY(0, 1);
        pl->setRes(resX, resY);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append(x * stepX);
                input.append(y * stepY);
                pl->classify(x, y, network()->output(input));
            }
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1, 1);
        pl->setRangeX(-1, 1);
        pl->setRangeY(-1, 1);
        pl->setRes(resX, resY);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append((x-resX/2) * stepX * 2);
                input.append((y-resY/2) * stepY * 2);
                pl->classify(x, y, network()->output(input));
            }
        }
    }

    //adds points from selected dataset
    DatasetEditModel* dset = dataset();

    if(dset != NULL){
        for(int i = 0; i < dset->minPatternCount(); i++){
            QList<double> outs;
            for(int j = 0; j < dset->minOutputCount(); j++) outs.append(dset->output(i, j));
            pl->classifyPoint(dset->input(i, 0), dset->input(i, 1), outs);
        }
    }

    plt = pl;
}

/**
 * Returns index of selected output or 0 for classification diagram.
 */
int GraphTestModel::output(){
	return out;
}

/**
 * Sets selected output.
 */
void GraphTestModel::setOutput(int output){
	this->out = output;
	setSaved(false);
}

/**
 * Returns pointer to selected network.
 */
TopologyEditModel* GraphTestModel::network(){
	BaseModel* netBase = selectedNetwork();
    Q_ASSERT(netBase != NULL);
	return (TopologyEditModel*)netBase;
}

/**
 * Returns pointer to selected dataset.
 */
DatasetEditModel* GraphTestModel::dataset(){
    if(selectedDatasetName().isEmpty()) return NULL;
    BaseModel* netBase = selectedDataset();
    if(netBase == NULL) return NULL;
    return (DatasetEditModel*)netBase;
}

/**
 * Saves model to file.
 */
void GraphTestModel::save(){
	GraphTestMdlParser& parser = GraphTestMdlParser::get();
	setSaved(parser.save(this));
}

}
