#include "GraphTestModel.h"
#include "Parser/GraphTestMdlParser.h"
using namespace Parser;

namespace ProjectData{

GraphTestModel::GraphTestModel() : BaseModel(GraphTest){}

void GraphTestModel::save(){
	GraphTestMdlParser& parser = GraphTestMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void GraphTestModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void GraphTestModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

}
