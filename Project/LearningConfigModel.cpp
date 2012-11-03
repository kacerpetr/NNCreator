#include "LearningConfigModel.h"

LearningConfigModel::LearningConfigModel(){}

void LearningConfigModel::setName(QString name){
	this->name = name;
}

QString LearningConfigModel::getName() const{
	return name;
}
