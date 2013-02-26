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
		/** Creates empty dataset. */
		Dataset();

		/** Creates copy of given dataset. */
		Dataset(const Dataset& obj);

		/** Sets minimal size of dataset. */
		void setMinSize(int patternCount, int inputCount, int outputCount);

		/** Sets minimal pattern count in dataset. */
		void setMinPaternCount(int patternCount);

		/** Sets minimal length of input vector. */
		void setMinInputCount(int inputCount);

		/** Sets minimal length of output vector. */
		void setMinOutputCount(int outputCount);

		/** Returns real pattern count. */
		int patternCount() const;

		/** Returns real length of input vector in given pattern. */
		int inputCount() const;

		/** Returns real length of output vector in given pattern. */
		int outputCount() const;

		/** Returns minimal pattern count. */
		int minPatternCount() const;

		/** Returns minimal length of input vector. */
		int minInputCount() const;

		/** Returns minimal length of output vector. */
		int minOutputCount() const;

		/** Reduces dataset size by deleting items beyond minimal dataset size. */
		void reduceToMinSize();

		/** Sets value of input in given pattern. */
		void setInput(int pattern, int index, double value);

		/** Sets value of output in given pattern. */
		void setOutput(int pattern, int index, double value);

		/** Returns value of input in given pattern or 0 if value is undefined. */
		double input(int pattern, int index) const;

		/** Returns value of output in given pattern or 0 if value is undefined. */
		double output(int pattern, int index) const;

		/** Returns whole input vector as a list of all input values in pattern. */
		QList<double> inputVector(int pattern) const;

		/** Returns whole output vector as a list of all output values in pattern. */
		QList<double> outputVector(int pattern) const;

		/** Checks if given input in given pattern is defined. */
		bool isInputNull(int pattern, int index) const;

		/** Checks if given output in given pattern is defined. */
		bool isOutputNull(int pattern, int index) const;

		void clearInput(int pattern, int index);

		void clearOutput(int pattern, int index);

		/**
		 * Checks if dataset is consitent.
		 * Dataset is consistent if all items in range between zero and minimal
		 * pattern count or minimal input or output vector length are defined.
		 */
		bool isConsistent() const;

		/** Returns string representation of dataset. */
		QString toString() const;

		/** Class destructor. */
		~Dataset();

	private:
		/** Removes last pattern in dataset. */
		void removeLastPattern();
		/** Reduces lengths of input and output vectors to minimal size. */
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
