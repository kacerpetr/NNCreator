#include "LearningConfigModel.h"
#include "Parsers/LrnConfMdlParser.h"
using namespace Parsers;

namespace Project{

LearningConfigModel::LearningConfigModel() : BaseModel(LearningConfig){}

void LearningConfigModel::save(){
	LrnConfMdlParser& parser = LrnConfMdlParser::get();
	parser.save(this);
	setSaved(true);
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
