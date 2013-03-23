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
		LrnEngine();
		void setAlgorithm(AbstractLrnAlg* algorithm);
		AbstractLrnAlg* getAlgorithm();
		void waitTofinish();
		~LrnEngine();

	public slots:
		void startThread();
		void stopThread();

	private slots:
		void delThread();

	private:
		/** Pointer to QThread instance. */
		QThread* thread;
		/** Pointer to learning algorithm. */
		AbstractLrnAlg* alg;
};

}

#endif //LRNENGINE_H
