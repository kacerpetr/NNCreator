#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "ILearningMachine.h"

namespace NeuralNetwork{

class BackPropagation : public ILearningMachine{
	public:
		BackPropagation(INeuralNetwork* neuralNetwork, TrainingPattern* trainingPattern);
		double iterate(unsigned int pattern);

	private:
		inline double transferFcnD(double x) const;

	private:
		double alpha;
		TrainingPattern* trainingPattern;
		INeuralNetwork* neuralNetwork;
		std::vector< std::vector<double> > delta;
		std::vector< std::vector<double> > output;
};

}

#endif // BACKPROPAGATION_H
