#include "Project.h"
#include "NeuralNetwork/BasicNetwork.h"
#include "NeuralNetwork/TrainingPattern.h"
#include "NeuralNetwork/BackPropagation.h"

namespace Project{

Project::Project() : path(QString()), name(QString()){}

Project::Project(QString path, QString name) : path(path), name(name){}

AbstractNeuralNetwork* Project::getNeuralNetwork(int index){
	return neuralNetwork[index];
}

AbstractTrainingPattern* Project::getTrainingPattern(int index){
	return trainingPattern[index];
}

AbstractLearningMachine* Project::getLearningMachine(int index){
	return learningMachine[index];
}

Project::~Project(){
	for(int i = 0; i < neuralNetwork.length(); i++) delete neuralNetwork[i];
	for(int i = 0; i < trainingPattern.length(); i++) delete trainingPattern[i];
	for(int i = 0; i < learningMachine.length(); i++) delete learningMachine[i];
}

QFileInfo& Project::getNeuralNetworkFile(int index){
	return neuralNetworkFile[index];
}

QFileInfo& Project::getTrainingPatternFile(int index){
	return trainingPatternFile[index];
}

QFileInfo& Project::getLearningMachineFile(int index){
	return learningMachineFile[index];
}

int Project::getNeuralNetworkCount() const{
	return neuralNetwork.length();
}

int Project::getTrainingPatternCount() const{
	return trainingPattern.length();
}

int Project::getLearningMachineCount() const{
	return learningMachine.length();
}

int Project::getGraphCount() const{
	return 0;
}

void Project::createNeuralNetwork(){
	neuralNetwork.append(new BasicNetwork());
	neuralNetworkFile.append(QFileInfo("network"));
}

void Project::createTrainingPattern(){
	trainingPattern.append(new TrainingPattern());
	trainingPatternFile.append(QFileInfo("pattern"));
}

void Project::createLearningMachine(){
	learningMachine.append(new BackPropagation());
	learningMachineFile.append(QFileInfo("learning"));
}

void Project::removeNeuralNetwork(int index){
	delete neuralNetwork[index];
	neuralNetwork.removeAt(index);
	neuralNetworkFile.removeAt(index);
}

void Project::removeTrainingPattern(int index){
	delete trainingPattern[index];
	trainingPattern.removeAt(index);
	trainingPatternFile.removeAt(index);
}

void Project::removeLearningMachine(int index){
	delete learningMachine[index];
	learningMachine.removeAt(index);
	learningMachineFile.removeAt(index);
}

QString Project::getName() const{
	return name;
}

void Project::setName(QString name){
	this->name = name;
}

QString Project::getPath() const{
	return path;
}

void Project::setPath(QString path){
	this->path = path;
}

}
