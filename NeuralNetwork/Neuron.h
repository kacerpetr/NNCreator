#ifndef NEURON_H
#define NEURON_H

#include <string>
#include <list>
using namespace std;


class Neuron{
	public:
		Neuron();
		Neuron(const Neuron& obj);
		Neuron(const string& obj);

		int inputCount() const;
		double getInput(int input) const;
		double setInput(double value, int input);

		int weightCount() const;
		double getWeight(int weight) const;
		void setWeight(int value, double weight);
		double removeWeight(int weight);
		void insertWeight(double value, int weight);
		void appendWeight(double value);

		string toString();
		double operator()() const;

	private:
		double bias;
		list<double> input;
		list<double> weight;
};

#endif // NEURON_H
