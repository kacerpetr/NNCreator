#ifndef BPNETST_H
#define BPNETST_H

#include "AbstractBpNet.h"
#include "Neuron.h"

namespace NeuralNetwork{

class BpNetSt : public AbstractBpNet{
	public:
		BpNetSt();
		BpNetSt(const BpNetSt& obj);
		void setInputCount(int count);
		void appendLayer();
		void insertLayer(int position);
		void removeLayer(int layer);
		void duplicateLayer(int layer);
		void appendNeuron(int layer);
		void appendNeuron(int layer, int count);
		void appendNeuron(int layer, const Neuron& neuron);
		void removeLastNeuron(int layer);
		void insertNeuron(int layer, int position);
		void removeNeuron(int layer, int position);
		int getInputCount() const;
		int getLayerCount() const;
		int getNeuronCount() const;
		int getNeuronCount(int layer) const;
		int getWeightCount() const;
		void setBias(double value);
		void randomizeWeight(int seed, double min, double max);
		void randomizeBias(int seed, double min, double max);
		void setTransferFunction(TransferFcn trFcn);
		QList<double> getOutput(const QList<double>& input) const;
		QList< QList<double> > getLayerOutput(const QList<double>& input) const;
		QList<Neuron>& operator[](int layer);
		QString toString() const;
		~BpNetSt();

	private:
		int inputCount;
		QList< QList<Neuron> > net;
};

}

#endif //BPNETST_H
