#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "AbstractLearningMachine.h"

namespace NeuralNetwork{

class BackPropagation : public AbstractLearningMachine{
	public:
		BackPropagation();
		BackPropagation(AbstractNeuralNetwork* neuralNetwork, TrainingPattern* trainingPattern);
		virtual ~BackPropagation();
		double iterate(unsigned int pattern);

	private:
		inline double transferFcnD(double x) const;

	private:
		double alpha;
		TrainingPattern* trainingPattern;
		AbstractNeuralNetwork* neuralNetwork;
		std::vector< std::vector<double> > delta;
		std::vector< std::vector<double> > output;
};

}

#endif // BACKPROPAGATION_H
