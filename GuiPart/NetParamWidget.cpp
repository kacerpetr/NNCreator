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

#include "NetParamWidget.h"
#include "ui_NetParamWidget.h"
#include <QDebug>

namespace Application{

/**
 * Class constructor.
 */
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

/**
 * Class destructor.
 */
NetParamWidget::~NetParamWidget(){
    delete ui;
}

/**
 * Sets given model to edit widget.
 */
void NetParamWidget::setModel(TopologyEditModel* model){
    mdl = model;
    if(mdl != NULL){
        bool saved = mdl->isSaved();
        setNetStats();
        setRandGenParams();
        setTrFcnBox();
        ui->networkNameLabel->setText(mdl->name());
        connect(
            model, SIGNAL(changed(ChangeType)),
            this, SLOT(modelChanged(ChangeType)),
            Qt::UniqueConnection
        );
        mdl->setSaved(saved);
    }
}

/**
 * Returns true if widget has some model.
 */
bool NetParamWidget::hasModel(){
    return mdl != NULL;
}

/**
 * Called when model is changed.
 * @param type type of model change
 */
void NetParamWidget::modelChanged(ChangeType type){
    if(type == TopologyChange) setNetStats();
    else if(type == NetParamChange) setRandGenParams();
    else if(type == TrFcnChange) setTrFcnBox();
    else if(type == ModelRenamed) ui->networkNameLabel->setText(mdl->name());
}

/**
 * Sets network stat values to their gui items.
 */
void NetParamWidget::setNetStats(){
    if(mdl == NULL) return;
    ui->inputsEdit->setText(QString::number(mdl->inputCount()));
    ui->outputsEdit->setText(QString::number(mdl->outputCount()));
    ui->layersEdit->setText(QString::number(mdl->layerCount()+1));
    ui->neuronsEdit->setText(QString::number(mdl->neuronCount()));
    ui->weightsEdit->setText(QString::number(mdl->weightCount()));
}

/**
 * Sets randomizer setting values to gui items.
 */
void NetParamWidget::setRandGenParams(){
    if(mdl == NULL) return;
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

/**
 * Sets model values to gui items.
 */
void NetParamWidget::setTrFcnBox(){
    if(mdl == NULL) return;
    if(mdl->transferFunction() == UnarySigmoid)
        ui->trFcnBox->setCurrentIndex(0);
    else if(mdl->transferFunction() == BinarySigmoid)
        ui->trFcnBox->setCurrentIndex(1);
}

/**
 * Randomizes weight values of all neurons in selected network.
 */
void NetParamWidget::randomizeWeights(){
    mdl->randomizeWeights();
}

/**
 * Randomizes bias values of all neurons in selected network.
 */
void NetParamWidget::randomizeBias(){
    mdl->randomizeBiases();
}

/**
 * Randomizes weight slope of all neurons in selected network.
 */
void NetParamWidget::randomizeSlope(){
    mdl->randomizeSlopes();
}

/**
 * Sets bias seed value.
 */
void NetParamWidget::setBiasSeed(int val){
    mdl->setBiasSeed(val);
}

/**
 * Sets minimal random bias value.
 */
void NetParamWidget::setBiasMin(double val){
    mdl->setBiasMin(val);
}

/**
 * Sets maximal random bias value.
 */
void NetParamWidget::setBiasMax(double val){
    mdl->setBiasMax(val);
}

/**
 * Sets weight seed value.
 */
void NetParamWidget::setWgSeed(int val){
    mdl->setWeightSeed(val);
}

/**
 * Sets minimal random weight value.
 */
void NetParamWidget::setWgMin(double val){
    mdl->setWeightMin(val);
}

/**
 * Sets maximal random weight value.
 */
void NetParamWidget::setWgMax(double val){
    mdl->setWeightMax(val);
}

/**
 * Sets slope seed value.
 */
void NetParamWidget::setSlopeSeed(int val){
    mdl->setSlopeSeed(val);
}

/**
 * Sets minimal random slope value.
 */
void NetParamWidget::setSlopeMin(double val){
    mdl->setSlopeMin(val);
}

/**
 * Sets maximal random slope value.
 */
void NetParamWidget::setSlopeMax(double val){
    mdl->setSlopeMax(val);
}

/**
 * Sets transfer function of neural network neurons.
 */
void NetParamWidget::trFcnSelected(int index){
    if(index == 0) mdl->setTransferFunction(UnarySigmoid);
    else if(index == 1) mdl->setTransferFunction(BinarySigmoid);
    mdl->modelChanged(TrFcnChange);
}

}
