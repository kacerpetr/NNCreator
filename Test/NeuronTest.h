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

#ifndef NEURONTEST_H
#define NEURONTEST_H

#include <QObject>
#include "NeuralNetwork/Neuron.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of Neuron class.
 */
class NeuronTest : public QObject{
	Q_OBJECT

	private slots:
		void test1();
		void test2();
		void test3();
		void test4();
		void test5();
};

}

#endif // NEURONTEST_H
