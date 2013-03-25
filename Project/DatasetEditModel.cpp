#include "DatasetEditModel.h"
#include "Parser/DatasetMdlParser.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

/**
 * DatasetEditModel class constructor.
 */
DatasetEditModel::DatasetEditModel() : BaseModel(DatasetEdit), viewMdl(NULL){
	viewMdl = new DatasetViewModel(this, this);
	connect(viewMdl, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged()));
	setPatternCount(1);
	setInputCount(1);
	setOutputCount(1);
}

/**
 * Class destructor.
 */
DatasetEditModel::~DatasetEditModel(){
	delete viewMdl;
}

/**
 * Saves model to file.
 */
void DatasetEditModel::save(){
	reduceToMinSize();
	DatasetMdlParser& parser = DatasetMdlParser::get();
	setSaved(parser.save(this));
	viewMdl->emitLayoutChanged();
}

/**
 * Sets pattern count of dataset.
 */
void DatasetEditModel::setPatternCount(int count){
	setMinPaternCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Sets output count of dataset.
 */
void DatasetEditModel::setInputCount(int count){
	setMinInputCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Sets input count of dataset.
 */
void DatasetEditModel::setOutputCount(int count){
	setMinOutputCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Returns dataset table view model.
 */
DatasetViewModel* DatasetEditModel::viewModel(){
	return viewMdl;
}

void DatasetEditModel::dataChanged(){
	setSaved(false);
}

}
