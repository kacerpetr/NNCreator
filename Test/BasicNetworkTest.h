#ifndef BASICNETWORKTEST_H
#define BASICNETWORKTEST_H

#include <QObject>

namespace NeuralNetwork{

class BasicNetworkTest : public QObject{
	Q_OBJECT

	private slots:
		void stringConstructorTest();
		void insertLayerTest();
		void appendNeuronTest();
		void noLayerOutputTest();
		void oneLayerOutputTest();
		void twoLayersOutputTest();
		void threeLayersOutputTest();
};

}

#endif // BASICNETWORKTEST_H
