#include "LrnConfMdlParser.h"

namespace Parsers{

LrnConfMdlParser::LrnConfMdlParser(){}

LrnConfMdlParser& LrnConfMdlParser::get(){
	static LrnConfMdlParser instance;
	return instance;
}

LearningConfigModel* LrnConfMdlParser::load(QString path) const{

}

bool LrnConfMdlParser::save(LearningConfigModel* project) const{

}

}
