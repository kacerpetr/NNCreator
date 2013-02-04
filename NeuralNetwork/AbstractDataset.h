#ifndef ABSTRACTDATASET_H
#define ABSTRACTDATASET_H

#include <QList>

namespace NeuralNetwork{

class AbstractDataset{
	public:
		virtual void appendPattern() = 0;
		virtual void appendPattern(int count) = 0;
		virtual void removePattern(int patternIndex) = 0;
		virtual void clearPattern(int patternIndex) = 0;
		virtual void appendInputs(int patternIndex, int count, double value) = 0;
		virtual void appendOutputs(int patternIndex, int count, double value) = 0;
		virtual void setInputVector(int patternIndex, const QList<double>& inputVector) = 0;
		virtual void setOutputVector(int patternIndex, const QList<double>& outputVector) = 0;
		virtual QList<double> getInputVector(int patternIndex) const = 0;
		virtual QList<double> getOutputVector(int patternIndex) const = 0;
		virtual int patternCount() const = 0;
		virtual int inputCount(int patternIndex) const = 0;
		virtual int outputCount(int patternIndex) const = 0;
		virtual QList<double>& operator[](int patternIndex) = 0;
		virtual QList<double>& operator()(int patternIndex) = 0;
		virtual QString toString() const = 0;
};

}

#endif //ABSTRACTDATASET_H
