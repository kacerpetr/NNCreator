#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include "ILearningMachine.h"

namespace NeuralNetwork{

class BackPropagation : public ILearningMachine{
	public:
		BackPropagation(const TrainingPattern* obj, INeuralNetwork* net);
		double iterate();

	private:
		TrainingPattern* trainingPattern;
		INeuralNetwork* neuralNetwork;
		std::vector< std::vector<double> > delta;
		std::vector< std::vector<double> > weight;
};

}

#endif // BACKPROPAGATION_H
