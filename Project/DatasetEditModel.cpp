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

#include "DatasetEditModel.h"
#include "Parser/DatasetMdlParser.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

/**
 * DatasetEditModel class constructor.
 */
DatasetEditModel::DatasetEditModel() : BaseModel(DatasetEdit), viewMdl(NULL){
	viewMdl = new DatasetViewModel(this, this);
	connect(viewMdl, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged()));
	setPatternCount(1);
	setInputCount(1);
	setOutputCount(1);
}

DatasetEditModel::DatasetEditModel(DatasetEditModel* mdl):
  BaseModel(DatasetEdit),
  Dataset(*((Dataset*)mdl)),
  viewMdl(NULL)
{
    viewMdl = new DatasetViewModel(this, this);
    connect(viewMdl, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChanged()));
}

/**
 * Class destructor.
 */
DatasetEditModel::~DatasetEditModel(){
	delete viewMdl;
}

/**
 * Saves model to file.
 */
void DatasetEditModel::save(){
	reduceToMinSize();
	DatasetMdlParser& parser = DatasetMdlParser::get();
	setSaved(parser.save(this));
	viewMdl->emitLayoutChanged();
}

/**
 * Sets pattern count of dataset.
 */
void DatasetEditModel::setPatternCount(int count){
	setMinPaternCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Sets output count of dataset.
 */
void DatasetEditModel::setInputCount(int count){
	setMinInputCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Sets input count of dataset.
 */
void DatasetEditModel::setOutputCount(int count){
	setMinOutputCount(count);
    viewMdl->emitLayoutChanged();
}

/**
 * Returns dataset table view model.
 */
DatasetViewModel* DatasetEditModel::viewModel(){
	return viewMdl;
}

/**
 * Sets model as unsaved when data is changed.
 */
void DatasetEditModel::dataChanged(){
	setSaved(false);
}

}
