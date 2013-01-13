#ifndef BACKPROPAGATIONTEST_H
#define BACKPROPAGATIONTEST_H

#include <QObject>

namespace NeuralNetwork{

class BackPropagationTest : public QObject{
	Q_OBJECT

	private slots:
		void xorTest();
		//void test();
		//void test2();
};

}

#endif // BACKPROPAGATIONTEST_H
