#include "GraphTestModel.h"
#include "Parser/GraphTestMdlParser.h"
#include <QDebug>
using namespace Parser;

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

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0,1);
        pl->setRangeX(0,1);
        for(double i = 0; i <= 100; i += 1){
            QList<double> input;
            input.append(i*0.01);
            QList<double> out = network()->output(input);
            pl->addPoint(i*0.01, out[this->out-1]);
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1,1);
        pl->setRangeX(-1,1);
        for(double i = 0; i <= 100; i += 1){
            QList<double> input;
            input.append((i-50)*0.02);
            QList<double> out = network()->output(input);
            pl->addPoint((i-50)*0.02, out[this->out-1]);
        }
    }

	plt = pl;
}

void GraphTestModel::draw2D(){
    Plot2D* pl = new Plot2D();
    pl->setLabelX("First input");
    pl->setLabelY("Second input");

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0, 1);
        pl->setRangeX(0, 1);
        pl->setRangeY(0, 1);
        pl->setRes(51, 51);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append(x * 0.02);
                input.append(y * 0.02);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }
    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1, 1);
        pl->setRangeX(-1, 1);
        pl->setRangeY(-1, 1);
        pl->setRes(51, 51);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append((x-25) * 0.04);
                input.append((y-25) * 0.04);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }

    plt = pl;
}

void GraphTestModel::draw3D(){
	Plot3D* pl = new Plot3D();

    if(network()->transferFunction() == UnarySigmoid){
        pl->setRange(0, 1);
        pl->setRangeX(0, 1);
        pl->setRangeY(0, 1);
        pl->setRangeZ(0, 1);
        pl->setRes(21, 21, 21);
        for(int x = 0; x < 21; x++){
            for(int y = 0; y < 21; y++){
                for(int z = 0; z < 21; z++){
                    QList<double> input;
                    input.append(x * 0.05);
                    input.append(y * 0.05);
                    input.append(z * 0.05);
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
        pl->setRangeZ(1, 1);
        pl->setRes(21, 21, 21);
        for(int x = 0; x < 21; x++){
            for(int y = 0; y < 21; y++){
                for(int z = 0; z < 21; z++){
                    QList<double> input;
                    input.append((x-10) * 0.1);
                    input.append((y-10) * 0.1);
                    input.append((z-10) * 0.1);
                    QList<double> out = network()->output(input);
                    pl->setPoint(x, y, z, out[this->out-1]);
                }
            }
        }
    }

	plt = pl;
}

void GraphTestModel::drawCl(){
    qDebug() << "classification diagram";
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
