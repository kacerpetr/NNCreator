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
		/** First test of bpAlgSt class. */
		void test1();
		/** Second test of bpAlgSt class. */
		void test2();
		/** Third test of bpAlgSt class. */
		void test3();
};

}

#endif // BPALGSTTEST_H
