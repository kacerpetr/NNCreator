#ifndef BASICNETWORK_H
#define BASICNETWORK_H

#include "AbstractNeuralNetwork.h"

namespace NeuralNetwork{

class BasicNetwork : public virtual AbstractNeuralNetwork{
	public:
		BasicNetwork();
		BasicNetwork(const BasicNetwork& obj);
		BasicNetwork(const std::string& obj);
		virtual ~BasicNetwork();

		void setWeights(const std::vector<double>& obj, unsigned int layer, unsigned int neuron);
		void setNeurons(const std::vector<Neuron>& obj, unsigned int layer);

		void setWeight(double value, unsigned int layer, unsigned int neuron, unsigned int weight);
		void setNeuron(Neuron obj, unsigned int layer, unsigned int neuron);
		void setBias(double value, unsigned int layer, unsigned int neuron);
		void setBias(double value);

		void addWeight(double value, unsigned int layer, unsigned int neuron, unsigned int weight);
		void addBias(double value, unsigned int layer, unsigned int neuron);

		std::vector<double> getWeights(unsigned int layer, unsigned int neuron) const;
		std::vector<Neuron> getNeurons(unsigned int layer) const;

		double getWeight(unsigned int layer, unsigned int neuron, unsigned int weight) const;
		Neuron getNeuron(unsigned int layer, unsigned int neuron) const;
		double getBias(unsigned int layer, unsigned int neuron) const;

		void appendLayer();
		void insertLayer(unsigned int position);
		void removeLayer(unsigned int position);
		void appendNeuron(unsigned int layer);
		void appendNeuron(Neuron obj, unsigned int layer);
		void insertNeuron(unsigned int layer, unsigned int position);
		void removeNeuron(unsigned int layer, unsigned int position);

		virtual unsigned int weightCount(unsigned int layer, unsigned int neuron) const;
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
