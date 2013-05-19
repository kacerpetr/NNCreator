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

#include "LrnEngine.h"
#include <QDebug>

namespace NeuralNetwork{

/**
 * Creates unconfigured learning engine.
 */
LrnEngine::LrnEngine() : QObject(){}

/**
 * Sets pointer to learning algorithm class.
 */
void LrnEngine::setAlgorithm(AbstractLrnAlg* algorithm){
	Q_ASSERT(algorithm != NULL);
	thread = new QThread(this);
	alg = algorithm;
	alg->moveToThread(thread);
	connect(thread, SIGNAL(started()), alg, SLOT(start()));
    connect(alg, SIGNAL(stoped()), thread, SLOT(quit()));
	connect(thread, SIGNAL(finished()), this, SLOT(delThread()));
}

/**
 * Returns pointer to learning algorithm class.
 */
AbstractLrnAlg* LrnEngine::getAlgorithm(){
	return alg;
}

/**
 * Waits until learning is finished.
 */
void LrnEngine::waitToFinish(int maxTime){
    thread->wait(maxTime);
}

/**
 * Starts learning in secondary thread.
 */
void LrnEngine::startThread(){
	thread->start();
}

/**
 * Stops learning in secondary thread.
 */
void LrnEngine::stopThread(){
	Q_ASSERT(alg != NULL);
	alg->stop();
}

void LrnEngine::delThread(){
	delete thread;
	thread = NULL;
	delete alg;
	alg = NULL;
}

/**
 * Class destructor.
 */
LrnEngine::~LrnEngine(){}

}

