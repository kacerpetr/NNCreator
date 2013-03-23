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
		void test1();
		void test2();
		void test3();
		void test4();
};

}

#endif //MLNNETSTTEST_H
