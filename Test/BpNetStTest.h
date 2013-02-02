#ifndef BPNETSTTEST_H
#define BPNETSTTEST_H

#include <QObject>
#include "NeuralNetwork/BpNetSt.h"
using namespace NeuralNetwork;

namespace Test{

class BpNetStTest : public QObject{
	Q_OBJECT

	public:
		explicit BpNetStTest(QObject *parent = 0);

	private slots:
		void test1();
		void test2();
		void test3();
		void test4();
};

}

#endif //BPNETSTTEST_H
