#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>
#include "AbstractDataset.h"

namespace NeuralNetwork{

class Dataset : public AbstractDataset{
	public:
		Dataset();
		Dataset(const Dataset& obj);
		void appendPattern();
		void removePattern(int patternIndex);
		void clearPattern(int patternIndex);
		void clearInputs(int patternIndex);
		void clearOutputs(int patternIndex);
		void appendInputs(int patternIndex, int count, double value);
		void appendOutputs(int patternIndex, int count, double value);
		void appendInput(int patternIndex, double value);
		void appendOutput(int patternIndex, double value);
		void removeInput(int patternIndex, int inputIndex);
		void removeOutput(int patternIndex, int outputIndex);
		void setInput(int patternIndex, int inputIndex, double value);
		void setOutput(int patternIndex, int outputIndex, double value);
		double getInput(int patternIndex, int inputIndex) const;
		double getOutput(int patternIndex, int outputIndex) const;
		void setInputVector(int patternIndex, const QList<double>& inputVector);
		void setOutputVector(int patternIndex, const QList<double>& outputVector);
		QList<double> getInputVector(int patternIndex) const;
		QList<double> getOutputVector(int patternIndex) const;
		int patternCount() const;
		int inputCount(int patternIndex) const;
		int outputCount(int patternIndex) const;
		QString toString() const;
		~Dataset();

	private:
		QList< QList<double> > input;
		QList< QList<double> > output;
};

}

#endif //DATASET_H
