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

#ifndef LRNENGINE_H
#define LRNENGINE_H

#include <QObject>
#include <QThread>
#include "BpAlgSt.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Engine to run learning of neural network in secondary thread.
 */
class LrnEngine : public QObject{
	Q_OBJECT

	public:
		LrnEngine();
		void setAlgorithm(AbstractLrnAlg* algorithm);
		AbstractLrnAlg* getAlgorithm();
        void waitToFinish(int maxTime);
		~LrnEngine();

	public slots:
		void startThread();
		void stopThread();

	private slots:
		void delThread();

	private:
		/** Pointer to QThread instance. */
		QThread* thread;
		/** Pointer to learning algorithm. */
		AbstractLrnAlg* alg;
};

}

#endif //LRNENGINE_H
