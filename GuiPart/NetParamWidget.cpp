#include "NetParamWidget.h"
#include "ui_NetParamWidget.h"
#include <QDebug>

namespace Application{

NetParamWidget::NetParamWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NetParamWidget){
    ui->setupUi(this);
    connect(ui->randWeightButton, SIGNAL(pressed()), this, SLOT(randomizeWeights()));
    connect(ui->randBiasButton, SIGNAL(pressed()), this, SLOT(randomizeBias()));
    connect(ui->randSlopeButton, SIGNAL(pressed()), this, SLOT(randomizeSlope()));
    connect(ui->biasSeedBox, SIGNAL(valueChanged(int)), this, SLOT(setBiasSeed(int)));
    connect(ui->biasMinBox, SIGNAL(valueChanged(double)), this, SLOT(setBiasMin(double)));
    connect(ui->biasMaxBox, SIGNAL(valueChanged(double)), this, SLOT(setBiasMax(double)));
    connect(ui->weightSeedBox, SIGNAL(valueChanged(int)), this, SLOT(setWgSeed(int)));
    connect(ui->weightMinBox, SIGNAL(valueChanged(double)), this, SLOT(setWgMin(double)));
    connect(ui->weightMaxBox, SIGNAL(valueChanged(double)), this, SLOT(setWgMax(double)));
    connect(ui->slopeSeedBox, SIGNAL(valueChanged(int)), this, SLOT(setSlopeSeed(int)));
    connect(ui->slopeMinBox, SIGNAL(valueChanged(double)), this, SLOT(setSlopeMin(double)));
    connect(ui->slopeMaxBox, SIGNAL(valueChanged(double)), this, SLOT(setSlopeMax(double)));
    connect(ui->trFcnBox, SIGNAL(currentIndexChanged(int)), this, SLOT(trFcnSelected(int)));
}

NetParamWidget::~NetParamWidget(){
    delete ui;
}

void NetParamWidget::setModel(TopologyEditModel* model){
    mdl = model;
    if(mdl != NULL){
        bool saved = mdl->isSaved();
        setNetStats();
        setRandGenParams();
        setTrFcnBox();
        connect(
            model, SIGNAL(changed(ChangeType)),
            this, SLOT(modelChanged(ChangeType)),
            Qt::UniqueConnection
        );
        mdl->setSaved(saved);
    }
}

bool NetParamWidget::hasModel(){
    return mdl != NULL;
}

void NetParamWidget::modelChanged(ChangeType type){
    if(type == TopologyChange) setNetStats();
    else if(type == NetParamChange) setRandGenParams();
    else if(type == TrFcnChange) setTrFcnBox();
}

void NetParamWidget::setNetStats(){
    ui->inputsEdit->setText(QString::number(mdl->inputCount()));
    ui->outputsEdit->setText(QString::number(mdl->outputCount()));
    ui->layersEdit->setText(QString::number(mdl->layerCount()+1));
    ui->neuronsEdit->setText(QString::number(mdl->neuronCount()));
    ui->weightsEdit->setText(QString::number(mdl->weightCount()));
}

void NetParamWidget::setRandGenParams(){
    ui->weightSeedBox->setValue(mdl->weightSeed());
    ui->weightMinBox->setValue(mdl->weightMin());
    ui->weightMaxBox->setValue(mdl->weightMax());
    ui->biasSeedBox->setValue(mdl->biasSeed());
    ui->biasMinBox->setValue(mdl->biasMin());
    ui->biasMaxBox->setValue(mdl->biasMax());
    ui->slopeSeedBox->setValue(mdl->slopeSeed());
    ui->slopeMinBox->setValue(mdl->slopeMin());
    ui->slopeMaxBox->setValue(mdl->slopeMax());
}

void NetParamWidget::setTrFcnBox(){
    if(mdl->transferFunction() == UnarySigmoid)
        ui->trFcnBox->setCurrentIndex(0);
    else if(mdl->transferFunction() == BinarySigmoid)
        ui->trFcnBox->setCurrentIndex(1);
}

void NetParamWidget::randomizeWeights(){
    mdl->randomizeWeights();
}

void NetParamWidget::randomizeBias(){
    mdl->randomizeBiases();
}

void NetParamWidget::randomizeSlope(){
    mdl->randomizeSlopes();
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
    mdl->setWeightMin(val);
}

void NetParamWidget::setWgMax(double val){
    mdl->setWeightMax(val);
}

void NetParamWidget::setSlopeSeed(int val){
    mdl->setSlopeSeed(val);
}

void NetParamWidget::setSlopeMin(double val){
    mdl->setSlopeMin(val);
}

void NetParamWidget::setSlopeMax(double val){
    mdl->setSlopeMax(val);
}

void NetParamWidget::trFcnSelected(int index){
    if(index == 0) mdl->setTransferFunction(UnarySigmoid);
    else if(index == 1) mdl->setTransferFunction(BinarySigmoid);
    mdl->modelChanged(TrFcnChange);
}

}
