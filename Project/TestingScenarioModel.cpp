#include "TestingScenarioModel.h"

TestingScenarioModel::TestingScenarioModel(){}

void TestingScenarioModel::setName(QString name){
	this->name = name;
}

QString TestingScenarioModel::getName() const{
	return name;
}
