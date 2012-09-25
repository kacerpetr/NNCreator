#ifndef NEURONNETWORKTEST_H
#define NEURONNETWORKTEST_H

/*
 * This file is part of neuron network implementation.
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

#include <QTextStream>
#include <QString>
#include <QtTest/QtTest>
#include <QDebug>
#include <QList>

#include "Network.h"


/**
 * NeuronNetwork namespace contains data structure that represents multilayer neuron network.
 */
namespace NeuralNetwork{

#define ROUND6(x) ((int)((x)*1E6))/1.0E6
#define HTAN(x) ((1 - pow(M_E,-(x))) / (1 + pow(M_E,-(x))));

class Test : public QObject{
	Q_OBJECT
	private slots:
		void neuronOutput(void);
		void neuronToString(void);
		void neuronFromString(void);

		void inputLayerOutput(void);
		void innerLayerOutput(void);
		void layerToString(void);
		void layerFromString(void);

		void networkOutput(void);
		void networkToString(void);
		void networkFromString(void);
};

}

#endif // NEURONNETWORKTEST_H
