#ifndef BASICNETWORK_H
#define BASICNETWORK_H

#include "INeuralNetwork.h"

namespace NeuralNetwork{

class BasicNetwork : public virtual INeuralNetwork{
	public:
		BasicNetwork(void);
		BasicNetwork(const BasicNetwork& obj);
		BasicNetwork(const std::string& obj);
		~BasicNetwork(void);

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

		void randomizeWeights(void);
		std::string toString(void) const;
};

}

#endif //BASICNETWORK_H
