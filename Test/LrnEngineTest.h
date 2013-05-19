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

#ifndef LRNENGINETEST_H
#define LRNENGINETEST_H

#include <QObject>
#include "NeuralNetwork/LrnEngine.h"
#include "NeuralNetwork/Dataset.h"
#include "NeuralNetwork/MlnNetSt.h"
using namespace NeuralNetwork;

/**
 * Contains all application test code.
 */
namespace Test{

/**
 * Contains test code of MlnNetSt class.
 */
class LrnEngineTest : public QObject{
	Q_OBJECT

	public slots:
		void lrnStarted();
		void lrnUpdate(int iteration, long time, double error);
        void lrnStoped();

	private slots:
		void initTestCase();
		void learningTest();

	private:
		/** Test dataset. */
		Dataset set;
		/** Test neural network. */
		MlnNetSt net;
		/** Tested learning algorithm. */
		BpAlgSt alg;
		/** Tested learning engine. */
		LrnEngine eng;
};

}

#endif //LRNENGINETEST_H
