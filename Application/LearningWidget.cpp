#include "LearningWidget.h"
#include "ui_LearningWidget.h"

namespace Application{

LearningWidget::LearningWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LearningWidget), model(NULL){
	ui->setupUi(this);

	npw = new NetParamWidget(this);
	ui->splitterH->addWidget(npw);

	graph = new LrnGraphWidget(this);
	ui->graphFrame->layout()->addWidget(graph);

	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
	connect(ui->startBtn, SIGNAL(pressed()), this, SLOT(startLearning()));
	connect(ui->stopBtn, SIGNAL(pressed()), this, SLOT(stopLearning()));
	connect(ui->datasetBox, SIGNAL(activated(QString)), this, SLOT(datasetSelected(QString)));
	connect(ui->networkBox, SIGNAL(activated(QString)), this, SLOT(networkSelected(QString)));
	connect(ui->lrnCoefBox, SIGNAL(valueChanged(double)), this, SLOT(lrnCoefChanged(double)));
	connect(ui->maxErrBox, SIGNAL(valueChanged(double)), this, SLOT(maxErrChanged(double)));
	connect(ui->maxIterBox, SIGNAL(valueChanged(int)), this, SLOT(maxIterChanged(int)));
}

LearningWidget::~LearningWidget(){
	delete ui;
}

void LearningWidget::setModel(LearningConfigModel* model){
	this->model = model;

	if(model == NULL){
		ui->itemName->setText(QString());
	}
	else{
		ui->itemName->setText(model->name());

		ui->networkBox->clear();
		ui->networkBox->addItem(QString("<Choose neural network>"));

		QStringList nets = model->networkList();
		if(!nets.isEmpty()) ui->networkBox->addItems(nets);

		int index = ui->networkBox->findText(model->networkName());

		ui->datasetBox->clear();
		ui->datasetBox->addItem(QString("<No network selected>"));

		if(index > 0){
			ui->networkBox->setCurrentIndex(index);
			networkSelected(model->networkName());
		}

		ui->maxErrBox->setValue(model->maxErr());
		ui->maxIterBox->setValue(model->maxIter());
		ui->lrnCoefBox->setValue(model->lrnCoef());
		ui->maxTimeBox->setValue(model->maxTime());

		connect(model, SIGNAL(update(int,long,double)), this, SLOT(updateLearning(int,long,double)));
		connect(model, SIGNAL(stoped(int,long,double)), this, SLOT(learningStoped(int,long,double)));
	}
}

bool LearningWidget::hasModel(){
	return model != NULL;
}

void LearningWidget::closeBtnPressed(){
	emit closePressed(model);
}

void LearningWidget::startLearning(){
	model->startLearning();
}

void LearningWidget::stopLearning(){
	model->stopLearning();
}

void LearningWidget::learningStoped(int iteration, long time, double error){
	ui->actErrorEdit->setText(QString::number(error));
	ui->actIterEdit->setText(QString::number(iteration));
	ui->actTimeEdit->setText(QString::number(time));
}

void LearningWidget::updateLearning(int iteration, long time, double error){
	ui->actErrorEdit->setText(QString::number(error));
	ui->actIterEdit->setText(QString::number(iteration));
	ui->actTimeEdit->setText(QString::number(time));
}

void LearningWidget::networkSelected(QString name){
	if(ui->networkBox->currentIndex() < 1){
		model->setNetworkName(QString());
		return;
	}

	ui->datasetBox->clear();
	QStringList list = model->datasetList(name);

	if(list.isEmpty()){
		ui->datasetBox->addItem(QString("<No dataset available for this network>"));
	}else{
		ui->datasetBox->addItem(QString("<Select training dataset>"));
		ui->datasetBox->addItems(list);
		if(!model->datasetName().isEmpty()){
			int index = ui->datasetBox->findText(model->datasetName());
			if(index > 0) ui->datasetBox->setCurrentIndex(index);
		}
	}

	model->setNetworkName(name);

	TopologyEditModel* mdl = model->topologyEditModel(name);
	Q_ASSERT(mdl != NULL);
	npw->setModel(mdl);
}

void LearningWidget::datasetSelected(QString name){
	if(ui->datasetBox->currentIndex() == -1){
		model->setDatasetName(QString());
		return;
	}

	model->setDatasetName(name);
}

void LearningWidget::lrnCoefChanged(double value){
	model->setLrnCoef(value);
}

void LearningWidget::maxIterChanged(int value){
	model->setMaxIter(value);
}

void LearningWidget::maxErrChanged(double value){
	model->setMaxErr(value);
}

void LearningWidget::maxTimeChanged(int value){
	model->setMaxTime(value);
}

}
