#ifndef DATASET_H
#define DATASET_H

#include <QString>
#include <QList>

namespace NeuralNetwork{

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
		bool isConsistent() const;
		QString toString() const;
		~Dataset();

	private:
		void removeLastPattern();
		void reducePattern(int pattern);

	private:
		QList< QList<double*> > inputList;
		QList< QList<double*> > outputList;
		int patternCnt;
		int inputCnt;
		int outputCnt;
};

}

#endif // DATASET_H
