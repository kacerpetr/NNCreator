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

#ifndef MLNNETST_H
#define MLNNETST_H

#include "AbstractMlnNet.h"
#include "Neuron.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Implementation of multi layer neural network.
 */
class MlnNetSt : public AbstractMlnNet{
	public:
		MlnNetSt();
		MlnNetSt(const MlnNetSt& obj);
		void setInputCount(int count);
		void appendLayer();
		void insertLayer(int position);
		void removeLayer(int layer);
		void duplicateLayer(int layer);
		void appendNeuron(int layer);
		void appendNeuron(int layer, int count);
		void appendNeuron(int layer, const Neuron& neuron);
		void removeLastNeuron(int layer);
		void insertNeuron(int layer, int position);
		void removeNeuron(int layer, int position);
		void setNeuronCount(int layer, int count);
		int inputCount() const;
		int layerCount() const;
		int neuronCount() const;
		int neuronCount(int layer) const;
		int weightCount() const;
		int weightCount(int layer) const;
		int outputCount() const;
		void setBias(double value);
		void randomizeWeight(int seed, double min, double max);
		void randomizeBias(int seed, double min, double max);
        void randomizeSlope(int seed, double min, double max);
		void setTransferFunction(TransferFcn trFcn);
		QList<double> output(const QList<double>& input) const;
		QList< QList<double> > layerOutput(const QList<double>& input) const;
		QList<Neuron>& operator[](int layer);
		QString toString() const;
		virtual ~MlnNetSt();

	private:
		/** Number of inputs of neural network, serves as input layer. */
		int inCnt;
		/** List of neural network layers. */
		QList< QList<Neuron> > net;
};

}

#endif //MLNNETST_H
