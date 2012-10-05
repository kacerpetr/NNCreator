#ifndef TRAININGPATTERN_H
#define TRAININGPATTERN_H

#include <QString>
#include <QList>

namespace NeuralNetwork{

class TrainingPattern{
	public:
		TrainingPattern();
		TrainingPattern(const TrainingPattern& obj);
		TrainingPattern(const QString& str);

		void appendPattern();
		void appendValue(unsigned int pattern, double input, double output);
		void removePattern(unsigned int pattern);

		unsigned int patternCount();
		unsigned int itemCount(unsigned int pattern);

		double getInput(unsigned int pattern, unsigned int index);
		double getOutput(unsigned int pattern, unsigned int index);

		QString toString();

	private:
		QList< QList<double> > input;
		QList< QList<double> > output;
};

}

#endif // TRAININGPATTERN_H
