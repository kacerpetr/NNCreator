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
#include "Exception.h"

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

void Test::neuronToString(void){
	Neuron n1;
	n1.appendWeight(-10000);
	n1.appendWeight(266.22221);
	n1.appendWeight(0);
	n1.appendWeight(0.285);
	n1.appendWeight(-0.5566448855);
	n1.appendWeight(1000.018855664477);
	n1.setBias(0.5);
	qDebug() << n1.toString();
	QCOMPARE(n1.toString(), QString("[4 0.5000000000 -10000.0000000000 266.2222100000 0.0000000000 0.2850000000 -0.5566448855 1000.0188556645]"));

	Neuron n2;
	n2.appendWeight(0);
	n2.setTransferFunction(NOT_LINEAR);
	qDebug() << n2.toString();
	QCOMPARE(n2.toString(), QString("[1 0.0000000000 0.0000000000]"));

	Neuron n3;
	n3.setTransferFunction(STANDARD_LOGISTIC);
	qDebug() << n3.toString();
	QCOMPARE(n3.toString(), QString("[3 0.0000000000]"));
}

void Test::neuronFromString(void){
	Neuron n1 = Neuron("[4 -10000.0000000000 266.2222100000 0.0000000000 0.2850000000 -0.5566448855 1000.0188556645]");
	qDebug() << n1.getBias();
	qDebug() << n1.toString();
	QCOMPARE(n1.toString(), QString("[4 -10000.0000000000 266.2222100000 0.0000000000 0.2850000000 -0.5566448855 1000.0188556645]"));

	Neuron n2 = Neuron("");
	qDebug() << n2.toString();
	QCOMPARE(n2.toString(), QString("[4 0.0000000000]"));

	Neuron n3 = Neuron("[]");
	qDebug() << n3.toString();
	QCOMPARE(n3.toString(), QString("[4 0.0000000000]"));

	Neuron n4 = Neuron("[2]");
	qDebug() << n4.toString();
	QCOMPARE(n4.toString(), QString("[2 0.0000000000]"));

	Neuron n5 = Neuron("[3 0.25]");
	qDebug() << n5.toString();
	QCOMPARE(n5.toString(), QString("[3 0.2500000000]"));

	// bad inputs
	try{
		Neuron n = Neuron("[3 0.25v fdgdg]");
	}catch(Exception ex){
		qDebug() << ex.toString();
	}

	try{
		Neuron n = Neuron("[3g 154 2]");
	}catch(Exception ex){
		qDebug() << ex.toString();
	}

	try{
		Neuron n = Neuron("3 0.25 1]");
	}catch(Exception ex){
		qDebug() << ex.toString();
	}

	try{
		Neuron n = Neuron("[3 0.25 1 154d]");
	}catch(Exception ex){
		qDebug() << ex.toString();
	}
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

	double out1 = HTAN(1.12*1.25 + 0.5);
	double out2 = HTAN(0.2*0.45 - 0.5);
	double out3 = HTAN(1.25*-0.33 + 0.1);

	QCOMPARE(output[0], out1);
	QCOMPARE(output[1], out2);
	QCOMPARE(output[2], out3 );
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
	n2.appendWeight(1.11);
	n2.appendWeight(-1.05);
	n2.appendWeight(0.25);
	n2.appendWeight(-0.44);
	n2.setBias(-0.5);

	Layer l1;
	l1.appendNeuron(n1);
	l1.appendNeuron(n2);

	QList<double> output = l1(input);
	qDebug() << output;

	double out1 = HTAN(1.12*1.25 + 0.2*-1.25 - 0.33*2.25 - 0.88*-0.58 + 0.5);
	double out2 = HTAN(1.12*1.11 + 0.2*-1.05 - 0.33*0.25 - 0.88*-0.44 - 0.5);

	QCOMPARE(output[0], out1);
	QCOMPARE(output[1], out2);
}

void Test::layerToString(void){

}

void Test::layerFromString(void){

}

void Test::networkOutput(void){
	QList<double> input;
	input << 0.92 << -0.16;

	// input layer
	Neuron ni1;
	ni1.appendWeight(-0.88);
	ni1.setBias(0.15);

	Neuron ni2;
	ni2.appendWeight(-0.10);
	ni2.setBias(-0.12);

	Layer li;
	li.appendNeuron(ni1);
	li.appendNeuron(ni2);
	li.setInput(true);

	QList<double> output_i = li(input);
	qDebug() << "input layer: " << output_i;

	double out_i1 = HTAN(0.92*-0.88 + 0.15)
	double out_i2 = HTAN(-0.16*-0.10 - 0.12)

	QCOMPARE(output_i[0], out_i1);
	QCOMPARE(output_i[1], out_i2);

	// inner layer
	Neuron n11;
	n11.appendWeight(0.15);
	n11.appendWeight(0.33);
	n11.setBias(0.01);

	Neuron n12;
	n12.appendWeight(1.55);
	n12.appendWeight(-0.95);
	n12.setBias(-0.52);

	Neuron n13;
	n13.appendWeight(0.50);
	n13.appendWeight(0.30);
	n13.setBias(0.35);

	Layer l1;
	l1.appendNeuron(n11);
	l1.appendNeuron(n12);
	l1.appendNeuron(n13);

	QList<double> output_1 = l1(output_i);
	qDebug() << "inner layer: " << output_1;

	double out_11 = HTAN(out_i1*0.15 + out_i2*0.33 + 0.01)
	double out_12 = HTAN(out_i1*1.55 - out_i2*0.95 - 0.52)
	double out_13 = HTAN(out_i1*0.50 + out_i2*0.30 + 0.35)

	QCOMPARE(output_1[0], out_11);
	QCOMPARE(output_1[1], out_12);
	QCOMPARE(output_1[2], out_13);

	// output layer
	Neuron no1;
	no1.appendWeight(0.75);
	no1.appendWeight(-0.25);
	no1.appendWeight(0.33);
	no1.setBias(0.0);

	Neuron no2;
	no2.appendWeight(1.12);
	no2.appendWeight(0.00);
	no2.appendWeight(1.5);
	no2.setBias(-0.2);

	Layer lo;
	lo.appendNeuron(no1);
	lo.appendNeuron(no2);

	QList<double> output_o = lo(output_1);
	qDebug() << "output layer: " << output_o;

	double out_o1 = HTAN(out_11*0.75 + out_12*-0.25 + out_13*0.33 + 0.00);
	double out_o2 = HTAN(out_11*1.12 + out_12*0.00 + out_13*1.5 - 0.2);

	QCOMPARE(output_o[0], out_o1);
	QCOMPARE(output_o[1], out_o2);

	Network n;
	n.appendLayer(li);
	n.appendLayer(l1);
	n.appendLayer(lo);

	QList<double> output_n = n(input);
	qDebug() << "network output:" << output_n;
	QCOMPARE(output_n, output_o);
}

void Test::networkToString(void){

}

void Test::networkFromString(void){

}

}




















