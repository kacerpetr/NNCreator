#include "GraphTestModel.h"
#include "Parser/GraphTestMdlParser.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

GraphTestModel::GraphTestModel() : BaseModel(GraphTest),
	out(0)
{}

QList<Point1D> GraphTestModel::graph1D(){
	QList<Point1D> res;

	for(double i = 0; i <= 1; i += 0.05){
		QList<double> input;
		input.append(i);

		QList<double> out = network()->output(input);

		Point1D p;
		p.x = i;
		p.o = out[this->out];

		res.append(p);
	}

	return res;
}

QList<Point2D> GraphTestModel::graph2D(){
	QList<Point2D> res;

	for(double i = 0; i <= 1; i += 0.05){
		for(double j = 0; j <= 1; j += 0.05){
			QList<double> input;
			input.append(i);
			input.append(j);

			QList<double> out = network()->output(input);

			Point2D p;
			p.x = i;
			p.y = j;
			p.o = out[this->out];

			res.append(p);
		}
	}

	return res;
}

QList<Point3D> GraphTestModel::graph3D(){
	QList<Point3D> res;

	for(double i = 0; i <= 1; i += 0.05){
		for(double j = 0; j <= 1; j += 0.05){
			for(double k = 0; k <= 1; k += 0.05){
				QList<double> input;
				input.append(i);
				input.append(j);
				input.append(k);

				QList<double> out = network()->output(input);

				Point3D p;
				p.x = i;
				p.y = j;
				p.z = k;
				p.o = out[this->out];

				res.append(p);
			}
		}
	}

	return res;
}

int GraphTestModel::output(){
	return out;
}

void GraphTestModel::setOutput(int output){
	this->out = output;
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
