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
	updateIntervalV(20)
{}

LearningConfigModel::~LearningConfigModel(){}

QStringList LearningConfigModel::networkList(){
	Q_ASSERT(prj != NULL);

	QStringList lst;
	for(int i = 0; i < prj->count(TopologyEdit); i++){
		QString mdlName = prj->getModelName(i, TopologyEdit);
		if(!mdlName.isEmpty()) lst.append(mdlName);
	}
	return lst;
}

QStringList LearningConfigModel::datasetList(QString name){
	Q_ASSERT(prj != NULL);

	QList<BaseModel*> sets = prj->getRelatedDataset(name);
	QStringList lst;
	for(int i = 0; i < sets.length(); i++){
		lst.append(sets[i]->name());
	}
	return lst;
}

QString LearningConfigModel::networkName(){
	return mlNet;
}

QString LearningConfigModel::datasetName(){
	return trSet;
}

void LearningConfigModel::setNetworkName(QString name){
	mlNet = name;
}

void LearningConfigModel::setDatasetName(QString name){
	trSet = name;
}

TopologyEditModel* LearningConfigModel::topologyEditModel(QString name){
	BaseModel* mdl = prj->getModel(name, TopologyEdit);
	return (TopologyEditModel*)mdl;
}

void LearningConfigModel::save(){
	LrnConfMdlParser& parser = LrnConfMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void LearningConfigModel::startLearning(){
	Q_ASSERT(prj != NULL);

	BaseModel* setMdlBase = prj->getModel(trSet, DatasetEdit);
	BaseModel* netMdlBase = prj->getModel(mlNet, TopologyEdit);
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

void LearningConfigModel::lrnStarted(){
	emit started();
}

void LearningConfigModel::lrnStoped(int iteration, long time, double error){
	emit stoped(iteration, time, error);
}

void LearningConfigModel::lrnUpdate(int iteration, long time, double error){
	emit update(iteration, time, error);
}

}
