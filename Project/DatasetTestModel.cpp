#include "DatasetTestModel.h"
#include "Parsers/DatasetTestMdlParser.h"
using namespace Parsers;

namespace ProjectData {

DatasetTestModel::DatasetTestModel() : BaseModel(DatasetTest){}

void DatasetTestModel::save(){
	DatasetTestMdlParser& parser = DatasetTestMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void DatasetTestModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void DatasetTestModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}


}
