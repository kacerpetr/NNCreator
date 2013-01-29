#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "AbstractLearningMachine.h"

namespace NeuralNetwork{

class BackPropagation : public AbstractLearningMachine{
	public:
		BackPropagation();
		BackPropagation(AbstractNeuralNetwork* neuralNetwork, Dataset* trainingPattern);
		virtual ~BackPropagation();
		double iterate(unsigned int pattern);
		double alpha;

	private:
		inline double transferFcnD(double x) const;

	private:
		Dataset* trainingPattern;
		AbstractNeuralNetwork* neuralNetwork;
		std::vector< std::vector<double> > delta;
		std::vector< std::vector<double> > output;
};

}

#endif // BACKPROPAGATION_H
