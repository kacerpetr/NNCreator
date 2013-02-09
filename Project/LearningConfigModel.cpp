#include "LearningConfigModel.h"

namespace Project{

LearningConfigModel::LearningConfigModel() : BaseModel(LearningConfig){}

void LearningConfigModel::save(){
	mdlSaved = true;
}

void LearningConfigModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void LearningConfigModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}


}
