#include "TestingScenarioModel.h"

namespace Project{

TestingScenarioModel::TestingScenarioModel(TestingScenarioType type) : type(type){
	datasetModel = new TrainingPatternModel();
}

TestingScenarioModel::~TestingScenarioModel(){
	delete datasetModel;
}

void TestingScenarioModel::setName(QString name){
	this->name = name;
}

QString TestingScenarioModel::getName() const{
	return name;
}

TrainingPatternModel* TestingScenarioModel::getDatasetModel(){
	return datasetModel;
}

TestingScenarioType TestingScenarioModel::getType(){
	return type;
}

}
