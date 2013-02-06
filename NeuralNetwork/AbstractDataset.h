#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H

#include <QList>

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Interface for dataset of learning or testing patterns.
 */
class AbstractDataset{
	public:
		/** Appends empty pattern. */
		virtual void appendPattern() = 0;

		/** Appends count of empty patterns. */
		virtual void appendPattern(int count) = 0;

		/** Removes pattern at given index. */
		virtual void removePattern(int patternIndex) = 0;

		/** Clears pattern at given index. */
		virtual void clearPattern(int patternIndex) = 0;

		/** Appends count of inputs of given value at given pattern. */
		virtual void appendInputs(int patternIndex, int count, double value) = 0;

		/** Appends count of outputs of given value at given pattern. */
		virtual void appendOutputs(int patternIndex, int count, double value) = 0;

		/** Sets all inputs in pattern. */
		virtual void setInputVector(int patternIndex, const QList<double>& inputVector) = 0;

		/** Sets all outputs in pattern. */
		virtual void setOutputVector(int patternIndex, const QList<double>& outputVector) = 0;

		/** Returns list of inputs in given pattern. */
		virtual QList<double> getInputVector(int patternIndex) const = 0;

		/** Returns list of ouputs in given pattern. */
		virtual QList<double> getOutputVector(int patternIndex) const = 0;

		/** Returns count of patterns in dataset. */
		virtual int patternCount() const = 0;

		/** Returns count of inputs in given pattern. */
		virtual int inputCount(int patternIndex) const = 0;

		/** Returns count of outputs in given pattern. */
		virtual int outputCount(int patternIndex) const = 0;

		/** Returns reference to list of inputs in given pattern. */
		virtual QList<double>& operator[](int patternIndex) = 0;

		/** Returns reference to list of outputs in given pattern. */
		virtual QList<double>& operator()(int patternIndex) = 0;

		/** Returns string representation of dataset. */
		virtual QString toString() const = 0;
};

}

#endif //ABSTRACTDATASET_H
