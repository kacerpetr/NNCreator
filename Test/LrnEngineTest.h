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

/**
 * Contains test code of MlnNetSt class.
 */
class LrnEngineTest : public QObject{
	Q_OBJECT

	public slots:
		/**
		 * Slot connected to started signal of learning algorithm class.
		 * @see AbstractLrnAlg::started()
		 */
		void lrnStarted();

		/**
		 * Slot connected to update signal of learning algorithm class.
		 * @see AbstractLrnAlg::update(int iteration, long time, double error)
		 */
		void lrnUpdate(int iteration, long time, double error);

		/**
		 * Slot connected to stoped signal of learning algorithm class.
		 * @see AbstractLrnAlg::stoped(int iteration, long time, double error)
		 */
		void lrnStoped(int iteration, long time, double error);

	private slots:
		/** Initializes test data. */
		void initTestCase();
		/** Test of learning engine. */
		void learningTest();

	private:
		/** Test dataset. */
		Dataset set;
		/** Test neural network. */
		MlnNetSt net;
		/** Tested learning algorithm. */
		BpAlgSt alg;
		/** Tested learning engine. */
		LrnEngine eng;
};

}

#endif //LRNENGINETEST_H
