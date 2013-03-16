#ifndef ABSTRACTLRNALG_H
#define ABSTRACTLRNALG_H

#include <QTime>
#include <QObject>
#include "AbstractMlnNet.h"
#include "Dataset.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Interface for general learning algorithm.
 */
class AbstractLrnAlg : public QObject{
	Q_OBJECT

	public:
		/** Sets pointer to neural network. */
		virtual void setNetwork(AbstractMlnNet* net) = 0;

		/** Sets pointer to dataset. */
		virtual void setDataset(Dataset* data) = 0;

		/**
		 * Sets update interval (count of iterations).
		 * At the end of each interval will be emmited,
		 * update signal during learning.
		 */
		virtual void setUpdateInterval(int interval) = 0;

		/**
		 * Sets maximal iteration count.
		 * When actual iteration of learning reach this value,
		 * learning will be stoped.
		 */
		virtual void setStopIteration(int stopIter) = 0;

		/**
		 * Sets maximal error value.
		 * Learning will be stoped when when actual error will
		 * be less or equal than maximal error value.
		 */
		virtual void setStopError(double stopErr) = 0;

		/**
		 * Sets maximal error value.
		 * Learning will be stoped when when actual error will
		 * be less or equal than maximal error value.
		 */
		virtual void setStopTime(long stopTime) = 0;

		/** Sets learning speed coeficient alpha */
		virtual void setAlpha(double alpha) = 0;

		/** Returns pointer to neural network */
		virtual AbstractMlnNet* network() = 0;

		/** Returns pointer to dataset */
		virtual Dataset* dataset() = 0;

		/**
		 * Sets update interval (count of iterations).
		 * At the end of each interval will be emmited,
		 * update signal during learning.
		 */
		virtual int updateInterval() const = 0;

		/**
		 * Returns maximal iteration count.
		 * When actual iteration of learning reach this value,
		 * learning will be stoped.
		 */
		virtual int stopIteration() const = 0;

		/**
		 * Returns maximal error value.
		 * Learning will be stoped when when actual error will
		 * be less or equal than maximal error value.
		 */
		virtual double stopError() const = 0;

		/**
		 * Returns maximal error value.
		 * Learning will be stoped when when actual error will
		 * be less or equal than maximal error value.
		 */
		virtual long stopTime() const = 0;

		/** Returns true if learning is in process. */
		virtual bool isRunning() const = 0;

		/** Returns current iteration of learning. */
		virtual int currentIteration() const = 0;

		/** Returns current error of neural network. */
		virtual double currentError() const = 0;

		/** Returns current duration of learning. */
		virtual long currentTime() const = 0;

		/** Returns learning speed coeficient alpha */
		virtual double alpha() const = 0;

	signals:
		/** Emmited when learning is started. */
        void started();
		/** Emmited when learning is finished or stoped. */
        void stoped();
		/** Emmited when actual iteration modulo update intertval equals zero. */
        void update(int iteration, long time, double error);

	public slots:
		/** Starts learning proccess. */
		virtual void start() = 0;
		/** Stops learning after current iteration is finished. */
		virtual void stop() = 0;
};

}

#endif //ABSTRACTLRNALG_H
