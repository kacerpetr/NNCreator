#include "TrainingPattern.h"

namespace NeuralNetwork{

TrainingPattern::TrainingPattern(){}

TrainingPattern::TrainingPattern(const TrainingPattern& obj){
	input = obj.input;
	output = obj.output;
}

TrainingPattern::TrainingPattern(const QString& str){

}

void TrainingPattern::appendPattern(){
	input.push_back(QList<double>());
	output.push_back(QList<double>());
}

void TrainingPattern::appendValue(unsigned int pattern, double input, double output){
	this->input[pattern].push_back(input);
	this->output[pattern].push_back(output);
}

void TrainingPattern::removePattern(unsigned int index){
	this->input.removeAt(index);
	this->output.removeAt(index);
}

unsigned int TrainingPattern::patternCount(){
	return input.size();
}

unsigned int TrainingPattern::itemCount(unsigned int pattern){
	return input[pattern].size();
}

double TrainingPattern::getInput(unsigned int pattern, unsigned int index){
	return input[pattern][index];
}

double TrainingPattern::getOutput(unsigned int pattern, unsigned int index){
	return output[pattern][index];
}

QString TrainingPattern::toString(){
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

}
