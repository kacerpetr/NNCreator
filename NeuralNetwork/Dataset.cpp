#include "Dataset.h"
#include <QDebug>

namespace NeuralNetwork{

Dataset::Dataset(): patternCnt(0), inputCnt(0), outputCnt(0){}

Dataset::Dataset(const Dataset& obj): patternCnt(obj.patternCnt), inputCnt(obj.inputCnt), outputCnt(obj.outputCnt){
	//creates empty patterns
	for(int i = 0; i < obj.inputList.length(); i++)	inputList.append(QList<double*>());
	for(int i = 0; i < obj.outputList.length(); i++) outputList.append(QList<double*>()
																	   );
	//makes copy of input vectors
	for(int i = 0; i < inputList.length(); i++){
		for(int j = 0; j < obj.inputList[i].length(); j++){
			inputList[i].append(NULL);
			if(!obj.isInputNull(i,j)) setInput(i, j, obj.input(i, j));
		}
	}

	//makes copy of output vectors
	for(int i = 0; i < outputList.length(); i++){
		for(int j = 0; j < obj.outputList[i].length(); j++){
			outputList[i].append(NULL);
			if(!obj.isOutputNull(i,j)) setOutput(i, j, obj.input(i, j));
		}
	}
}

void Dataset::setMinSize(int patternCount, int inputCount, int outputCount){
	//input check
	Q_ASSERT(patternCount >= 0);
	Q_ASSERT(inputCount >= 0);
	Q_ASSERT(outputCount >= 0);

	//sets internal variables
	patternCnt = patternCount;
	inputCnt = inputCount;
	outputCnt = outputCount;

	//adds pattern to get required pattern count
	Q_ASSERT(inputList.length() == outputList.length());
	if(patternCnt > inputList.length()){
		int len = patternCnt-inputList.length();
		for(int i = 0; i < len; i++){
			inputList.append(QList<double*>());
			outputList.append(QList<double*>());
		}
	}

	//adjusts input and output vectors length
	Q_ASSERT(inputList.length() == outputList.length());
	for(int i = 0; i < inputList.length(); i++){
		//adds inputs to get required input vector length
		if(inputCnt > inputList[i].length()){
			int len = inputCnt-inputList[i].length();
			for(int j = 0; j < len; j++){
				inputList[i].append(NULL);
			}
		}
		//adds outputs to get required output vector length
		if(outputCnt > outputList[i].length()){
			int len = outputCnt-outputList[i].length();
			for(int j = 0; j < len; j++){
				outputList[i].append(NULL);
			}
		}
	}
}

void Dataset::setMinPaternCount(int patternCount){
	Q_ASSERT(patternCount >= 0);
	setMinSize(patternCount, inputCnt, outputCnt);
}

void Dataset::setMinInputCount(int inputCount){
	Q_ASSERT(inputCount >= 0);
	setMinSize(patternCnt, inputCount, outputCnt);
}

void Dataset::setMinOutputCount(int outputCount){
	Q_ASSERT(outputCount >= 0);
	setMinSize(patternCnt, inputCnt, outputCount);
}

int Dataset::patternCount() const{
	Q_ASSERT(inputList.length() == outputList.length());
	return inputList.length();
}

int Dataset::inputCount() const{
	Q_ASSERT(inputList.length() == outputList.length());
	if(inputList.isEmpty()) return 0;
	return inputList[0].length();
}

int Dataset::outputCount() const{
	Q_ASSERT(inputList.length() == outputList.length());
	if(outputList.isEmpty()) return 0;
	return outputList[0].length();
}

int Dataset::minPatternCount() const{
	return patternCnt;
}

int Dataset::minInputCount() const{
	return inputCnt;
}

int Dataset::minOutputCount() const{
	return outputCnt;
}

void Dataset::reduceToMinSize(){
	Q_ASSERT(inputList.length() == outputList.length());

	//removes redundand patterns
	if(inputList.length() > patternCnt){
		int len = inputList.length()-patternCnt;
		for(int i = 0; i < len; i++){
			removeLastPattern();
		}
	}

	//reduces single patterns to their minimum size
	for(int i = 0; i < inputList.length(); i++) reducePattern(i);
}

void Dataset::setInput(int pattern, int index, double value){
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	if(inputList[pattern][index] == NULL){
		inputList[pattern][index] = new double;
	}
	*inputList[pattern][index] = value;
}

void Dataset::setOutput(int pattern, int index, double value){
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	if(outputList[pattern][index] == NULL){
		outputList[pattern][index] = new double;
	}
	*outputList[pattern][index] = value;
}

double Dataset::input(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	return inputList[pattern][index] == NULL ? 0.0 : *inputList[pattern][index];
}

double Dataset::output(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	return outputList[pattern][index] == NULL ? 0.0 : *outputList[pattern][index];
}

QList<double> Dataset::inputVector(int pattern) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	QList<double> result;
	for(int i = 0; i < inputList[pattern].length(); i++){
		result.append(input(pattern,i));
	}
	return result;
}

