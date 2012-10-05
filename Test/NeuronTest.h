#ifndef NEURONTEST_H
#define NEURONTEST_H

#include <QObject>

namespace NeuralNetwork{

class NeuronTest : public QObject{
	Q_OBJECT

	private slots:
		void stringConstructorTest();
		void outputCalculationTest();
};

}

#endif // NEURONTEST_H
