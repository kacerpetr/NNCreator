#include "DatasetTestMdlParser.h"

namespace Parsers{

DatasetTestMdlParser::DatasetTestMdlParser(){}

DatasetTestMdlParser& DatasetTestMdlParser::get(){
	static DatasetTestMdlParser instance;
	return instance;
}

DatasetTestModel* DatasetTestMdlParser::load(QString path) const{

}

bool DatasetTestMdlParser::save(DatasetTestModel* project) const{

}

}
