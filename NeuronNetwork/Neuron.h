#ifndef NEURON_H
#define NEURON_H

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
#include <QStringList>
#include <QDebug>
#include "math.h"
//#include "Common/Array.h"
#include "Exception.h"

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuronNetwork{
	class Neuron;
}

/**
 * Neuron transfer functions.
 *
 * NOT_LINEAR
 * f(x)=
 * 1 when x ≥ 1
 * 0 when x < 0
 *
 * SATURATED_LINEAR
 * f(x)=
 * 1 when x ≥ 1
 * x when 0 ≤ x ≤ 1
 * 0 when x < 0
 *
 * STANDARD_LOGISTIC
 * f(x)= 1 / (1 + e^-x)
 *
 * HYPERBOLIC_TANGENS
 * f(x)= (1 - e^-x) / (1 + e^-x)
 */
enum TransferFunction{
	NOT_LINEAR = 1,
	SATURATED_LINEAR = 2,
	STANDARD_LOGISTIC = 3,
	HYPERBOLIC_TANGENS = 4
};

/**
 * Class Neuron represents single formal neuron with bias.
 *
 * @package NeuronNetwork
 */
class Neuron{

};



#endif // NEURON_H
