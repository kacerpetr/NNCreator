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

#include "DatasetTestModel.h"
#include "Parser/DatasetTestMdlParser.h"
#include "TopologyEditModel.h"
#include <QElapsedTimer>
#include <QDebug>

using namespace Parser;

namespace ProjectData {

/**
 * Class constructor.
 */
DatasetTestModel::DatasetTestModel() : BaseModel(DatasetTest){}

/**
 * Runs test and returns result table.
 */
QList< QList<double> > DatasetTestModel::runTest(long& time, double& err){
	BaseModel* setMdlBase = selectedDataset();
	BaseModel* netMdlBase = selectedNetwork();
	Q_ASSERT(setMdlBase != NULL && netMdlBase != NULL);

	setSaved(false);

	DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
	TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

	QList< QList<double> > res;

	time = 0;
	err = 0;
	QElapsedTimer timer;
	for(int i = 0; i < setMdl->minPatternCount(); i++){
		timer.restart();
		QList<double> out = netMdl->output(setMdl->inputVector(i));

		time += timer.nsecsElapsed();

		res.append(QList<double>());

		double ptErr = 0;

		for(int j = 0; j < out.length(); j++){
			double outErr = setMdl->output(i,j) - out[j];
			res[i].append(out[j]);
			res[i].append(outErr);
			ptErr += outErr * outErr;
		}

		res[i].prepend(ptErr*0.5);
		err += ptErr*0.5;

	}
	time = time / setMdl->patternCount();

	return res;
}

/**
 * Saves model to file.
 */
void DatasetTestModel::save(){
	DatasetTestMdlParser& parser = DatasetTestMdlParser::get();
	setSaved(parser.save(this));
}

}
