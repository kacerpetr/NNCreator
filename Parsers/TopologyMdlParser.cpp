#include "TopologyMdlParser.h"

namespace Parsers{

TopologyMdlParser::TopologyMdlParser(){}

TopologyMdlParser& TopologyMdlParser::get(){
	static TopologyMdlParser instance;
	return instance;
}

TopologyEditModel* TopologyMdlParser::load(QString path) const{

}

bool TopologyMdlParser::save(TopologyEditModel* project) const{

}

}
