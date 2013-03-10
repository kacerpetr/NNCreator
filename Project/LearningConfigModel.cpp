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
	maxTimeV(10),
	lrnCoefV(0.5),
	updateIntervalV(20),
	plt(NULL)
{
	plt = new Plot1D();
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

	DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
	TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

	BpAlgSt* alg = new BpAlgSt();
	alg->setNetwork(netMdl);
	alg->setDataset(setMdl);
	alg->setAlpha(lrnCoefV);
	alg->setStopError(maxErrV);
	alg->setStopIteration(maxIterV);
	alg->setStopTime(maxIterV);
	alg->setUpdateInterval(updateIntervalV);

	connect(alg, SIGNAL(update(int,long,double)), this, SLOT(lrnUpdate(int,long,double)));
	connect(alg, SIGNAL(stoped(int,long,double)), this, SLOT(lrnStoped(int,long,double)));

	eng.setAlgorithm(alg);
	eng.startThread();
}

void LearningConfigModel::stopLearning(){
	eng.stopThread();
}

void LearningConfigModel::setMaxIter(int value){
	maxIterV = value;
}

void LearningConfigModel::setMaxErr(double value){
	maxErrV = value;
}

void LearningConfigModel::setMaxTime(int value){
	maxTimeV = value;
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
}

double LearningConfigModel::lrnCoef(){
	return lrnCoefV;
}

void LearningConfigModel::setUpdateInterval(int value){
	updateIntervalV = value;
}

int LearningConfigModel::updateInterval(){
	return updateIntervalV;
}

Plot1D* LearningConfigModel::plot(){
	return plt;
}

void LearningConfigModel::lrnStarted(){
	emit started();
}

void LearningConfigModel::lrnStoped(int iteration, long time, double error){
	plt->addPoint(iteration, error);
	emit stoped(iteration, time, error);
}

void LearningConfigModel::lrnUpdate(int iteration, long time, double error){
	plt->addPoint(iteration, error);
	emit update(iteration, time, error);
}

}
