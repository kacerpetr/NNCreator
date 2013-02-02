#include "Dataset.h"

namespace NeuralNetwork{

Dataset::Dataset() : AbstractDataset(){}

Dataset::Dataset(const Dataset& obj) : AbstractDataset(){
	input = obj.input;
	output = obj.output;
	Q_ASSERT(input.length() == output.length());
}

void Dataset::appendPattern(){
	input.append(QList<double>());
	output.append(QList<double>());
	Q_ASSERT(input.length() == output.length());
}

void Dataset::removePattern(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input.removeAt(patternIndex);
	output.removeAt(patternIndex);
	Q_ASSERT(input.length() == output.length());
}

void Dataset::clearPattern(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input[patternIndex].clear();
	output[patternIndex].clear();
	Q_ASSERT(input.length() == output.length());
}

void Dataset::clearInputs(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input[patternIndex].clear();
}

void Dataset::clearOutputs(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
	output[patternIndex].clear();
}

void Dataset::appendInputs(int patternIndex, int count, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(count >= 0);
	for(int i = 0; i < count; i++){
		input[patternIndex].append(value);
	}
}

void Dataset::appendOutputs(int patternIndex, int count, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
	Q_ASSERT(count >= 0);
	for(int i = 0; i < count; i++){
		output[patternIndex].append(value);
	}
}

void Dataset::appendInput(int patternIndex, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input[patternIndex].append(value);
}

void Dataset::appendOutput(int patternIndex, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	output[patternIndex].append(value);
}

void Dataset::removeInput(int patternIndex, int inputIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(inputIndex >= 0 && inputIndex < input[patternIndex].length());
	input[patternIndex].removeAt(inputIndex);
}

void Dataset::removeOutput(int patternIndex, int outputIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(outputIndex >= 0 && outputIndex < output[patternIndex].length());
	output[patternIndex].removeAt(outputIndex);
}

void Dataset::setInput(int patternIndex, int inputIndex, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(inputIndex >= 0 && inputIndex < input[patternIndex].length());
	input[patternIndex][inputIndex] = value;
}

void Dataset::setOutput(int patternIndex, int outputIndex, double value){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(outputIndex >= 0 && outputIndex < output[patternIndex].length());
	output[patternIndex][outputIndex] = value;
}

double Dataset::getInput(int patternIndex, int inputIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(inputIndex >= 0 && inputIndex < input[patternIndex].length());
	return input[patternIndex][inputIndex];
}

double Dataset::getOutput(int patternIndex, int outputIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	Q_ASSERT(outputIndex >= 0 && outputIndex < output[patternIndex].length());
	return output[patternIndex][outputIndex];
}

void Dataset::setInputVector(int patternIndex, const QList<double>& inputVector){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input[patternIndex] = inputVector;
}

void Dataset::setOutputVector(int patternIndex, const QList<double>& outputVector){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	output[patternIndex] = outputVector;
}

QList<double> Dataset::getInputVector(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return input[patternIndex];
}

QList<double> Dataset::getOutputVector(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return output[patternIndex];
}

int Dataset::patternCount() const{
	return input.length();
}

int Dataset::inputCount(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return input[patternIndex].length();
}

int Dataset::outputCount(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return output[patternIndex].length();
}

QList<double>& Dataset::operator[](int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return input[patternIndex];
}

QList<double>& Dataset::operator()(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return output[patternIndex];
}

QString Dataset::toString() const{
	Q_ASSERT(input.length() == output.length());
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
