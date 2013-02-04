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

void Dataset::appendPattern(int count){
	Q_ASSERT(count >= 0);
	for(int i = 0; i < count; i++){
		input.append(QList<double>());
		output.append(QList<double>());
	}
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

void Dataset::setInputVector(int patternIndex, const QList<double>& inputVector){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	input[patternIndex] = inputVector;
}

void Dataset::setOutputVector(int patternIndex, const QList<double>& outputVector){
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
	output[patternIndex] = outputVector;
}

QList<double> Dataset::getInputVector(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return input[patternIndex];
}

QList<double> Dataset::getOutputVector(int patternIndex) const{
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
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
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
	return output[patternIndex].length();
}

QList<double>& Dataset::operator[](int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < input.length());
	return input[patternIndex];
}

QList<double>& Dataset::operator()(int patternIndex){
	Q_ASSERT(patternIndex >= 0 && patternIndex < output.length());
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
