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
		void test1();
		void test2();
		void test3();
		void test4();
		void test5();
};

}

#endif // NEURONTEST_H
