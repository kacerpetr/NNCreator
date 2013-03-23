#include "GraphTestModel.h"
#include "Parser/GraphTestMdlParser.h"
#include <QDebug>
#include "Util/Settings.h"
using namespace Parser;
using namespace Util;

namespace ProjectData{

GraphTestModel::GraphTestModel() : BaseModel(GraphTest),
	out(1),
	plt(NULL)
{}

GraphTestModel::~GraphTestModel(){
	delete plt;
	plt = NULL;
}

QWidget* GraphTestModel::plot(){
	return plt;
}

bool GraphTestModel::hasSettings(){
    return !selectedNetworkName().isEmpty();
}

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

void GraphTestModel::draw1D(){
	Plot1D* pl = new Plot1D();
    pl->setLabelX("Input");
    pl->setLabelY("Output");
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

void GraphTestModel::draw2D(){
    Plot2D* pl = new Plot2D();
    pl->setLabelX("First input");
    pl->setLabelY("Second input");

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

void GraphTestModel::drawCl(){
    PlotCls* pl = new PlotCls();
    pl->setLabelX("First input");
    pl->setLabelY("Second input");
    pl->setSmoothTex(false);

    Settings& settings = Settings::get();
    int resX = settings.classifDiagResX();
    int resY = settings.classifDiagResY();
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

    plt = pl;
}

int GraphTestModel::output(){
	return out;
}

void GraphTestModel::setOutput(int output){
	this->out = output;
	setSaved(false);
}

TopologyEditModel* GraphTestModel::network(){
	BaseModel* netBase = selectedNetwork();
	Q_ASSERT(netBase != NULL);
	return (TopologyEditModel*)netBase;
}

void GraphTestModel::save(){
	GraphTestMdlParser& parser = GraphTestMdlParser::get();
	setSaved(parser.save(this));
}

}
