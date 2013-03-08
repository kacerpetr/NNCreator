#include "DatasetEditModel.h"
#include "Parser/DatasetMdlParser.h"
using namespace Parser;

namespace ProjectData{

DatasetEditModel::DatasetEditModel() : BaseModel(DatasetEdit), viewMdl(NULL){
	viewMdl = new DatasetViewModel(this, this);
	setPatternCount(1);
	setInputCount(1);
	setOutputCount(1);
}

DatasetEditModel::~DatasetEditModel(){
	delete viewMdl;
}

void DatasetEditModel::save(){
	reduceToMinSize();
	DatasetMdlParser& parser = DatasetMdlParser::get();
	setSaved(parser.save(this));
	viewMdl->emitLayoutChanged();
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
