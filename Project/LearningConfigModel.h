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

#ifndef LEARNINGCONFIGMODEL_H
#define LEARNINGCONFIGMODEL_H

#include <QString>
#include <QStringList>
#include "BaseModel.h"
#include "NeuralNetwork/BpAlgSt.h"
#include "NeuralNetwork/LrnEngine.h"
#include "TopologyEditModel.h"
#include "GuiPart/Plot1D.h"

namespace Application{
    class Plot1D;
}

using namespace Application;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Learning configuration data model class.
 */
class LearningConfigModel : public BaseModel{
	Q_OBJECT

	public:
		LearningConfigModel();
		~LearningConfigModel();
		void startLearning();
        void stepLearning();
		void stopLearning();
		void setMaxIter(int value);
		void setMaxErr(double value);
		void setMaxTime(int value);
		void setLrnCoef(double value);
		void setUpdateInterval(int value);
		int maxIter();
		double maxErr();
		int maxTime();
		double lrnCoef();
		int updateInterval();
        void fillPlot(QString data);
		Plot1D* plot();
		virtual void save();
        void reinitNetwork();

	public slots:
        void lrnStarted();
        void lrnStoped();
		void lrnUpdate(int iteration, long time, double error);
        void addPlot(QString name);

	signals:
        /** Emitted when learning is started. */
		void started();
        /** Emitted when learning is stoped. */
        void stoped();
        /** Emitted every update interval during learning. */
		void update(int iteration, long time, double error);

	private:
        /** Learning error plot. */
		Plot1D* plt;
        /** Learning engine. */
		LrnEngine eng;
        /** Stop iteration. */
		int maxIterV;
        /** Stop error value. */
		double maxErrV;
        /** Stop time in miliseconds. */
		int maxTimeV;
        /** Learning coeficient value. */
		double lrnCoefV;
        /** Learning algorithm emits update signal each interval of iterations. */
		int updateIntervalV;
        /** Iteration after last learning finished. */
        double prevIter;
};

}

#endif // LEARNINGCONFIGMODEL_H
