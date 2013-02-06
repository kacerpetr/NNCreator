#ifndef NEURON_H
#define NEURON_H

#include <QString>
#include <QList>
#include "Dataset.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/** Neuron transfer function types. */
enum TransferFcn{
	BinarySigmoid, /**< Binary sigmoid function with output between -1 and 1. */
	UnarySigmoid   /**< Unary sigmoid function with output between 0 and 1.   */
};

/**
 * Class that represents artificial neuron.
 */
class Neuron{
	public:
		/** Creates neuron without weights and with bias of zero value. */
		Neuron();

		/** Creates copy of given neuron. */
		Neuron(const Neuron& neuron);

		/**
		 * Transfer function setter.
		 * @see TransferFcn
		 * @param trFcn new transfer function of neuron
		 */
		void setTrFcn(TransferFcn trFcn);

		/**
		 * Transfer function getter.
		 * @see TransferFcn
		 * @return type of neuron transfer function
		 */
		TransferFcn trFcn() const;

		/** Returns neuron bias value. */
		double bias() const;

		/** Sets neuron bias value. */
		void setBias(double bias);

		/** Adds given value to exiting neuron bias. */
		void addBias(double value);

		/** Returns slope of neuron transfer function. */
		double slope() const;

		/** Sets slope of neuron transfer function. */
		void setSlope(double slope);

		/** Returns list of neuron weights. */
		QList<double> weights() const;

		/** Replaces actual weight list by given weight list. */
		void setWeights(const QList<double>& weights);

		/**
		 * Removes weight of neuron.
		 * @param weightIndex index of weight between 0 and weightCount.
		 */
		void removeWeight(int weightIndex);

		/** Removes weight of neuron with highest index. */
		void removeLastWeight();

		/** Removes or adds weights so neuron will have count weights. */
		void leaveWeight(int count);

		/** Inserts weight of given value at position given by index.*/
		void insertWeight(int weightIndex, double value);

		/** Appends weight of given value. */
		void appendWeight(double value);

		/** Appends count weights of given value. */
		void appendWeights(int count, double value);

		/** Returns actual count of neuron weights. */
		int weightCount() const;

		/**
		 * Returns output of neuron.
		 * @param input must be same length as weight count
		 */
		double output(const QList<double>& input) const;

		/** Returns output of neuron, can be used in case of one input. */
		double output(double input) const;

		/** Returns string representation of neuron. */
		QString toString() const;

		/** Returns reference to weight value at given index. */
		double& operator[](int weightIndex);

		/**
		 * Assigns given neuron to this neuron.
		 * @return reference to this neuron
		 */
		Neuron& operator=(const Neuron& neuron);

		/** Calculates value of transfer function. */
		double trFcn(double x) const;

		/** Calculates value of derived transfer function. */
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
