#include "LearningConfigModel.h"
#include "Parser/LrnConfMdlParser.h"
#include "TopologyEditModel.h"
#include "DatasetEditModel.h"
#include <QDebug>
using namespace Parser;

namespace ProjectData{

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
    plt->setLabelX("Iteration");
    plt->setLabelY("Output error");
}

LearningConfigModel::~LearningConfigModel(){
	delete plt;
}

void LearningConfigModel::save(){
	LrnConfMdlParser& parser = LrnConfMdlParser::get();
	setSaved(parser.save(this));
}

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

void LearningConfigModel::stopLearning(){
	eng.stopThread();
}

void LearningConfigModel::setMaxIter(int value){
	maxIterV = value;
	setSaved(false);
}

void LearningConfigModel::setMaxErr(double value){
	maxErrV = value;
	setSaved(false);
}

void LearningConfigModel::setMaxTime(int value){
	maxTimeV = value;
	setSaved(false);
}

int LearningConfigModel::maxIter(){
	return maxIterV;
}

double LearningConfigModel::maxErr(){
	return maxErrV;
}

int LearningConfigModel::maxTime(){
	return maxTimeV;
}

void LearningConfigModel::setLrnCoef(double value){
	lrnCoefV = value;
	setSaved(false);
}

double LearningConfigModel::lrnCoef(){
	return lrnCoefV;
}

void LearningConfigModel::setUpdateInterval(int value){
	updateIntervalV = value;
	setSaved(false);
}

int LearningConfigModel::updateInterval(){
	return updateIntervalV;
}

void LearningConfigModel::fillPlot(QString data){
    plt->fromString(data);
}

Plot1D* LearningConfigModel::plot(){
	return plt;
}

void LearningConfigModel::lrnStarted(){
    plt->repaint();
	emit started();
}

void LearningConfigModel::lrnStoped(){
    plt->repaint();
    emit stoped();
}

void LearningConfigModel::lrnUpdate(int iteration, long time, double error){
    plt->addPoint(prevIter + iteration, error);
    if(iteration%200 == 0) plt->repaint();
    emit update(prevIter + iteration, time, error);
}

}
