#ifndef MLNNETSTTEST_H
#define MLNNETSTTEST_H

#include <QObject>
#include "NeuralNetwork/MlnNetSt.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of LrnEngine class.
 */
class MlnNetStTest : public QObject{
	Q_OBJECT

	private slots:
		/** First test of mlnNetSt class. */
		void test1();
		/** Second test of mlnNetSt class. */
		void test2();
		/** Third test of mlnNetSt class. */
		void test3();
		/** Fourth test of mlnNetSt class. */
		void test4();
};

}

#endif //MLNNETSTTEST_H
