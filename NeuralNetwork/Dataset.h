#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>
#include "AbstractDataset.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Dataset of training and testing patterns.
 */
class Dataset : public AbstractDataset{
	public:
		Dataset();
		Dataset(const Dataset& obj);
		void appendPattern();
		void appendPattern(int count);
		void removePattern(int patternIndex);
		void clearPattern(int patternIndex);
		void appendInputs(int patternIndex, int count, double value);
		void appendOutputs(int patternIndex, int count, double value);
		void setInputVector(int patternIndex, const QList<double>& inputVector);
		void setOutputVector(int patternIndex, const QList<double>& outputVector);
		QList<double> getInputVector(int patternIndex) const;
		QList<double> getOutputVector(int patternIndex) const;
		int patternCount() const;
		int inputCount(int patternIndex) const;
		int outputCount(int patternIndex) const;
		QList<double>& operator[](int patternIndex);
		QList<double>& operator()(int patternIndex);
		QString toString() const;
		~Dataset();

	private:
		QList< QList<double> > input;
		QList< QList<double> > output;
};

}

#endif //DATASET_H
