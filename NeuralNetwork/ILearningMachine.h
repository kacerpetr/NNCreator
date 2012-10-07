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
		virtual double iterate(unsigned int pattern) = 0;
};

}

#endif // ILEARNINGMACHINE_H
