#ifndef TRAININGPATTERN_H
#define TRAININGPATTERN_H

#include <QString>
#include <vector>
#include "AbstractTrainingPattern.h"

namespace NeuralNetwork{

class TrainingPattern : public AbstractTrainingPattern{
	public:
		TrainingPattern();
		TrainingPattern(const TrainingPattern& obj);
		TrainingPattern(const QString& str);
		virtual ~TrainingPattern();

		void appendPattern();
		void removePattern(unsigned int pattern);

		void appendInput(unsigned int pattern, double input);
		void appendOutput(unsigned int pattern, double output);
		void removeInput(unsigned int index);
		void removeOutput(unsigned int index);

		unsigned int patternCount();
		unsigned int itemCount(unsigned int pattern);

		double getInput(unsigned int pattern, unsigned int index);
		double getOutput(unsigned int pattern, unsigned int index);

		std::vector<double> getInput(unsigned int pattern);
		std::vector<double> getOutput(unsigned int pattern);

		QString toString();

	private:
		std::vector< std::vector<double> > input;
		std::vector< std::vector<double> > output;
};

}

#endif // TRAININGPATTERN_H
