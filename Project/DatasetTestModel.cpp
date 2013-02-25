#include "DatasetTestModel.h"
#include "Parser/DatasetTestMdlParser.h"
#include <QElapsedTimer>
#include <QDebug>

using namespace Parser;

namespace ProjectData {

DatasetTestModel::DatasetTestModel() : BaseModel(DatasetTest), prj(NULL){}

void DatasetTestModel::setProject(Project* prj){
	this->prj = prj;
}

QStringList DatasetTestModel::networkList(){
	Q_ASSERT(prj != NULL);

	QStringList lst;
	for(int i = 0; i < prj->count(TopologyEdit); i++){
		QString mdlName = prj->getModelName(i, TopologyEdit);
		if(!mdlName.isEmpty()) lst.append(mdlName);
	}
	return lst;
}

QStringList DatasetTestModel::datasetList(QString name){
	Q_ASSERT(prj != NULL);

	QList<DatasetEditModel*> sets = prj->getRelatedDataset(name);
	QStringList lst;
	for(int i = 0; i < sets.length(); i++){
		lst.append(sets[i]->name());
	}
	return lst;
}

QString DatasetTestModel::networkName(){
	return mlNet;
}

QString DatasetTestModel::datasetName(){
	return trSet;
}

void DatasetTestModel::setNetworkName(QString name){
	mlNet = name;
}

void DatasetTestModel::setDatasetName(QString name){
	trSet = name;
}

QList< QList<double> > DatasetTestModel::runTest(long& time, double& err){
	Q_ASSERT(!mlNet.isEmpty() && !trSet.isEmpty());
	Q_ASSERT(prj != NULL);

	BaseModel* setMdlBase = prj->getModel(trSet, DatasetEdit);
	BaseModel* netMdlBase = prj->getModel(mlNet, TopologyEdit);
	Q_ASSERT(setMdlBase != NULL && netMdlBase != NULL);

	DatasetEditModel* setMdl = (DatasetEditModel*)setMdlBase;
	TopologyEditModel* netMdl = (TopologyEditModel*)netMdlBase;

	QList< QList<double> > res;

	time = 0;
	err = 0;
	QElapsedTimer timer;
	for(int i = 0; i < setMdl->minPatternCount(); i++){
		timer.restart();
		QList<double> out = netMdl->network()->output(setMdl->inputVector(i));

		time += timer.nsecsElapsed();

		res.append(QList<double>());

		double ptErr = 0;

		for(int j = 0; j < out.length(); j++){
			double outErr = setMdl->output(i,j) - out[j];
			res[i].append(outErr);
			ptErr += outErr * outErr;
		}

		res[i].prepend(ptErr*0.5);
		err += ptErr*0.5;

	}
	time = time / setMdl->patternCount();

	return res;
}

DatasetEditModel* DatasetTestModel::dataset(){
	Q_ASSERT(!trSet.isEmpty());
	Q_ASSERT(prj != NULL);

	BaseModel* setMdlBase = prj->getModel(trSet, DatasetEdit);
	Q_ASSERT(setMdlBase != NULL);

	return (DatasetEditModel*)setMdlBase;
}

void DatasetTestModel::save(){
	DatasetTestMdlParser& parser = DatasetTestMdlParser::get();
	parser.save(this);
	setSaved(true);
}

void DatasetTestModel::setOpened(bool state){
	mdlOpened = state;
	emit opened(this);
}

void DatasetTestModel::setSaved(bool state){
	mdlSaved = state;
	emit saved(this);
}

}
