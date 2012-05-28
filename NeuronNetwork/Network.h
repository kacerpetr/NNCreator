#ifndef NETWORK_H
#define NETWORK_H

#include <QTextStream>
#include "Layer.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

class Network{
	public:
		Network(void);
		Network(const Network& network);

		inline void appendLayer(const Layer& layer);
		inline Layer getLayer(unsigned int index) const;
		inline void setLayer(unsigned int index, const Layer& layer);
		inline void insertLayer(unsigned int index, const Layer& layer);
		inline Layer removeLayer(unsigned int index);

		inline unsigned int getCount();

		QString toString(void);
		Layer fromString(QString str);

		QList<double> operator()(const QList<double>& input);

	private:
		QList<Layer> layer;
};

}

#endif // NETWORK_H
