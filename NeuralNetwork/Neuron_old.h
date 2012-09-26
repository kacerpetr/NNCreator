#ifndef NEURON_H
#define NEURON_H

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
#include <QString>

/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

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
class Neuron_old{
	public:
		Neuron_old(void);
		Neuron_old(const Neuron_old& neuron);
		Neuron_old(QString str);

		double getBias(void) const;
		void setBias(double bias);

		double getWeight(unsigned int index) const;
		void setWeight(unsigned int index, double value);
		double removeWeight(unsigned int index);
		void insertWeight(unsigned int index, double value);
		void appendWeight(double value);

		QList<double> getWeights(void) const;
		void setWeights(const QList<double>& weight);

		TransferFunction getTransferFunction(void) const;
		void setTransferFunction(const TransferFunction trFcn);

		QString toString(void);
		double transferFcn(double x) const;
		static Neuron_old fromString(const QString str);

		double operator()(const QList<double>& input) const;
		double operator()(const double input) const;
		Neuron_old& operator=(const Neuron_old& neuron);

	private:
		double bias;
		TransferFunction trFcn;
		QList<double> weight;
};

}

#endif // NEURON_H
