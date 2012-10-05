#ifndef INEURALNETWORK_H
#define INEURALNETWORK_H

#include <string.h>
#include "Neuron.h"
#include <vector>

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * unsigned interface for all future neural network implementations.
 */
class INeuralNetwork{
	public:
		virtual void setWeights(const std::vector<double>& obj, unsigned int neuron, unsigned int layer) = 0;
		virtual void setNeurons(const std::vector<Neuron>& obj, unsigned int layer) = 0;

		virtual void setWeight(double value, unsigned int weight, unsigned int neuron, unsigned int layer) = 0;
		virtual void setNeuron(Neuron obj, unsigned int neuron, unsigned int layer) = 0;
		virtual void setBias(double value, unsigned int neuron, unsigned int layer) = 0;
		virtual void setBias(double value) = 0;

		virtual std::vector<double> getWeights(unsigned int neuron, unsigned int layer) const = 0;
		virtual std::vector<Neuron> getNeurons(unsigned int layer) const = 0;

		virtual double getWeight(unsigned int weight, unsigned int neuron, unsigned int layer) const = 0;
		virtual Neuron getNeuron(unsigned int neuron, unsigned int layer) const = 0;
		virtual double getBias(unsigned int neuron, unsigned int layer) const = 0;

		virtual void appendLayer() = 0;
		virtual void insertLayer(unsigned int position) = 0;
		virtual void removeLayer(unsigned int position) = 0;
		virtual void appendNeuron(unsigned int layer) = 0;
		virtual void appendNeuron(Neuron obj, unsigned int layer) = 0;
		virtual void insertNeuron(unsigned int layer, unsigned int position) = 0;
		virtual void removeNeuron(unsigned int layer, unsigned int position) = 0;

		virtual unsigned int weightCount(unsigned int neuron, unsigned int layer) const = 0;
		virtual unsigned int neuronCount(unsigned int layer) const = 0;
		virtual unsigned int layerCount() const = 0;

		virtual std::vector<double> operator()(const std::vector<double>& input) = 0;
		virtual void randomizeWeights() = 0;
		virtual std::string toString() const = 0;
};

}
#endif // INEURALNETWORK_H
