#include "Project.h"
#include "NeuralNetwork/BasicNetwork.h"
#include "NeuralNetwork/TrainingPattern.h"
#include "NeuralNetwork/BackPropagation.h"

namespace Project{

Project::Project() : path(QString()), name(QString()){}

Project::Project(QString path, QString name) : path(path), name(name){}

Project::~Project(){
	for(int i = 0; i < neuralNetwork.length(); i++) delete neuralNetwork[i];
	for(int i = 0; i < trainingPattern.length(); i++) delete trainingPattern[i];
	for(int i = 0; i < learningConfig.length(); i++) delete learningConfig[i];
	for(int i = 0; i < testingScenario.length(); i++) delete testingScenario[i];
}


QString Project::getName() const{
	return name;
}

QString Project::getPath() const{
	return path;
}

void Project::setName(QString name){
	this->name = name;
}

void Project::setPath(QString path){
	this->path = path;
}


TrainingPatternModel* Project::getTrainingPattern(int index){
	return trainingPattern[index];
}

NeuralNetworkModel* Project::getNeuralNetwork(int index){
	return neuralNetwork[index];
}

LearningConfigModel* Project::getLearningConfig(int index){
	return learningConfig[index];
}

TestingScenarioModel* Project::getTestingScenario(int index){
	return testingScenario[index];
}


int Project::getTrainingPatternCount() const{
	return trainingPattern.length();
}

int Project::getNeuralNetworkCount() const{
	return neuralNetwork.length();
}

int Project::getLearningConfigCount() const{
	return learningConfig.length();
}

int Project::getTestingScenarioCount() const{
	return testingScenario.length();
}


void Project::createTrainingPattern(QString name){
	TrainingPatternModel* model = new TrainingPatternModel();
	model->setName(name);
	trainingPattern.append(model);
}

void Project::createNeuralNetwork(QString name){
	NeuralNetworkModel* model = new NeuralNetworkModel();
	model->setName(name);
	neuralNetwork.append(model);
}

void Project::createLearningConfig(QString name){
	LearningConfigModel* model = new LearningConfigModel();
	model->setName(name);
	learningConfig.append(model);
}

void Project::createTestingScenario(QString name){
	TestingScenarioModel* model = new TestingScenarioModel();
	model->setName(name);
	testingScenario.append(model);
}


void Project::removeTrainingPattern(int index){
	delete trainingPattern[index];
	trainingPattern.removeAt(index);
}

void Project::removeNeuralNetwork(int index){
	delete neuralNetwork[index];
	neuralNetwork.removeAt(index);
}

void Project::removeLearningConfig(int index){
	delete learningConfig[index];
	learningConfig.removeAt(index);
}

void Project::removeTestingScenario(int index){
	delete testingScenario[index];
	testingScenario.removeAt(index);
}


QString Project::getTrainingPatternName(int index) const{
	return trainingPattern[index]->getName();
}

QString Project::getNeuralNetworkName(int index) const{
	return neuralNetwork[index]->getName();
}

QString Project::getLearningConfigName(int index) const{
	return learningConfig[index]->getName();
}

QString Project::getTestingScenarioName(int index) const{
	return testingScenario[index]->getName();
}

}