QList<double> Dataset::outputVector(int pattern) const{
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	QList<double> result;
	for(int i = 0; i < outputList[pattern].length(); i++){
		result.append(output(pattern,i));
	}
	return result;
}

bool Dataset::isConsistent() const{
	//checks inputs
	for(int i = 0; i < patternCnt; i++){
		for(int j = 0; j < inputCnt; j++){
			if(inputList[i][j] == NULL) return false;
		}
	}

	//checks outputs
	for(int i = 0; i < patternCnt; i++){
		for(int j = 0; j < outputCnt; j++){
			if(outputList[i][j] == NULL) return false;
		}
	}

	//dataset does not countain NULL values
	return true;
}

bool Dataset::isInputNull(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	return (inputList[pattern][index] == NULL);
}

bool Dataset::isOutputNull(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	return (outputList[pattern][index] == NULL);
}

void Dataset::clearInput(int pattern, int index){
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	delete inputList[pattern][index];
	inputList[pattern][index] = NULL;
}

void Dataset::clearOutput(int pattern, int index){
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	delete outputList[pattern][index];
	outputList[pattern][index] = NULL;
}

QString Dataset::toString() const{
	Q_ASSERT(inputList.length() == outputList.length());
	QString str;
	for(int i = 0; i < inputList.length(); i++){
		str += QString("Pattern ") + QString::number(i) + ":\n";
		for(int j = 0; j < inputList[i].length(); j++){
			str += QString("  input") + "[" + QString::number(j) + "]:";
			str += isInputNull(i,j) ? "NULL" : QString::number(input(i,j));
			str += QString("\n");
		}
		for(int j = 0; j < outputList[i].length(); j++){
			str += QString("  output") + "[" + QString::number(j) + "]:";
			str += isOutputNull(i,j) ? "NULL" : QString::number(output(i,j));
			str += QString("\n");
		}
	}
	return str;
}

Dataset::~Dataset(){
	//unallocates input vectors values
	for(int i = 0; i < inputList.length(); i++){
		for(int j = 0; j < inputList[i].length(); j++){
			delete inputList[i][j];
		}
	}

	//unallocates output vectors values
	for(int i = 0; i < outputList.length(); i++){
		for(int j = 0; j < outputList[i].length(); j++){
			delete outputList[i][j];
		}
	}
}

void Dataset::removeLastPattern(){
	Q_ASSERT(!inputList.isEmpty());
	Q_ASSERT(!outputList.isEmpty());
	for(int i = 0; i < inputList.last().length(); i++) delete inputList.last()[i];
	for(int i = 0; i < outputList.last().length(); i++)	delete outputList.last()[i];
	inputList.removeLast();
	outputList.removeLast();
}

void Dataset::reducePattern(int pattern){
	//reduces input vector length
	if(inputList[pattern].length() > inputCnt){
		int len = inputList[pattern].length();
		for(int i = len-1; i >= inputCnt; i--){
			delete inputList[pattern][i];
			inputList[pattern].removeLast();
		}
	}

	//reduces output vector length
	if(outputList[pattern].length() > outputCnt){
		int len = outputList[pattern].length();
		for(int i = len-1; i >= outputCnt; i--){
			delete outputList[pattern][i];
			outputList[pattern].removeLast();
		}
	}
}

}
