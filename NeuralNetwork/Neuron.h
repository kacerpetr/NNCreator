#ifndef NEURON_H
#define NEURON_H

#include <QString>
#include <QList>

/**
 *
 */
namespace NeuralNetwork{

enum TransferFcn{
	BinarySigmoid,
	UnarySigmoid
};

class Neuron{
	public:
		Neuron();
		Neuron(const Neuron& neuron);
		TransferFcn getTrFcn() const;
		void setTrFcn(TransferFcn trFcn);
		double getBias() const;
		void setBias(double bias);
		void addBias(double value);
		double getSlope() const;
		void setSlope(double slope);
		QList<double> getWeights() const;
		void setWeights(const QList<double>& weights);
		double getWeight(int weightIndex) const;
		void setWeight(int weightIndex, double value);
		void removeWeight(int weightIndex);
		void removeLastWeight();
		void leaveWeight(int count);
		void insertWeight(int weightIndex, double value);
		void appendWeight(double value);
		void appendWeights(int count, double value);
		int weightCount() const;
		double getOutput(const QList<double>& input) const;
		double getOutput(double input) const;
		QString toString() const;
		double& operator[](int weightIndex);
		Neuron& operator=(const Neuron& neuron);
		double trFcn(double x) const;
		double trFcnD(double x) const;
		~Neuron();



	private:
		double bias;
		double slope;
		TransferFcn trFcnType;
		QList<double> weight;
};

}

#endif // NEURON_H
