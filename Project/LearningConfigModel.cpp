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

#include "LearningConfigModel.h"
#include "Parser/LrnConfMdlParser.h"
#include "TopologyEditModel.h"
#include "DatasetEditModel.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

/**
 * Class constructor.
 */
LearningConfigModel::LearningConfigModel() :
	BaseModel(LearningConfig),
	maxIterV(25000),
	maxErrV(0.001),
    maxTimeV(15000),
	lrnCoefV(0.5),
    updateIntervalV(1),
	plt(NULL)
{
	plt = new Plot1D();
    plt->setModel(this);
    plt->setLabelX(tr("Iteration"));
    plt->setLabelY(tr("Output error"));
}

/**
 * Class destructor.
 */
LearningConfigModel::~LearningConfigModel(){
    //delete plt;
}

/**
 * Saves model to file.
 */
void LearningConfigModel::save(){
	LrnConfMdlParser& parser = LrnConfMdlParser::get();
	setSaved(parser.save(this));
}

/**
 * Initializes and starts learning.
 */
void LearningConfigModel::startLearning(){
	BaseModel* setMdlBase = selectedDataset();
	BaseModel* netMdlBase = selectedNetwork();
	Q_ASSERT(setMdlBase != NULL && netMdlBase != NULL);

	setSaved(false);

	DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
	TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

    netMdl->setSaved(false);

	BpAlgSt* alg = new BpAlgSt();
	alg->setNetwork(netMdl);
	alg->setDataset(setMdl);
	alg->setAlpha(lrnCoefV);
	alg->setStopError(maxErrV);
	alg->setStopIteration(maxIterV);
    alg->setStopTime(maxTimeV);
	alg->setUpdateInterval(updateIntervalV);

    connect(alg, SIGNAL(started()), this, SLOT(lrnStarted()));
    connect(alg, SIGNAL(update(int,long,double)), this, SLOT(lrnUpdate(int,long,double)));
    connect(alg, SIGNAL(stoped()), this, SLOT(lrnStoped()));

	eng.setAlgorithm(alg);
    prevIter = plt->maxX();
	eng.startThread();
}

/**
 * Executes one step of learning.
 */
void LearningConfigModel::stepLearning(){
    BaseModel* setMdlBase = selectedDataset();
    BaseModel* netMdlBase = selectedNetwork();
    Q_ASSERT(setMdlBase != NULL && netMdlBase != NULL);

    setSaved(false);

    DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
    TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

    netMdl->setSaved(false);

    BpAlgSt* alg = new BpAlgSt();
    alg->setNetwork(netMdl);
    alg->setDataset(setMdl);
    alg->setAlpha(lrnCoefV);
    alg->setStopError(0);
    alg->setStopIteration(1);
    alg->setStopTime(maxTimeV);
    alg->setUpdateInterval(1);

    connect(alg, SIGNAL(started()), this, SLOT(lrnStarted()));
    connect(alg, SIGNAL(update(int,long,double)), this, SLOT(lrnUpdate(int,long,double)));
    connect(alg, SIGNAL(stoped()), this, SLOT(lrnStoped()));

    eng.setAlgorithm(alg);
    prevIter = plt->maxX();
    eng.startThread();
}


/**
 * Stops learning.
 */
void LearningConfigModel::stopLearning(){
	eng.stopThread();
}

/**
 * Sets stop iteration.
 */
void LearningConfigModel::setMaxIter(int value){
	maxIterV = value;
	setSaved(false);
}

/**
 * Sets stop error.
 */
void LearningConfigModel::setMaxErr(double value){
	maxErrV = value;
	setSaved(false);
}

/**
 * Sets stop time.
 */
void LearningConfigModel::setMaxTime(int value){
	maxTimeV = value;
	setSaved(false);
}

/**
 * Returns stop iteration.
 */
int LearningConfigModel::maxIter(){
	return maxIterV;
}

/**
 * Returns stop error.
 */
double LearningConfigModel::maxErr(){
	return maxErrV;
}

/**
 * Returns stop time.
 */
int LearningConfigModel::maxTime(){
	return maxTimeV;
}

/**
 * Sets learning coeficient.
 */
void LearningConfigModel::setLrnCoef(double value){
	lrnCoefV = value;
	setSaved(false);
}

/**
 * Returns learning coeficient.
 */
double LearningConfigModel::lrnCoef(){
	return lrnCoefV;
}

/**
 * Sets update interval in iterations.
 */
void LearningConfigModel::setUpdateInterval(int value){
	updateIntervalV = value;
	setSaved(false);
}

/**
 * Returns update interval in iterations.
 */
int LearningConfigModel::updateInterval(){
	return updateIntervalV;
}

/**
 * Fills plot with data from string.
 */
void LearningConfigModel::fillPlot(QString data){
    plt->fromString(data);
    plt->setMinAutorangeO(0.0);
}

/**
 * Returns plot pointer.
 */
Plot1D* LearningConfigModel::plot(){
	return plt;
}

/**
 * Called when learning started.
 */
void LearningConfigModel::lrnStarted(){
    plt->repaint();
	emit started();
}

/**
 * Called when learning stoped.
 */
void LearningConfigModel::lrnStoped(){
    plt->repaint();
    emit stoped();
}

/**
 * Adds point to plot and redraws it.
 */
void LearningConfigModel::lrnUpdate(int iteration, long time, double error){
    plt->addPoint(prevIter + iteration, error);
    if(iteration%200 == 0){
        plt->setMinAutorangeO(0.0);
        plt->repaint();
    }
    emit update(prevIter + iteration, time, error);
}

/**
 * Adds other plot to this plot.
 */
void LearningConfigModel::addPlot(QString name){
    BaseModel* model = prj->getModel(name, LearningConfig);
    Plot1D* plot = NULL;
    if(model != NULL){
        plot = ((LearningConfigModel*)model)->plot();
    }
    if(plot != NULL) plt->addPlot(plot);
    plt->setMinAutorangeO(0.0);
}

/**
 * Randomizes weights, biases and slopes of selected network.
 */
void LearningConfigModel::reinitNetwork(){
    BaseModel* mdl = selectedNetwork();
    TopologyEditModel* net = (TopologyEditModel*)mdl;
    net->randomizeBiases();
    net->randomizeSlopes();
    net->randomizeWeights();
}

}
