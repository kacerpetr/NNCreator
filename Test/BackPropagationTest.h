#ifndef BACKPROPAGATIONTEST_H
#define BACKPROPAGATIONTEST_H

#include <QObject>

namespace NeuralNetwork{

class BackPropagationTest : public QObject{
	Q_OBJECT

	private slots:
		void test();
};

}

#endif // BACKPROPAGATIONTEST_H
