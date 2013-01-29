#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H

#include <QList>

namespace NeuralNetwork{

class AbstractDataset{
	public:
		virtual void appendPattern() = 0;
		virtual void removePattern(int patternIndex) = 0;
		virtual void clearPattern(int patternIndex) = 0;
		virtual void clearInputs(int patternIndex) = 0;
		virtual void clearOutputs(int patternIndex) = 0;
		virtual void appendInputs(int patternIndex, int count, double value) = 0;
		virtual void appendOutputs(int patternIndex, int count, double value) = 0;
		virtual void appendInput(int patternIndex, double value) = 0;
		virtual void appendOutput(int patternIndex, double value) = 0;
		virtual void removeInput(int patternIndex, int inputIndex) = 0;
		virtual void removeOutput(int patternIndex, int outputIndex) = 0;
		virtual void setInput(int patternIndex, int inputIndex, double value) = 0;
		virtual void setOutput(int patternIndex, int outputIndex, double value) = 0;
		virtual double getInput(int patternIndex, int inputIndex) const = 0;
		virtual double getOutput(int patternIndex, int outputIndex) const = 0;
		virtual void setInputVector(int patternIndex, const QList<double>& inputVector) = 0;
		virtual void setOutputVector(int patternIndex, const QList<double>& outputVector) = 0;
		virtual QList<double> getInputVector(int patternIndex) const = 0;
		virtual QList<double> getOutputVector(int patternIndex) const = 0;
		virtual int patternCount(int patternIndex) const = 0;
		virtual int inputCount(int patternIndex) const = 0;
		virtual int outputCount(int patternIndex) const = 0;
		virtual QString toString() const = 0;
};

}

#endif //ABSTRACTDATASET_H
