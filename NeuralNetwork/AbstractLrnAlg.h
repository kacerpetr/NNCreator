#ifndef ABSTRACTLRNALG_H
#define ABSTRACTLRNALG_H

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
class AbstractLrnAlg{
	public:
		virtual double iterate(unsigned int pattern) = 0;

	public slots:
		virtual void start() = 0;
		virtual void stop() = 0;

	signals:
		void graphUpdate();
};

}

#endif //ABSTRACTLRNALG_H
