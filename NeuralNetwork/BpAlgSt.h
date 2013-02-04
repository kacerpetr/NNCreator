#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <QObject>
#include <QElapsedTimer>
#include "AbstractLrnAlg.h"

namespace NeuralNetwork{

class BpAlgSt : public AbstractLrnAlg{
	Q_OBJECT

	public:
		BpAlgSt();
		BpAlgSt(BpAlgSt& obj);
		void setNetwork(AbstractBpNet* net);
		void setDataset(AbstractDataset* data);
		void setUpdateInterval(int interval);
		void setStopIteration(int stopIter);
		void setStopError(double stopErr);
		void setStopTime(long stopTime);
		void setAlpha(double alpha);
		AbstractBpNet* getNetwork();
		AbstractDataset* getDataset();
		int getUpdateInterval() const;
		int getStopIteration() const;
		double getStopError() const;
		long getStopTime() const;
		bool isRunning() const;
		int getCurrentIteration() const;
		double getCurrentError() const;
		long getCurrentTime() const;
		double getAlpha() const;
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

	signals:
		void started();
		void stoped(int iteration, long time, double error);
		void update(int iteration, long time, double error);

	private:
		//used during learning
		QList< QList<double> > delta;
		QList< QList<double> > output;
		int actIter;
		double actError;
		QElapsedTimer timer;
		long actTime;
		//main variables
		int updateInterval;
		int stopIter;
		double stopError;
		long stopTime;
		bool running;
		AbstractBpNet* net;
		AbstractDataset* data;
		double alpha;
};

}

#endif // BACKPROPAGATION_H
