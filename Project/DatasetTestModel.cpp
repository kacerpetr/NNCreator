#include "DatasetTestModel.h"

namespace Project {

DatasetTestModel::DatasetTestModel() : BaseModel(DatasetTest){}

void DatasetTestModel::save(){
	mdlSaved = true;
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
