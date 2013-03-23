#ifndef NEURON_H
#define NEURON_H

#include <QString>
#include <QList>
#include "Util/globaldef.h"
#include "Dataset.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Class that represents artificial neuron.
 */
class Neuron{
	public:
		Neuron();
        Neuron(const Neuron& neuron);
		void setTrFcn(TransferFcn trFcn);
		TransferFcn trFcn() const;
        double bias() const;
        void setBias(double bias);
        void addBias(double value);
        double slope() const;
        void setSlope(double slope);
        QList<double> weights() const;
		void setWeights(const QList<double>& weights);
        void removeWeight(int weightIndex);
		void removeLastWeight();
		void leaveWeight(int count);
		void insertWeight(int weightIndex, double value);	
		void appendWeight(double value);
		void appendWeights(int count, double value);
        int weightCount() const;
		double output(const QList<double>& input) const;
		double output(double input) const;
        QString toString() const;
		double& operator[](int weightIndex);
        Neuron& operator=(const Neuron& neuron);
        double trFcn(double x) const;
        double trFcnD(double x) const;
		~Neuron();

	private:
		/** Value of neuron bias. */
		double biasVal;
		/** Value of slope of transfer function. */
		double slopeVal;
		/** Transfer function type. */
		TransferFcn trFcnType;
		/** List of neuron weights. */
		QList<double> weight;
};

}

#endif // NEURON_H
