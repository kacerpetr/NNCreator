#ifndef LRNENGINETEST_H
#define LRNENGINETEST_H

#include <QObject>
#include "NeuralNetwork/LrnEngine.h"
#include "NeuralNetwork/Dataset.h"
#include "NeuralNetwork/MlnNetSt.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

class LrnEngineTest : public QObject{
	Q_OBJECT

	public:
		explicit LrnEngineTest(QObject *parent = 0);

	public slots:
		void lrnStarted();
		void lrnUpdate(int iteration, long time, double error);
		void lrnStoped(int iteration, long time, double error);

	private slots:
		void initTestCase();
		void learningTest();

	private:
		Dataset set;
		MlnNetSt net;
		BpAlgSt alg;
		LrnEngine eng;
};

}

#endif //LRNENGINETEST_H
