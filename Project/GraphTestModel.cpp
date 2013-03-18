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

void GraphTestModel::drawPlot(){
	Q_ASSERT(network()->inputCount() >= 1);
	Q_ASSERT(network()->inputCount() <= 3);

	setSaved(false);

	delete plt;
	plt = NULL;

	if(network()->inputCount() == 1) draw1D(); else
	if(network()->inputCount() == 2) draw2D(); else
	if(network()->inputCount() == 3) draw3D();
}

void GraphTestModel::draw1D(){
	Plot1D* pl = new Plot1D();

	for(double i = 0; i <= 1; i += 0.05){
		QList<double> input;
		input.append(i);
		QList<double> out = network()->output(input);
		pl->addPoint(i, out[this->out-1]);
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
        pl->setRes(101, 101);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append(x * 0.01);
                input.append(y * 0.01);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }

    else if(network()->transferFunction() == BinarySigmoid){
        pl->setRange(-1, 1);
        pl->setRangeX(-1, 1);
        pl->setRangeY(-1, 1);
        pl->setRes(101, 101);
        for(int x = 0; x < pl->image()->size().width(); x++){
            for(int y = 0; y < pl->image()->size().height(); y++){
                QList<double> input;
                input.append((x-50) * 0.02);
                input.append((y-50) * 0.02);
                QList<double> out = network()->output(input);
                pl->setPoint(x, y, out[this->out-1]);
            }
        }
    }

    plt = pl;
}

void GraphTestModel::draw3D(){
	Plot3D* pl = new Plot3D();

	for(double i = 0; i <= 1; i += 0.05){
		for(double j = 0; j <= 1; j += 0.05){
			for(double k = 0; k <= 1; k += 0.05){
				QList<double> input;
				input.append(i);
				input.append(j);
				input.append(k);
				QList<double> out = network()->output(input);
				pl->addPoint(i, j, k, out[this->out-1]);
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
