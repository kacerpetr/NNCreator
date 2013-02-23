#include "DatasetTestModel.h"
#include "Parser/DatasetTestMdlParser.h"
using namespace Parser;

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
