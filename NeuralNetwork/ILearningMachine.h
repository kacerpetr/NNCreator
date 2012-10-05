#ifndef ILEARNINGMACHINE_H
#define ILEARNINGMACHINE_H

#include "INeuralNetwork.h"
#include "TrainingPattern.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Learning macine interface.
 */
class ILearningMachine{
	public:
		virtual void setTrainingPattern(const TrainingPattern* obj) = 0;
		virtual void setNeuralNetwork(INeuralNetwork* net) = 0;
		virtual double iterate() = 0;
};

}

#endif // ILEARNINGMACHINE_H
