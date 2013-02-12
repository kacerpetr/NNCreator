#include "GraphTestMdlParser.h"

namespace Parsers{

GraphTestMdlParser::GraphTestMdlParser(){}

GraphTestMdlParser& GraphTestMdlParser::get(){
	static GraphTestMdlParser instance;
	return instance;
}

GraphTestModel* GraphTestMdlParser::load(QString path) const{

}

bool GraphTestMdlParser::save(GraphTestModel* project) const{

}

}
