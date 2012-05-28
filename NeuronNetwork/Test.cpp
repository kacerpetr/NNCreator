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
/*
void Test::arrayConstructor(){
	Array<double> a;
	QCOMPARE(a.toString(), QString("[]"));

	Array<double> b = Array<double>(4, 1.8);
	QCOMPARE(b.toString(), QString("[1.8, 1.8, 1.8, 1.8]"));

	Array<double> c = Array<double>(b);
	QCOMPARE(c.toString(), QString("[1.8, 1.8, 1.8, 1.8]"));
}

void Test::arrayFill(){
	Array<double> a = Array<double>(5, 0.0);
	a.fill(11.215);
	QCOMPARE(a.toString(), QString("[11.215, 11.215, 11.215, 11.215, 11.215]"));

	Array<double> b;
	b.fill(11.215);
	QCOMPARE(b.toString(), QString("[]"));
}

void Test::arrayOperators(){
	Array<double> a = Array<double>(7, 1.1);
	Array<double> b = Array<double>(5, 0.65);
	a = b;
	QCOMPARE(a.toString(), QString("[0.65, 0.65, 0.65, 0.65, 0.65]"));
	QVERIFY(a.length() == b.length());
}

void Test::neuronOutputTrFc1(){
	Array<double> weight = Array<double>(5, 0);
	weight[0] = 1.6;
	weight[2] = 2.9;
	weight[4] = 0.21;
	Array<double> input = Array<double>(5, 0.3);
	input[1] = 0.01;
	input[3] = 3.1;

	Neuron a = Neuron(5);
	a.setWeight(weight);
	a.setTransferFunction(NOT_LINEAR);
	QCOMPARE(a(input), 1.0);

	weight[2] = -5.5;
	Neuron b = Neuron(5);
	b.setWeight(weight);
	b.setTransferFunction(NOT_LINEAR);
	QCOMPARE(b(input), 0.0);

	weight.fill(0);
	input.fill(0);
	Neuron c = Neuron(5);
	c.setWeight(weight);
	c.setTransferFunction(NOT_LINEAR);
	QCOMPARE(b(input), 0.0);
}

void Test::neuronOutputTrFc2(){
	Array<double> weight = Array<double>(5, 0.0);
	weight[0] = 0.6;
	weight[2] = 1.9;
	weight[4] = 0.21;
	Array<double> input = Array<double>(5, 0.3);
	input[1] = 0.01;
	input[4] = 0.1;

	Neuron a = Neuron(5);
	a.setWeight(weight);
	a.setTransferFunction(SATURATED_LINEAR);
	QCOMPARE(a(input), 0.77100);

	Neuron b = a;
	b.setBias(0.3);
	QCOMPARE(b(input), 1.0);

	Neuron c = Neuron(a);
	c.setBias(-0.8);
	QCOMPARE(c(input), 0.0);

	QCOMPARE(a(input), 0.77100);
}

void Test::neuronOutputTrFc3(){
	Array<double> weight = Array<double>(3, 0.0);
	weight[0] = 0.6;
	weight[1] = 1.9;
	weight[2] = 0.21;
	Array<double> input = Array<double>(3, 0.0);
	input[0] = 0.01;
	input[1] = 0.1;
	input[2] = 0.15;

	Neuron a = Neuron(3);
	a.setWeight(weight);
	a.setTransferFunction(STANDARD_LOGISTIC);
	QCOMPARE((int)(a(input)*100000), 55663);

	Neuron b = a;
	b.setBias(0.6);
	QCOMPARE((int)(b(input)*100000), 69582);

	Neuron c = Neuron(a);
	c.setBias(-1.0);
	QCOMPARE((int)(c(input)*100000), 31593);

	Neuron d = Neuron();
	d.setWeight(Array<double>(0, 0.0));
	QCOMPARE(d(Array<double>(0, 0.0)), 0.0);
}

void Test::neuronOutputTrFc4(){
	Array<double> weight = Array<double>(3, 0.0);
	weight[0] = 0.6;
	weight[1] = 1.9;
	weight[2] = 0.21;
	Array<double> input = Array<double>(3, 0.0);
	input[0] = 0.01;
	input[1] = 0.1;
	input[2] = 0.15;

	Neuron a = Neuron(3);
	a.setWeight(weight);
	a.setTransferFunction(HYPERBOLIC_TANGENS);
	QCOMPARE((int)(a(input)*100000), 11326);

	Neuron b = a;
	b.setBias(2.6);
	QCOMPARE((int)(b(input)*100000), 88828);

	Neuron c = Neuron(a);
	c.setBias(-3.0);
	QCOMPARE((int)(c(input)*100000), -88234);

	Neuron d = Neuron();
	d.setWeight(Array<double>(0, 0.0));
	QCOMPARE(d(Array<double>(0, 0.0)), 0.0);
}

void Test::neuronToString(){
	Array<double> weight = Array<double>(3, 0.0);
	weight[0] = 0.6;
	weight[1] = 1.9;
	weight[2] = 0.21;

	Neuron a = Neuron();
	QCOMPARE(a.toString(), QString("Neuron:\nweights = [0]\nbias = 0\ntransferFunction = 4"));

	Neuron b = Neuron(3);
	QCOMPARE(b.toString(), QString("Neuron:\nweights = [0, 0, 0]\nbias = 0\ntransferFunction = 4"));

	Neuron c = Neuron(3);
	c.setWeight(weight);
	c.setBias(0.12);
	c.setTransferFunction(STANDARD_LOGISTIC);
	QCOMPARE(c.toString(), QString("Neuron:\nweights = [0.6, 1.9, 0.21]\nbias = 0.12\ntransferFunction = 3"));
}

void Test::neuronTextFromTo(){
	try{
		QString str = "Neuron:\nweights = [0.6, 1.9, 0.21]\nbias = 0.12\ntransferFunction = 3";
		Neuron a = Neuron::valueOf(str);
		QCOMPARE(a.toString(), str);
	}catch(Exception& ex){
		qDebug() << (ex.toString());
	}

	try{
		QString str = QString("Neuron:\nweights = [41, 12.6, 0.21]\nbias = 1\ntransferFunction = 5");
		Neuron a = Neuron::valueOf(str);
		QCOMPARE(a.toString(), str);
	}catch(Exception& ex){
		QCOMPARE(ex.toString(), QString("NeuronException: valueOf() parse error, expected integer between 1 and 4, given: \"5\""));
	}

	try{
		QString str = QString("Neuron:\nweights = []\nbias = 1\ntransferFunction = 5");
		Neuron a = Neuron::valueOf(str);
		QCOMPARE(a.toString(), str);
	}catch(Exception& ex){
		QCOMPARE(ex.toString(), QString("NeuronException: valueOf() parse error, expected double in: \"\""));
	}

	try{
		QString str = QString("");
		Neuron a = Neuron::valueOf(str);
		QCOMPARE(a.toString(), str);
	}catch(Exception& ex){
		QCOMPARE(ex.toString(), QString("NeuronException: valueOf() parse error, unexpected keyword: \"\", expected: \"Neuron:\""));
	}
}
*/
}























