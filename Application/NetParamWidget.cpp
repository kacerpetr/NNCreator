#include "NetParamWidget.h"
#include "ui_NetParamWidget.h"

namespace Application{
	NetParamWidget::NetParamWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NetParamWidget){
		ui->setupUi(this);
		connect(ui->randWeightButton, SIGNAL(pressed()), this, SLOT(randomizeWeights()));
		connect(ui->randBiasButton, SIGNAL(pressed()), this, SLOT(randomizeBias()));
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
		mdl->randomizeBias();
	}
}
