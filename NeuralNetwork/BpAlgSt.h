#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <QObject>
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
		void setStopTime(QTime stopTime);
		AbstractBpNet* getNetwork();
		AbstractDataset* getDataset();
		int getUpdateInterval() const;
		int getStopIteration() const;
		double getStopError() const;
		QTime getStopTime() const;
		bool isRunning() const;
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
		//used during learning
		QList< QList<double> > delta;
		QList< QList<double> > output;
		int actIter;
		double actError;
		QTime actTime;

	private:
		//main variables
		int updateInterval;
		int stopIter;
		double stopError;
		QTime stopTime;
		bool running;
		AbstractBpNet* net;
		AbstractDataset* data;
};

}

#endif // BACKPROPAGATION_H
