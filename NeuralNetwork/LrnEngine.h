#ifndef LRNENGINE_H
#define LRNENGINE_H

#include <QObject>
#include <QThread>
#include "BpAlgSt.h"

namespace NeuralNetwork{

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

	private:
		QThread* thread;
		AbstractLrnAlg* alg;
};

}

#endif //LRNENGINE_H
