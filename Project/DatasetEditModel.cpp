#include "DatasetEditModel.h"
#include "Parser/DatasetMdlParser.h"
using namespace Parser;

namespace ProjectData{

DatasetEditModel::DatasetEditModel() : BaseModel(DatasetEdit), viewMdl(NULL){
	viewMdl = new DatasetViewModel(this, this);
}

DatasetEditModel::~DatasetEditModel(){
	delete viewMdl;
}

void DatasetEditModel::save(){
	DatasetMdlParser& parser = DatasetMdlParser::get();
	setSaved(parser.save(this));
}

void DatasetEditModel::setPatternCount(int count){
	setMinPaternCount(count);
	viewMdl->emitLayoutChanged();
}

void DatasetEditModel::setInputCount(int count){
	setMinInputCount(count);
	viewMdl->emitLayoutChanged();
}

void DatasetEditModel::setOutputCount(int count){
	setMinOutputCount(count);
	viewMdl->emitLayoutChanged();
}

DatasetViewModel* DatasetEditModel::viewModel(){
	return viewMdl;
}

}
