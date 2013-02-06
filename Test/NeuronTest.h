#ifndef NEURONTEST_H
#define NEURONTEST_H

#include <QObject>
#include "NeuralNetwork/Neuron.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of Neuron class.
 */
class NeuronTest : public QObject{
	Q_OBJECT

	private slots:
		/** First test of neuron class. */
		void test1();
		/** Second test of neuron class. */
		void test2();
		/** Third test of neuron class. */
		void test3();
		/** Fourth test of neuron class. */
		void test4();
		/** Fifth test of neuron class. */
		void test5();
};

}

#endif // NEURONTEST_H
