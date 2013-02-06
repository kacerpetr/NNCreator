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
		BpAlgSt();
		BpAlgSt(BpAlgSt& obj);
		void setNetwork(AbstractMlnNet* net);
		void setDataset(AbstractDataset* data);
		void setUpdateInterval(int interval);
		void setStopIteration(int stopIter);
		void setStopError(double stopErr);
		void setStopTime(long stopTime);
		void setAlpha(double alpha);
		AbstractMlnNet* network();
		AbstractDataset* dataset();
		int updateInterval() const;
		int stopIteration() const;
		double stopError() const;
		long stopTime() const;
		bool isRunning() const;
		int currentIteration() const;
		double currentError() const;
		long currentTime() const;
		double alpha() const;
		~BpAlgSt();

	public slots:
		void start();
		void stop();

	private:
		double calcError(int pattern);
		void calcOutputDelta(int pattern);
		void calcInnerDelta();
		void adjustWeight();
		void genDeltaArray();

	private:
		int updateInterv;
		int stopIter;
		double stopErrorVal;
		long stopTimeVal;
		bool running;
		AbstractMlnNet* net;
		AbstractDataset* data;
		long actTime;
		int actIter;
		double actError;
		QList< QList<double> > delta;
		QList< QList<double> > output;
		QElapsedTimer timer;
		double alphaVal;
};

}

#endif // BACKPROPAGATION_H
