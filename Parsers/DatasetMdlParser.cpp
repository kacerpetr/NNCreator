#include "DatasetMdlParser.h"

namespace Parsers{

DatasetMdlParser::DatasetMdlParser(){}

DatasetMdlParser& DatasetMdlParser::get(){
	static DatasetMdlParser instance;
	return instance;
}

DatasetEditModel* DatasetMdlParser::load(QString path) const{

}

bool DatasetMdlParser::save(DatasetEditModel* project) const{

}

}
