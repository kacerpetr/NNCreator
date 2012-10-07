#ifndef NEURON_H
#define NEURON_H

#include <string>
#include <vector>

namespace NeuralNetwork{

class Neuron{
	public:
		Neuron();
		Neuron(const Neuron& neuron);
		Neuron(std::string str);

		void setWeight(const std::vector<double>& weight);
		std::vector<double> getWeight() const;

		int weightCount() const;
		double getWeight(int index) const;
		void setWeight(double value, int index);
		void removeWeight(int index);
		void insertWeight(double value, int index);
		void appendWeight(double value);

		void setBias(double bias);
		double getBias() const;

		inline double transferFcn(double x) const;

		double operator()(const std::vector<double>& input) const;
		double operator()(double input) const;
		void operator=(const Neuron& neuron);
		std::string toString() const;

	private:
		double bias;
		std::vector<double> weight;
};

}

#endif // NEURON_H
