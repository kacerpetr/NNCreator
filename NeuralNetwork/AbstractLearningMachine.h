#ifndef ABSTRACTLEARNINGMACHINE_H
#define ABSTRACTLEARNINGMACHINE_H

#include "AbstractNeuralNetwork.h"
#include "TrainingPattern.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Learning macine interface.
 */
class AbstractLearningMachine{
	public:
		virtual double iterate(unsigned int pattern) = 0;
		virtual ~AbstractLearningMachine() = 0;
};

}

#endif //ABSTRACTLEARNINGMACHINE_H
