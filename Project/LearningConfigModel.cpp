#include "LearningConfigModel.h"
#include "Parsers/LrnConfMdlParser.h"
#include "TopologyEditModel.h"
#include <QDebug>
using namespace Parsers;

namespace ProjectData{

LearningConfigModel::LearningConfigModel() : BaseModel(LearningConfig){
	alg = new BpAlgSt();
	connect(alg, SIGNAL(update(int,long,double)), this, SLOT(lrnUpdate(int,long,double)));
	connect(alg, SIGNAL(stoped(int,long,double)), this, SLOT(lrnStoped(int,long,double)));
}

void LearningConfigModel::setProject(Project* prj){
	this->prj = prj;
}

LearningConfigModel::~LearningConfigModel(){
	delete alg;
}

QStringList LearningConfigModel::networkList(){
	Q_ASSERT(prj != NULL);

	QStringList lst;
	for(int i = 0; i < prj->count(TopologyEdit); i++){
		lst.append(prj->getModelName(i, TopologyEdit));
	}
	return lst;
}

QStringList LearningConfigModel::datasetList(QString name){
	Q_ASSERT(prj != NULL);

	QList<DatasetEditModel*> sets = prj->getRelatedDataset(name);
	QStringList lst;

	for(int i = 0; i < sets.length(); i++){
		lst.append(sets[i]->name());
	}

	return lst;
}

QString LearningConfigModel::networkName(){
	Q_ASSERT(prj != NULL);
	return mlNet;
}

QString LearningConfigModel::datasetName(){
	Q_ASSERT(prj != NULL);
	return trSet;
}

void LearningConfigModel::setNetworkName(QString name){
	Q_ASSERT(prj != NULL);
	mlNet = name;
}

void LearningConfigModel::setDatasetName(QString name){
	Q_ASSERT(prj != NULL);
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

void LearningConfigModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void LearningConfigModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

void LearningConfigModel::startLearning(){
	BaseModel* setMdlBase = prj->getModel(trSet, DatasetEdit);
	BaseModel* netMdlBase = prj->getModel(mlNet, TopologyEdit);
	Q_ASSERT(setMdlBase != NULL && netMdlBase != NULL);

	DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
	TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

	qDebug() << setMdl->getDataset()->inputCount() << netMdl->inputCount();

	alg->setNetwork(netMdl->network());
	alg->setDataset(setMdl->getDataset());

	eng.setAlgorithm(alg);
	eng.startThread();
}

void LearningConfigModel::stopLearning(){
	eng.stopThread();
}

AbstractLrnAlg* LearningConfigModel::lrnAlg(){
	return alg;
}

void LearningConfigModel::setMaxIter(int value){
	alg->setStopIteration(value);
}

void LearningConfigModel::setMaxErr(double value){
	alg->setStopError(value);
}

void LearningConfigModel::setMaxTime(int value){
	alg->setStopTime(value);
}

int LearningConfigModel::maxIter(){
	return alg->stopTime();
}

double LearningConfigModel::maxErr(){
	return alg->stopError();
}

int LearningConfigModel::maxTime(){
	return alg->stopTime();
}

void LearningConfigModel::setLrnCoef(double value){
	alg->setAlpha(value);
}

double LearningConfigModel::lrnCoef(){
	return alg->alpha();
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
