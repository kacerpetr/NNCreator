#include "NetParamWidget.h"
#include "ui_NetParamWidget.h"

namespace Application{
	NetParamWidget::NetParamWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NetParamWidget){
		ui->setupUi(this);
		connect(ui->randWeightButton, SIGNAL(pressed()), this, SLOT(randomizeWeights()));
		connect(ui->randBiasButton, SIGNAL(pressed()), this, SLOT(randomizeBias()));
		connect(ui->biasSeedBox, SIGNAL(valueChanged(int)), this, SLOT(setBiasSeed(int)));
		connect(ui->biasMinBox, SIGNAL(valueChanged(double)), this, SLOT(setBiasMin(double)));
		connect(ui->biasMaxBox, SIGNAL(valueChanged(double)), this, SLOT(setBiasMax(double)));
		connect(ui->weightSeedBox, SIGNAL(valueChanged(int)), this, SLOT(setWgSeed(int)));
		connect(ui->weightMinBox, SIGNAL(valueChanged(double)), this, SLOT(setWgMin(double)));
		connect(ui->weightMaxBox, SIGNAL(valueChanged(double)), this, SLOT(setWgMax(double)));
	}

	NetParamWidget::~NetParamWidget(){
		delete ui;
	}

	void NetParamWidget::setModel(TopologyEditModel* model){
		mdl = model;
		if(mdl != NULL){
			ui->weightSeedBox->setValue(mdl->weightSeed());
			ui->weightMinBox->setValue(mdl->weightMin());
			ui->weightMaxBox->setValue(mdl->weightMax());
			ui->biasSeedBox->setValue(mdl->biasSeed());
			ui->biasMinBox->setValue(mdl->biasMin());
			ui->biasMaxBox->setValue(mdl->biasMax());
			ui->inputsEdit->setText(QString::number(mdl->inputCount()));
			ui->outputsEdit->setText(QString::number(mdl->outputCount()));
			ui->layersEdit->setText(QString::number(mdl->layerCount()+1));
			ui->neuronsEdit->setText(QString::number(mdl->neuronCount()));
			ui->weightsEdit->setText(QString::number(mdl->weightCount()));
		}
	}

	bool NetParamWidget::hasModel(){
		return mdl != NULL;
	}

	void NetParamWidget::randomizeWeights(){
		mdl->randomizeWeights();
	}

	void NetParamWidget::randomizeBias(){
		mdl->randomizeBiases();
	}

	void NetParamWidget::setBiasSeed(int val){
		mdl->setBiasSeed(val);
	}

	void NetParamWidget::setBiasMin(double val){
		mdl->setBiasMin(val);
	}

	void NetParamWidget::setBiasMax(double val){
		mdl->setBiasMax(val);
	}

	void NetParamWidget::setWgSeed(int val){
		mdl->setWeightSeed(val);
	}

	void NetParamWidget::setWgMin(double val){
		mdl->setBiasMin(val);
	}

	void NetParamWidget::setWgMax(double val){
		mdl->setBiasMax(val);
	}

}
