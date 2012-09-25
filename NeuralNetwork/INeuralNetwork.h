#ifndef INEURALNETWORK_H
#define INEURALNETWORK_H

#include "Neuron.h"
#include <string.h>

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Interface for all future neural network implementations.
 */
class INeuralNetwork{
	public:
		virtual void setWeight(double value, int weight, int neuron, int layer) = 0;
		virtual void setNeuron(Neuron obj, int neuron, int layer) = 0;
		virtual void setInput(double value, int input) = 0;
		virtual void setBias(double value, int neuron, int layer) = 0;
		virtual void setBias(double value) = 0;

		virtual double getWeight(int weight, int neuron, int layer) const = 0;
		virtual Neuron getNeuron(int neuron, int layer) const = 0;
		virtual double getBias(int neuron, int layer) const = 0;
		virtual double getInput(int input) const = 0;
		virtual double getOutput(int output) const = 0;

		virtual void insertLayer(int position) = 0;
		virtual void removeLayer(int position) = 0;
		virtual void appendNeuron(Neuron obj) = 0;
		virtual void insertNeuron(int position, Neuron obj) = 0;
		virtual void removeNeuron(int position) = 0;

		virtual void randomizeWeights() = 0;
		virtual std::string toString() const = 0;
		virtual void checkRep() const = 0;
};

}
#endif // INEURALNETWORK_H
