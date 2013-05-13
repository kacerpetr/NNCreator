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

#ifndef DATASETEDITMODEL_H
#define DATASETEDITMODEL_H

#include "BaseModel.h"
#include "DatasetViewModel.h"
using namespace NeuralNetwork;

/**
 * Contains data models and classes related with project.
 */
namespace ProjectData{

/**
 * Data model for editor of training and testing datasets.
 */
class DatasetEditModel : public BaseModel, public Dataset{
	Q_OBJECT

	public:
		DatasetEditModel();
        DatasetEditModel(DatasetEditModel* mdl);
		~DatasetEditModel();
		virtual void save();
		void setPatternCount(int count);
		void setInputCount(int count);
		void setOutputCount(int count);
		DatasetViewModel* viewModel();

	private slots:
		void dataChanged();

	private:
		/** Dataset table view pointer. */
		DatasetViewModel* viewMdl;
};

}

#endif // TRAININGPATTERNMODEL_H
