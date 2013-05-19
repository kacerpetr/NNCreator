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

#include "LrnEngineTest.h"
#include <QWaitCondition>
#include <QtTest/QtTest>
#include <QDebug>

namespace Test{

/**
 * Slot connected to started signal of learning algorithm class.
 * @see AbstractLrnAlg::started()
 */
void LrnEngineTest::lrnStarted(){
	qDebug() << "Learning started ...";
}

/**
 * Slot connected to update signal of learning algorithm class.
 * @see AbstractLrnAlg::update(int iteration, long time, double error)
 */
void LrnEngineTest::lrnUpdate(int iteration, long time, double error){
	qDebug() << "Learning update: " << iteration << ", " << time << ", " << error;
}

/**
 * Slot connected to stoped signal of learning algorithm class.
 * @see AbstractLrnAlg::stoped(int iteration, long time, double error)
 */
void LrnEngineTest::lrnStoped(){
    qDebug() << "Learning stoped";
}

/**
 * Initializes test data.
 */
void LrnEngineTest::initTestCase(){
	//training dataset
	set.setMinSize(4,2,1);
	//inputs
	set.setInput(0, 0, 0);
	set.setInput(0, 1, 0);
	set.setInput(1, 0, 0);
	set.setInput(1, 1, 1);
	set.setInput(2, 0, 1);
	set.setInput(2, 1, 0);
	set.setInput(3, 0, 1);
	set.setInput(3, 1, 1);
	//outputs
	set.setOutput(0, 0, 0);
	set.setOutput(1, 0, 1);
	set.setOutput(2, 0, 1);
	set.setOutput(3, 0, 0);

	//neural network
	net.setInputCount(2);
	net.appendLayer();
	//inner layer
	net.appendNeuron(0, 3);
	net[0][0][0] = 0.1970;
	net[0][0][1] = 0.3009;
	net[0][0].setBias(-0.3378);
	net[0][1][0] = 0.3191;
	net[0][1][1] = 0.1904;
	net[0][1].setBias(0.2771);
	net[0][2][0] = -0.1448;
	net[0][2][1] = -0.0347;
	net[0][2].setBias(0.2859);
	net[0][3][0] = 0.3594;
	net[0][3][1] = -0.4861;
	net[0][3].setBias(-0.3329);
	//output layer
	net[1][0][0] = 0.4919;
	net[1][0][1] = -0.2913;
	net[1][0][2] = -0.3979;
	net[1][0][3] = 0.3581;
	net[1][0].setBias(-0.1401);

	//learning
	alg.setDataset(&set);
	alg.setNetwork(&net);
	alg.setAlpha(0.2);
	alg.setStopError(0.01);
	alg.setStopTime(2500);
	alg.setStopIteration(4000);
	alg.setUpdateInterval(200);

	connect(&alg, SIGNAL(started()), this, SLOT(lrnStarted()), Qt::DirectConnection);
    connect(&alg, SIGNAL(stoped()), this, SLOT(lrnStoped()), Qt::DirectConnection);
	connect(&alg, SIGNAL(update(int,long,double)), this, SLOT(lrnUpdate(int,long,double)), Qt::DirectConnection);
}

/**
 * Test of learning engine.
 */
void LrnEngineTest::learningTest(){
    eng.setAlgorithm(&alg);
    eng.startThread();
    eng.waitToFinish(500);
}

}
