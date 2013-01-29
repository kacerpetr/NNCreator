#include "Dataset.h"

namespace NeuralNetwork{

Dataset::Dataset() : AbstractDataset(){}

Dataset::Dataset(const Dataset& obj) : AbstractDataset(){
	input = obj.input;
	output = obj.output;
}

void Dataset::appendPattern(){
	input.append(QList<double>());
	output.append(QList<double>());
}

void Dataset::removePattern(int patternIndex){
	input.removeAt(patternIndex);
	output.removeAt(patternIndex);
}

void Dataset::clearPattern(int patternIndex){
	input[patternIndex].clear();
	output[patternIndex].clear();
}

void Dataset::clearInputs(int patternIndex){
	input[patternIndex].clear();
}

void Dataset::clearOutputs(int patternIndex){
	output[patternIndex].clear();
}

void Dataset::appendInputs(int patternIndex, int count, double value){
	for(int i = 0; i < count; i++){
		input[patternIndex].append(value);
	}
}

void Dataset::appendOutputs(int patternIndex, int count, double value){
	for(int i = 0; i < count; i++){
		output[patternIndex].append(value);
	}
}

void Dataset::appendInput(int patternIndex, double value){
	input[patternIndex].append(value);
}

void Dataset::appendOutput(int patternIndex, double value){
	output[patternIndex].append(value);
}

void Dataset::removeInput(int patternIndex, int inputIndex){
	input[patternIndex].removeAt(inputIndex);
}

void Dataset::removeOutput(int patternIndex, int outputIndex){
	output[patternIndex].removeAt(outputIndex);
}

void Dataset::setInput(int patternIndex, int inputIndex, double value){
	input[patternIndex][inputIndex] = value;
}

void Dataset::setOutput(int patternIndex, int outputIndex, double value){
	output[patternIndex][outputIndex] = value;
}

double Dataset::getInput(int patternIndex, int inputIndex) const{
	return input[patternIndex][inputIndex];
}

double Dataset::getOutput(int patternIndex, int outputIndex) const{
	return output[patternIndex][outputIndex];
}

void Dataset::setInputVector(int patternIndex, const QList<double>& inputVector){
	input[patternIndex] = inputVector;
}

void Dataset::setOutputVector(int patternIndex, const QList<double>& outputVector){
	output[patternIndex] = outputVector;
}

QList<double> Dataset::getInputVector(int patternIndex) const{
	return input[patternIndex];
}

QList<double> Dataset::getOutputVector(int patternIndex) const{
	return output[patternIndex];
}

int Dataset::patternCount() const{
	return input.length();
}

int Dataset::inputCount(int patternIndex) const{
	return input[patternIndex].length();
}

int Dataset::outputCount(int patternIndex) const{
	return output[patternIndex].length();
}

QString Dataset::toString() const{
	QString str;
	for(int i = 0; i < input.length(); i++){
		str += QString("Pattern ") + QString::number(i) + ":\n";
		for(int j = 0; j < input[i].length(); j++){
			str += QString("input=") + QString::number(input[i][j]);
			str += QString(" <-> output=") + QString::number(output[i][j]);
			str += QString("\n");
		}
	}
	return str;
}

Dataset::~Dataset(){}

}
