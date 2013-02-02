#ifndef ABSTRACTBPNET_H
#define ABSTRACTBPNET_H

#include <QString>
#include <QList>
#include "Neuron.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Interface for all future neural network implementations.
 */
class AbstractBpNet{
	public:
		virtual void setInputCount(int count) = 0;
		virtual void appendLayer() = 0;
		virtual void insertLayer(int position) = 0;
		virtual void removeLayer(int layer) = 0;
		virtual void duplicateLayer(int layer) = 0;
		virtual void appendNeuron(int layer) = 0;
		virtual void appendNeuron(int layer, int count) = 0;
		virtual void appendNeuron(int layer, const Neuron& neuron) = 0;
		virtual void removeLastNeuron(int layer) = 0;
		virtual void insertNeuron(int layer, int position) = 0;
		virtual void removeNeuron(int layer, int position) = 0;
		virtual int getInputCount() const = 0;
		virtual int getLayerCount() const = 0;
		virtual int getNeuronCount() const = 0;
		virtual int getWeightCount() const = 0;
		virtual int getNeuronCount(int layer) const = 0;
		virtual void setBias(double value) = 0;
		virtual void randomizeWeight(int seed, double min, double max) = 0;
		virtual void randomizeBias(int seed, double min, double max) = 0;
		virtual void setTransferFunction(TransferFcn trFcn) = 0;
		virtual QList<double> getOutput(const QList<double>& input) const = 0;
		virtual QList< QList<double> > getLayerOutput(const QList<double>& input) const = 0;
		virtual QList<Neuron>& operator[](int layer) = 0;
		virtual QString toString() const = 0;
};

}
#endif //ABSTRACTBPNETWORK_H
