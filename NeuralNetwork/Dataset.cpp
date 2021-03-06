/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Dataset.h"
#include <QDebug>

namespace NeuralNetwork{

/**
 * Creates empty dataset.
 */
Dataset::Dataset(): patternCnt(0), inputCnt(0), outputCnt(0){}

/**
 * Creates copy of given dataset.
 */
Dataset::Dataset(const Dataset& obj){
    //sets size of dataset
    setMinSize(obj.minPatternCount(), obj.minInputCount(), obj.minOutputCount());

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
            if(!obj.isOutputNull(i,j)) setOutput(i, j, obj.output(i, j));
		}
	}
}

/**
 * Sets minimal size of dataset.
 */
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

/**
 * Sets minimal pattern count in dataset.
 */
void Dataset::setMinPaternCount(int patternCount){
	Q_ASSERT(patternCount >= 0);
    setMinSize(patternCount, inputCnt, outputCnt);
}

/**
 * Sets minimal length of input vector.
 */
void Dataset::setMinInputCount(int inputCount){
	Q_ASSERT(inputCount >= 0);
	setMinSize(patternCnt, inputCount, outputCnt);
}

/**
 * Sets minimal length of output vector.
 */
void Dataset::setMinOutputCount(int outputCount){
	Q_ASSERT(outputCount >= 0);
	setMinSize(patternCnt, inputCnt, outputCount);
}

/**
 * Returns real pattern count.
 */
int Dataset::patternCount() const{
	Q_ASSERT(inputList.length() == outputList.length());
	return inputList.length();
}

/**
 * Returns real length of input vector in given pattern.
 */
int Dataset::inputCount(int pattern) const{
	Q_ASSERT(inputList.length() == outputList.length());
	if(inputList.isEmpty()) return 0;
	return inputList[0].length();
}

/**
 * Returns real length of output vector in given pattern.
 */
int Dataset::outputCount(int pattern) const{
	Q_ASSERT(inputList.length() == outputList.length());
	if(outputList.isEmpty()) return 0;
	return outputList[0].length();
}

/**
 * Returns minimal pattern count.
 */
int Dataset::minPatternCount() const{
	return patternCnt;
}

/**
 * Returns minimal length of input vector.
 */
int Dataset::minInputCount() const{
	return inputCnt;
}

/**
 * Returns minimal length of output vector.
 */
int Dataset::minOutputCount() const{
	return outputCnt;
}

/**
 * Reduces dataset size by deleting items beyond minimal dataset size.
 */
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

/**
 * Sets value of input in given pattern.
 */
void Dataset::setInput(int pattern, int index, double value){
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	if(inputList[pattern][index] == NULL){
		inputList[pattern][index] = new double;
	}
	*inputList[pattern][index] = value;
}

/**
 * Sets value of output in given pattern.
 */
void Dataset::setOutput(int pattern, int index, double value){
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	if(outputList[pattern][index] == NULL){
		outputList[pattern][index] = new double;
	}
	*outputList[pattern][index] = value;
}

/**
 * Returns value of input in given pattern or 0 if value is undefined.
 */
double Dataset::input(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	return inputList[pattern][index] == NULL ? 0.0 : *inputList[pattern][index];
}

/**
 * Returns value of output in given pattern or 0 if value is undefined.
 */
double Dataset::output(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	Q_ASSERT(index >= 0 && index < outputList[pattern].length());
	return outputList[pattern][index] == NULL ? 0.0 : *outputList[pattern][index];
}

/**
 * Returns whole input vector as a list of all input values in pattern.
 */
QList<double> Dataset::inputVector(int pattern) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	QList<double> result;
	for(int i = 0; i < inputList[pattern].length(); i++){
		result.append(input(pattern,i));
	}
	return result;
}

/**
 * Returns whole output vector as a list of all output values in pattern.
 */
QList<double> Dataset::outputVector(int pattern) const{
	Q_ASSERT(pattern >= 0 && pattern < outputList.length());
	QList<double> result;
	for(int i = 0; i < outputList[pattern].length(); i++){
		result.append(output(pattern,i));
	}
	return result;
}

/**
 * Checks if dataset is consitent.
 * Dataset is consistent if all items in range between zero and minimal
 * pattern count or minimal input or output vector length are defined.
 */
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

/**
 * Checks if given input in given pattern is defined.
 */
bool Dataset::isInputNull(int pattern, int index) const{
	Q_ASSERT(pattern >= 0 && pattern < inputList.length());
	Q_ASSERT(index >= 0 && index < inputList[pattern].length());
	return (inputList[pattern][index] == NULL);
}

/**
 * Checks if given output in given pattern is defined.
 */
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

/**
 * Returns string representation of dataset.
 */
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

/**
 * Class destructor.
 */
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

/**
 * Removes last pattern in dataset.
 */
void Dataset::removeLastPattern(){
	Q_ASSERT(!inputList.isEmpty());
	Q_ASSERT(!outputList.isEmpty());
	for(int i = 0; i < inputList.last().length(); i++) delete inputList.last()[i];
	for(int i = 0; i < outputList.last().length(); i++)	delete outputList.last()[i];
	inputList.removeLast();
	outputList.removeLast();
}

/**
 * Reduces lengths of input and output vectors to minimal size.
 */
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
