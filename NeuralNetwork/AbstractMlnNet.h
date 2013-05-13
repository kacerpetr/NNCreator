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

#ifndef ABSTRACTMLNNET_H
#define ABSTRACTMLNNET_H

#include <QString>
#include <QList>
#include "Neuron.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Interface for multilayer neural network.
 */
class AbstractMlnNet{
	public:
		/** Sets number of network inputs, works as input layer. */
		virtual void setInputCount(int count) = 0;

		/** Appends layer with one neuron. */
		virtual void appendLayer() = 0;

		/** Inserts layer with one neuron to network. */
		virtual void insertLayer(int position) = 0;

		/** Removes layer from network. */
		virtual void removeLayer(int layer) = 0;

		/** Duplicates neural network layer. */
		virtual void duplicateLayer(int layer) = 0;

		/** Appends new neuron to layer. */
		virtual void appendNeuron(int layer) = 0;

		/** Appends count of new neurons to layer. */
		virtual void appendNeuron(int layer, int count) = 0;

		/** Appends given neuron to layer. */
		virtual void appendNeuron(int layer, const Neuron& neuron) = 0;

		/** Removes last neuron from layer. */
		virtual void removeLastNeuron(int layer) = 0;

		/** Inserts new neuron to given positon of given layer. */
		virtual void insertNeuron(int layer, int position) = 0;

		/** Removes neuron from given positon of given layer. */
		virtual void removeNeuron(int layer, int position) = 0;

		/** Returns count of inputs of network. */
		virtual int inputCount() const = 0;

		/** Returns count of layers in network. */
		virtual int layerCount() const = 0;

		/** Returns count of neurons in network. */
		virtual int neuronCount() const = 0;

		/** Returns count of neurons in layer of network. */
		virtual int neuronCount(int layer) const = 0;

		/** Returns count of weights of all neurons in network. */
		virtual int weightCount() const = 0;

		/** Sets bias of all neurons in network. */
		virtual void setBias(double value) = 0;

		/** Randomizes all neuron weights in network. */
		virtual void randomizeWeight(int seed, double min, double max) = 0;

		/** Randomizes all biases of neurons in network. */
		virtual void randomizeBias(int seed, double min, double max) = 0;

		/** Randomizes all neuron weights in network. */
		virtual void setTransferFunction(TransferFcn trFcn) = 0;

		/**
		 * Returns list of output values of neural network.
		 * @param input length of input vector must be the same as input count of network
		 */
		virtual QList<double> output(const QList<double>& input) const = 0;

		/**
		 * Returns outputs of all layers obtained during input feedforwarding.
		 * @param input length of input vector must be the same as input count of network
		 * @note first vector in list of outputs in network input (= input layer output)
		 */
		virtual QList< QList<double> > layerOutput(const QList<double>& input) const = 0;

		/** Returns reference to list of neurons of given layer. */
		virtual QList<Neuron>& operator[](int layer) = 0;

		/** Returns string representation of neural network. */
		virtual QString toString() const = 0;
};

}
#endif //ABSTRACTMLNNETWORK_H
