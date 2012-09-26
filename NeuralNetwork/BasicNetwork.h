#ifndef BASICNETWORK_H
#define BASICNETWORK_H

#include "INeuralNetwork.h"

namespace NeuralNetwork{

class BasicNetwork : public virtual INeuralNetwork{
	public:
		BasicNetwork();
		BasicNetwork(const BasicNetwork& obj);
		BasicNetwork(const std::string& obj);
		~BasicNetwork();

		void setWeight(double value, int weight, int neuron, int layer);
		void setNeuron(Neuron obj, int neuron, int layer);
		void setInput(double value, int input);
		void setBias(double value, int neuron, int layer);
		void setBias(double value);

		double getWeight(int weight, int neuron, int layer) const;
		Neuron getNeuron(int neuron, int layer) const;
		double getBias(int neuron, int layer) const;
		double getInput(int input) const;
		double getOutput(int output) const;

		void insertLayer(int position);
		void removeLayer(int position);
		void appendNeuron(Neuron obj);
		void insertNeuron(int position, Neuron obj);
		void removeNeuron(int position);

		virtual int weightCount(int neuron, int layer) const;
		virtual int neuronCount(int layer) const;
		virtual int layerCount() const;
		virtual int inputCount() const;
		virtual int outputCount() const;

		void randomizeWeights();
		std::string toString() const;
};

}

#endif //BASICNETWORK_H
