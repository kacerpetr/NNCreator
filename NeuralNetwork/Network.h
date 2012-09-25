#ifndef NETWORK_H
#define NETWORK_H

/*
 * This file is part of neuron network implementation.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2012 Petr Kacer (kacerpetr@gmail.com)
 */

#include "INeuralNetwork.h"
#include <QTextStream>
#include "Layer.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

class Network{
	public:
		Network(void);
		Network(const Network& network);

		void appendLayer(const Layer& layer);
		Layer getLayer(unsigned int index) const;
		void setLayer(unsigned int index, const Layer& layer);
		void insertLayer(unsigned int index, const Layer& layer);
		Layer removeLayer(unsigned int index);

		unsigned int getCount();

		QString toString(void);
		Layer fromString(QString str);

		QList<double> operator()(const QList<double>& input);

	private:
		QList<Layer> layer;
};

}

#endif // NETWORK_H
