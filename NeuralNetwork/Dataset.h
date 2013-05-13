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

#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Dataset of training and testing patterns.
 */
class Dataset{
	public:
		Dataset();
		Dataset(const Dataset& obj);
		void setMinSize(int patternCount, int inputCount, int outputCount);
		void setMinPaternCount(int patternCount);
		void setMinInputCount(int inputCount);
		void setMinOutputCount(int outputCount);
		int patternCount() const;
        int inputCount(int pattern) const;
        int outputCount(int pattern) const;
		int minPatternCount() const;
        int minInputCount() const;
		int minOutputCount() const;
		void reduceToMinSize();
		void setInput(int pattern, int index, double value);
		void setOutput(int pattern, int index, double value);
		double input(int pattern, int index) const;
		double output(int pattern, int index) const;
		QList<double> inputVector(int pattern) const;
		QList<double> outputVector(int pattern) const;
        bool isInputNull(int pattern, int index) const;
        bool isOutputNull(int pattern, int index) const;
        void clearInput(int pattern, int index);
		void clearOutput(int pattern, int index);
		bool isConsistent() const;
		QString toString() const;
		~Dataset();

	private:
		void removeLastPattern();
		void reducePattern(int pattern);

	private:
		/** List of input vectors. */
		QList< QList<double*> > inputList;
		/** List of output vectors. */
		QList< QList<double*> > outputList;
		/** Minimal count of training patterns. */
		int patternCnt;
		/** Minimal length of input vector. */
		int inputCnt;
		/** Minimal length of output vector. */
		int outputCnt;
};

}

#endif // DATASET_H
