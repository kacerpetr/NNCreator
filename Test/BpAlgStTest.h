#ifndef BPALGSTTEST_H
#define BPALGSTTEST_H

#include <QObject>
#include "NeuralNetwork/BpAlgSt.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of BpAlgSt class.
 */
class BpAlgStTest : public QObject{
	Q_OBJECT

	private slots:
		void test1();
		void test2();
		void test3();
};

}

#endif // BPALGSTTEST_H
