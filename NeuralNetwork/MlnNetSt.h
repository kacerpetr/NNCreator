#ifndef MLNNETST_H
#define MLNNETST_H

#include "AbstractMlnNet.h"
#include "Neuron.h"

namespace NeuralNetwork{

class MlnNetSt : public AbstractMlnNet{
	public:
		MlnNetSt();
		MlnNetSt(const MlnNetSt& obj);
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
		int inputCount() const;
		int layerCount() const;
		int neuronCount() const;
		int neuronCount(int layer) const;
		int weightCount() const;
		void setBias(double value);
		void randomizeWeight(int seed, double min, double max);
		void randomizeBias(int seed, double min, double max);
		void setTransferFunction(TransferFcn trFcn);
		QList<double> output(const QList<double>& input) const;
		QList< QList<double> > layerOutput(const QList<double>& input) const;
		QList<Neuron>& operator[](int layer);
		QString toString() const;
		~MlnNetSt();

	private:
		int inCnt;
		QList< QList<Neuron> > net;
};

}

#endif //MLNNETST_H