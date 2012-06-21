/*
 * This file is part of neuron network experimental implementation.
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2012 Petr Kacer (kacerpetr@gmail.com)
 */

#include "Test.h"

namespace NeuronNetwork{

void Test::neuronOutput(void){
	QList<double> input;
	input << 1.12 << 0.2 << -0.33 << -0.88;

	Neuron n1;
	n1.appendWeight(1.25);
	n1.appendWeight(-1.25);
	n1.appendWeight(2.25);
	n1.appendWeight(-0.58);
	n1.setBias(0.5);

	n1.setTransferFunction(STANDARD_LOGISTIC);
	QCOMPARE(ROUND6(n1(input)), 0.805008);

	n1.setTransferFunction(HYPERBOLIC_TANGENS);
	QCOMPARE(ROUND6(n1(input)), 0.610017);

	n1.setTransferFunction(SATURATED_LINEAR);
	QCOMPARE(n1(input), 1.0);

	n1.setTransferFunction(NOT_LINEAR);
	QCOMPARE(n1(input), 1.0);
}

void Test::inputLayerOutput(void){
	QList<double> input;
	input << 1.12 << 0.2 << -0.33;

	Neuron n1;
	n1.appendWeight(1.25);
	n1.setBias(0.5);

	Neuron n2;
	n2.appendWeight(0.45);
	n2.setBias(-0.5);

	Neuron n3;
	n3.appendWeight(1.25);
	n3.setBias(0.1);

	Layer l1;
	l1.setInput(true);
	l1.appendNeuron(n1);
	l1.appendNeuron(n2);
	l1.appendNeuron(n3);

	QList<double> output = l1(input);
	qDebug() << output;

/*	double out1 = HTAN(1.12*1.25 + 0.5);
	double out2 = HTAN(0.2*0.45 - 0.5);
	double out3 = HTAN(1.25*-0.33 + 0.1);

	QCOMPARE(output[0], out1);
	QCOMPARE(output[1], out2);
	QCOMPARE(output[2], out3 );*/
}

void Test::innerLayerOutput(void){
	QList<double> input;
	input << 1.12 << 0.2 << -0.33 << -0.88;

	Neuron n1;
	n1.appendWeight(1.25);
	n1.appendWeight(-1.25);
	n1.appendWeight(2.25);
	n1.appendWeight(-0.58);
	n1.setBias(0.5);

	Neuron n2;
	n2.appendWeight(1.25);
	n2.appendWeight(-1.25);
	n2.appendWeight(2.25);
	n2.appendWeight(-0.58);
	n2.setBias(0.5);

	Neuron n3;
	n3.appendWeight(1.25);
	n3.appendWeight(-1.25);
	n3.appendWeight(2.25);
	n3.appendWeight(-0.58);
	n3.setBias(0.5);

	Layer l1;
	l1.appendNeuron(n1);
	l1.appendNeuron(n2);
	l1.appendNeuron(n3);

	qDebug() << l1(input);
}

void Test::networkOutput(void){

}

}




















