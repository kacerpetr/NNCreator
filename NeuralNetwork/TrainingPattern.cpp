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
	input.push_back(std::vector<double>());
	output.push_back(std::vector<double>());
}

void TrainingPattern::appendValue(unsigned int pattern, double input, double output){
	this->input[pattern].push_back(input);
	this->output[pattern].push_back(output);
}

void TrainingPattern::removePattern(unsigned int index){
	std::vector< std::vector<double> >::iterator it1 = this->input.begin() + index;
	this->input.erase(it1);

	std::vector< std::vector<double> >::iterator it2 = this->output.begin() + index;
	this->output.erase(it2);
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

std::vector<double> TrainingPattern::getInput(unsigned int pattern){
	return input[pattern];
}

std::vector<double> TrainingPattern::getOutput(unsigned int pattern){
	return output[pattern];
}

QString TrainingPattern::toString(){
	QString str;
	for(unsigned int i = 0; i < input.size(); i++){
		str += QString("Pattern ") + QString::number(i) + ":\n";
		for(unsigned int j = 0; j < input[i].size(); j++){
			str += QString("input=") + QString::number(input[i][j]);
			str += QString(" <-> output=") + QString::number(output[i][j]);
			str += QString("\n");
		}
	}
	return str;
}

}
