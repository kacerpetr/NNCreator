#ifndef LAYER_H
#define LAYER_H

/*
 * This file is part of neuron network experimental implementation.
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

#include <QTextStream>
#include "Neuron.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{

/**
 * Class Layer represents one layer of multilayer neuron network.
 *
 * @package NeuronNetwork
 */
class Layer{
	/*public:
		Layer(void);

		Layer(int neuronCount);

		Layer(Layer& layer);

		Neuron getNeuron(unsigned int index) const;

		void setNeuron(const Neuron neuron);

		Array<double> getOuptuts();

	private:
		int neuronCount;
		Array<Neuron>* neuron;
*/
};

}

#endif // LAYER_H
