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
		int inputCount() const;
		int outputCount() const;
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
