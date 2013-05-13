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

#include <QtTest/QtTest>
#include <QDebug>
#include "DatasetTest.h"

namespace Test{

/**
 * First test of dataset class.
 */
void DatasetTest::test1(){
	Dataset set;

	set.setMinSize(10, 8, 7);

	QVERIFY(set.minPatternCount() == 10);
	QVERIFY(set.minInputCount() == 8);
	QVERIFY(set.minOutputCount() == 7);
	QVERIFY(set.patternCount() == 10);
    QVERIFY(set.inputCount(0) == 8);
    QVERIFY(set.outputCount(0) == 7);
	QVERIFY(set.isConsistent() == false);
	QVERIFY(set.input(6,2) == 0);
	QVERIFY(set.output(2,5) == 0);
	QVERIFY(set.isInputNull(6,2) == true);
	QVERIFY(set.isOutputNull(2,5) == true);

	set.setInput(6, 2, 0.55);
	set.setOutput(2, 5, 0.57);

	QVERIFY(set.input(6,2) == 0.55);
	QVERIFY(set.output(2,5) == 0.57);
	QVERIFY(set.isInputNull(6,2) == false);
	QVERIFY(set.isOutputNull(2,5) == false);
	QVERIFY(set.isConsistent() == false);

	set.setMinSize(4, 5, 6);

	QVERIFY(set.minPatternCount() == 4);
	QVERIFY(set.minInputCount() == 5);
	QVERIFY(set.minOutputCount() == 6);
	QVERIFY(set.patternCount() == 10);
    QVERIFY(set.inputCount(0) == 8);
    QVERIFY(set.outputCount(0) == 7);
	QVERIFY(set.input(6,2) == 0.55);
	QVERIFY(set.output(2,5) == 0.57);
	QVERIFY(set.isInputNull(6,2) == false);
	QVERIFY(set.isOutputNull(2,5) == false);
	QVERIFY(set.isConsistent() == false);

	set.reduceToMinSize();

	QVERIFY(set.minPatternCount() == 4);
	QVERIFY(set.minInputCount() == 5);
	QVERIFY(set.minOutputCount() == 6);
	QVERIFY(set.patternCount() == 4);
    QVERIFY(set.inputCount(0) == 5);
    QVERIFY(set.outputCount(0) == 6);
	QVERIFY(set.output(2,5) == 0.57);
	QVERIFY(set.isOutputNull(2,5) == false);
	//qDebug() << set.toString();
}

/**
 * Second test of dataset class.
 */
void DatasetTest::test2(){
	Dataset set;

	set.setMinSize(2, 2, 2);

	set.setOutput(0, 0, 11.5);
	set.setOutput(0, 1, 1.5);
	set.setOutput(1, 0, 5.11);
	set.setOutput(1, 1, 666);

	set.setInput(0, 0, 11.5);
	set.setInput(0, 1, 1.5);
	set.setInput(1, 0, 5.11);
	set.setInput(1, 1, 666);

	QVERIFY(set.patternCount() == 2);
    QVERIFY(set.inputCount(0) == 2);
    QVERIFY(set.outputCount(0) == 2);
	QVERIFY(set.isConsistent() == true);

	set.setMinSize(5, 5, 5);
	set.setMinSize(2, 2, 2);

	QVERIFY(set.patternCount() == 5);
    QVERIFY(set.inputCount(0) == 5);
    QVERIFY(set.outputCount(0) == 5);
	QVERIFY(set.minPatternCount() == 2);
	QVERIFY(set.minInputCount() == 2);
	QVERIFY(set.minOutputCount() == 2);
	QVERIFY(set.isConsistent() == true);

	set.setMinSize(0, 0, 0);

	QVERIFY(set.patternCount() == 5);
    QVERIFY(set.inputCount(0) == 5);
    QVERIFY(set.outputCount(0) == 5);
	QVERIFY(set.minPatternCount() == 0);
	QVERIFY(set.minInputCount() == 0);
	QVERIFY(set.minOutputCount() == 0);
	QVERIFY(set.isConsistent() == true);

	set.setMinSize(1, 1, 1);
	set.reduceToMinSize();

	QVERIFY(set.isConsistent() == true);

	set.setMinSize(0, 0, 0);
	set.reduceToMinSize();

	QVERIFY(set.patternCount() == 0);
	QVERIFY(set.isConsistent() == true);

	set.setMinSize(0, 0, 0);
	set.reduceToMinSize();

	QVERIFY(set.isConsistent() == true);

	set.setMinSize(1, 2, 2);
	QVERIFY(set.patternCount() == 1);
    QVERIFY(set.inputCount(0) == 2);
    QVERIFY(set.outputCount(0) == 2);
	QVERIFY(set.isConsistent() == false);
}

}
