#ifndef BPALGSTTEST_H
#define BPALGSTTEST_H

#include <QObject>
#include "NeuralNetwork/BpAlgSt.h"
using namespace NeuralNetwork;

namespace Test{

class BpAlgStTest : public QObject{
	Q_OBJECT

	public:
		explicit BpAlgStTest(QObject *parent = 0);

	private slots:
		void test1();
		void test2();
};

}

#endif //BPALGSTTEST_H