#ifndef LAYER_H
#define LAYER_H

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

#include <QList>
#include "Neuron_old.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

/**
 * Class Layer represents one layer of multilayer neuron network.
 *
 * @package NeuronNetwork
 */
class Layer{
	public:
		Layer(void);
		Layer(const Layer& layer);
		Layer(QString str);

		void appendNeuron(const Neuron_old& neuron);
		Neuron_old getNeuron(unsigned int index) const;
		void setNeuron(unsigned int index, const Neuron_old& neuron);
		void insertNeuron(unsigned int index, const Neuron_old& neuron);
		Neuron_old removeNeuron(unsigned int index);

		bool isInput() const;
		void setInput(const bool input);

		unsigned int getCount();

		QString toString(void);
		static Layer fromString(QString str);

		QList<double> operator()(QList<double> input);

	private:
		bool input;
		QList<Neuron_old> neuron;
};

}

#endif // LAYER_H
