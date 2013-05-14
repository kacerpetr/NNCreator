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

#ifndef TOPOLOGYEDITMODEL_H
#define TOPOLOGYEDITMODEL_H

#include <QString>
#include "NeuralNetwork/MlnNetSt.h"
#include "BaseModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Data model of neural network topology editor.
 */
class TopologyEditModel : public BaseModel, public MlnNetSt{
	Q_OBJECT

	public:
		TopologyEditModel();
		virtual ~TopologyEditModel();
		virtual void save();
		void randomizeWeights();
		void randomizeBiases();
        void randomizeSlopes();
		void setWeightSeed(int value);
		int weightSeed() const;
		void setWeightMin(double value);
		double weightMin() const;
		void setWeightMax(double value);
		double weightMax() const;
		void setBiasSeed(int value);
		int biasSeed() const;
		void setBiasMin(double value);
		double biasMin() const;
		void setBiasMax(double value);
		double biasMax() const;
        void setSlopeSeed(int value);
        int slopeSeed() const;
        void setSlopeMin(double value);
        double slopeMin() const;
        void setSlopeMax(double value);
        double slopeMax() const;
		void setSelectedLayer(int layer);
		int selectedLayer() const;

    private:
		/** Seed for random weight generation. */
		double wgSeed;
		/** Minimal random weight value. */
		double wgMin;
		/** Maximal random weigth value. */
		double wgMax;
		/** Seed for random bias generation. */
		double bsSeed;
		/** Minimal random bias value. */
		double bsMin;
		/** Maximal random bias value. */
		double bsMax;
        /** Seed for random slope generation. */
        double slpSeed;
        /** Minimal random slope value. */
        double slpMin;
        /** Maximal random slope value. */
        double slpMax;
		/** Selected layer */
		int layer;
};

}
#endif // TOPOLOGYEDITMODEL_H
