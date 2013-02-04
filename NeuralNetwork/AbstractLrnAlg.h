#ifndef ABSTRACTLRNALG_H
#define ABSTRACTLRNALG_H

#include <QTime>
#include <QObject>
#include "AbstractBpNet.h"
#include "AbstractDataset.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Learning machine interface.
 */
class AbstractLrnAlg : public QObject{
	Q_OBJECT

	public:
		virtual void setNetwork(AbstractBpNet* net) = 0;
		virtual void setDataset(AbstractDataset* data) = 0;
		virtual void setUpdateInterval(int interval) = 0;
		virtual void setStopIteration(int stopIter) = 0;
		virtual void setStopError(double stopErr) = 0;
		virtual void setStopTime(long stopTime) = 0;
		virtual void setAlpha(double alpha) = 0;
		virtual AbstractBpNet* getNetwork() = 0;
		virtual AbstractDataset* getDataset() = 0;
		virtual int getUpdateInterval() const = 0;
		virtual int getStopIteration() const = 0;
		virtual double getStopError() const = 0;
		virtual long getStopTime() const = 0;
		virtual bool isRunning() const = 0;
		virtual int getCurrentIteration() const = 0;
		virtual double getCurrentError() const = 0;
		virtual long getCurrentTime() const = 0;
		virtual double getAlpha() const = 0;

	public slots:
		virtual void start() = 0;
		virtual void stop() = 0;
};

}

#endif //ABSTRACTLRNALG_H
