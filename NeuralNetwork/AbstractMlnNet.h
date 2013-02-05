#ifndef ABSTRACTMLNNET_H
#define ABSTRACTMLNNET_H

#include <QString>
#include <QList>
#include "Neuron.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Interface of multilayer neural network.
 */
class AbstractMlnNet{
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
		virtual int inputCount() const = 0;
		virtual int layerCount() const = 0;
		virtual int neuronCount() const = 0;
		virtual int neuronCount(int layer) const = 0;
		virtual int weightCount() const = 0;
		virtual void setBias(double value) = 0;
		virtual void randomizeWeight(int seed, double min, double max) = 0;
		virtual void randomizeBias(int seed, double min, double max) = 0;
		virtual void setTransferFunction(TransferFcn trFcn) = 0;
		virtual QList<double> output(const QList<double>& input) const = 0;
		virtual QList< QList<double> > layerOutput(const QList<double>& input) const = 0;
		virtual QList<Neuron>& operator[](int layer) = 0;
		virtual QString toString() const = 0;
};

}
#endif //ABSTRACTMLNNETWORK_H
