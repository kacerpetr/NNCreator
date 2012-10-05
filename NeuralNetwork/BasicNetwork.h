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

		void setWeights(const std::vector<double>& obj, unsigned int neuron, unsigned int layer);
		void setNeurons(const std::vector<Neuron>& obj, unsigned int layer);

		void setWeight(double value, unsigned int weight, unsigned int neuron, unsigned int layer);
		void setNeuron(Neuron obj, unsigned int neuron, unsigned int layer);
		void setBias(double value, unsigned int neuron, unsigned int layer);
		void setBias(double value);

		std::vector<double> getWeights(unsigned int neuron, unsigned int layer) const;
		std::vector<Neuron> getNeurons(unsigned int layer) const;

		double getWeight(unsigned int weight, unsigned int neuron, unsigned int layer) const;
		Neuron getNeuron(unsigned int neuron, unsigned int layer) const;
		double getBias(unsigned int neuron, unsigned int layer) const;

		void appendLayer();
		void insertLayer(unsigned int position);
		void removeLayer(unsigned int position);
		void appendNeuron(unsigned int layer);
		void appendNeuron(Neuron obj, unsigned int layer);
		void insertNeuron(unsigned int layer, unsigned int position);
		void removeNeuron(unsigned int layer, unsigned int position);

		virtual unsigned int weightCount(unsigned int neuron, unsigned int layer) const;
		virtual unsigned int neuronCount(unsigned int layer) const;
		virtual unsigned int layerCount() const;

		std::vector<double> operator()(const std::vector<double>& input);
		void operator=(const BasicNetwork& obj);
		void randomizeWeights();
		std::string toString() const;

	private:
		std::vector< std::vector<Neuron> > net;
};

}

#endif //BASICNETWORK_H
