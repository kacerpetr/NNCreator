#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <QObject>
#include <QElapsedTimer>
#include "AbstractLrnAlg.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Single threaded implementation of back propagation algorithm.
 */
class BpAlgSt : public AbstractLrnAlg{
	Q_OBJECT

	public:
		/**	Creates unconfigured learning configuration. */
		BpAlgSt();

		/** Copy constructor of learning algorithm. */
		BpAlgSt(BpAlgSt& obj);

		/** Copy constructor from pointer. */
		BpAlgSt(BpAlgSt* obj);

		/* Docummented in AbstractLrnAlg. */
		void setNetwork(AbstractMlnNet* net);
		void setDataset(Dataset* data);
		void setUpdateInterval(int interval);
		void setStopIteration(int stopIter);
		void setStopError(double stopErr);
		void setStopTime(long stopTime);
		void setAlpha(double alpha);
		AbstractMlnNet* network();
		Dataset* dataset();
		int updateInterval() const;
		int stopIteration() const;
		double stopError() const;
		long stopTime() const;
		bool isRunning() const;
		int currentIteration() const;
		double currentError() const;
		long currentTime() const;
		double alpha() const;

		/** Class destructor. */
		~BpAlgSt();

	public slots:
		/* Docummented in AbstractLrnAlg. */
		void start();
		void stop();

	private:
		/** Calculates network error for one training pattern. */
		double calcError(int pattern);
		/** Calculates deltas of neurons in output layer. */
		void calcOutputDelta(int pattern);
		/** Calculates deltas of neurons in inner layers. */
		void calcInnerDelta();
		/** Adjusts weights of network according to actual training pattern. */
		void adjustWeight();
		/** Generates data structure to store deltas of neurons. */
		void genDeltaArray();

	private:
		/** Update signal will be emited once after each interval of iterations. */
		int updateInterv;
		/** When this number of iterations is reached, learning will be stoped. */
		int stopIter;
		/** Learning will be stoped when actual error is less or equal to this value. */
		double stopErrorVal;
		/** Maximal time length of learning in miliseconds. */
		long stopTimeVal;
		/** Flag that tells that learning is in process. */
		bool running;
		/** Pointer to learned neural network. */
		AbstractMlnNet* net;
		/** Pointer to dataset of training patterns. */
		Dataset* data;
		/** Actual learning time in miliseconds. */
		long actTime;
		/** Actual iteration of learning. */
		int actIter;
		/** Actual error of neural network during learning. */
		double actError;
		/** Storage of calculated deltas. */
		QList< QList<double> > delta;
		/** Outputs of individual layers of neural network. */
		QList< QList<double> > output;
		/** Timer instance, used for learning time measurement. */
		QElapsedTimer timer;
		/** Learning speed coeficient alpha. */
		double alphaVal;
};

}

#endif // BACKPROPAGATION_H
