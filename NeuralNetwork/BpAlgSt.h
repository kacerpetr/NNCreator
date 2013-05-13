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

#ifndef BACKPROPAGATION_H
#define BACKPROPAGATION_H

#include <QObject>
#include <QElapsedTimer>
#include "AbstractLrnAlg.h"

/**
 * Contains data structures and algorithms needed for neural network designing and learning.
 */
namespace NeuralNetwork{

/**
 * Single threaded implementation of back propagation algorithm.
 */
class BpAlgSt : public AbstractLrnAlg{
	Q_OBJECT

	public:
		BpAlgSt();
		BpAlgSt(BpAlgSt& obj);
		BpAlgSt(BpAlgSt* obj);
		void setNetwork(AbstractMlnNet* net);
		void setDataset(Dataset* data);
		void setUpdateInterval(int interval);
		void setStopIteration(int stopIter);
		void setStopError(double stopErr);
		void setStopTime(long stopTime);
		void setAlpha(double alpha);
		AbstractMlnNet* network();
		Dataset* dataset();
		int updateInterval() const;
		int stopIteration() const;
		double stopError() const;
		long stopTime() const;
		bool isRunning() const;
		int currentIteration() const;
		double currentError() const;
		long currentTime() const;
		double alpha() const;
		~BpAlgSt();

	public slots:
		void start();
		void stop();

	private:
		double calcError(int pattern);
		void calcOutputDelta(int pattern);
		void calcInnerDelta();
		void adjustWeight();
		void genDeltaArray();

	private:
		/** Update signal will be emited once after each interval of iterations. */
		int updateInterv;
		/** When this number of iterations is reached, learning will be stoped. */
		int stopIter;
		/** Learning will be stoped when actual error is less or equal to this value. */
		double stopErrorVal;
		/** Maximal time length of learning in miliseconds. */
		long stopTimeVal;
		/** Flag that tells that learning is in process. */
		bool running;
		/** Pointer to learned neural network. */
		AbstractMlnNet* net;
		/** Pointer to dataset of training patterns. */
		Dataset* data;
		/** Actual learning time in miliseconds. */
		long actTime;
		/** Actual iteration of learning. */
		int actIter;
		/** Actual error of neural network during learning. */
		double actError;
		/** Storage of calculated deltas. */
		QList< QList<double> > delta;
		/** Outputs of individual layers of neural network. */
		QList< QList<double> > output;
		/** Timer instance, used for learning time measurement. */
		QElapsedTimer timer;
		/** Learning speed coeficient alpha. */
		double alphaVal;
};

}

#endif // BACKPROPAGATION_H
