/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NEURON_H
#define NEURON_H

#include <QString>
#include <QList>
#include "Util/Globaldef.h"
#include "Dataset.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Class that represents artificial neuron.
 */
class Neuron{
	public:
		Neuron();
        Neuron(const Neuron& neuron);
		void setTrFcn(TransferFcn trFcn);
		TransferFcn trFcn() const;
        double bias() const;
        void setBias(double bias);
        void addBias(double value);
        double slope() const;
        void setSlope(double slope);
        QList<double> weights() const;
		void setWeights(const QList<double>& weights);
        void removeWeight(int weightIndex);
		void removeLastWeight();
		void leaveWeight(int count);
		void insertWeight(int weightIndex, double value);	
		void appendWeight(double value);
		void appendWeights(int count, double value);
        int weightCount() const;
		double output(const QList<double>& input) const;
		double output(double input) const;
        QString toString() const;
		double& operator[](int weightIndex);
        Neuron& operator=(const Neuron& neuron);
        double trFcn(double x) const;
        double trFcnD(double x) const;
		~Neuron();

	private:
		/** Value of neuron bias. */
		double biasVal;
		/** Value of slope of transfer function. */
		double slopeVal;
		/** Transfer function type. */
		TransferFcn trFcnType;
		/** List of neuron weights. */
		QList<double> weight;
};

}

#endif // NEURON_H
