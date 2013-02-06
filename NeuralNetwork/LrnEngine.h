#ifndef LRNENGINE_H
#define LRNENGINE_H

#include <QObject>
#include <QThread>
#include "BpAlgSt.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Engine to run learning of neural network in secondary thread.
 */
class LrnEngine : public QObject{
	Q_OBJECT

	public:
		/** Creates unconfigured learning engine. */
		LrnEngine();

		/** Sets pointer to learning algorithm class. */
		void setAlgorithm(AbstractLrnAlg* algorithm);

		/** Returns pointer to learning algorithm class. */
		AbstractLrnAlg* getAlgorithm();

		/** Waits until learning is finished. */
		void waitTofinish();

		/** Class destructor. */
		~LrnEngine();

	public slots:
		/** Starts learning in secondary thread. */
		void startThread();
		/** Stops learning in secondary thread. */
		void stopThread();

	private:
		/** Pointer to QThread instance. */
		QThread* thread;
		/** Pointer to learning algorithm. */
		AbstractLrnAlg* alg;
};

}

#endif //LRNENGINE_H
