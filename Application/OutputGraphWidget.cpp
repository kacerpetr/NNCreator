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

#include "OutputGraphWidget.h"
#include "ui_OutputGraphWidget.h"
#include "GuiPart/Plot1D.h"
#include "Project/DatasetEditModel.h"

namespace Application{

/**
 * Class constructor.
 */
OutputGraphWidget::OutputGraphWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::OutputGraphWidget),
    model(NULL)
{
    //autogenerated stuff
    ui->setupUi(this);

    //connects signals and slots
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
	connect(ui->drawButton, SIGNAL(pressed()), this, SLOT(drawGraph()));
	connect(ui->outputBox, SIGNAL(valueChanged(int)), this, SLOT(outputChanged(int)));
    connect(ui->networkBox, SIGNAL(activated(QString)), this, SLOT(networkSelected(QString)));
    connect(ui->datasetBox, SIGNAL(activated(QString)), this, SLOT(datasetSelected(QString)));
}

/**
 * Class destructor.
 */
OutputGraphWidget::~OutputGraphWidget(){
	delete ui;
}

/**
 * Sets given model to edit widget.
 */
void OutputGraphWidget::setModel(GraphTestModel* model){
	this->model = model;

    //disables certain parts of GUI
    ui->drawButton->setEnabled(false);
    ui->outputBox->setEnabled(false);
    hideDatasetSelection(true);

    //clears model name label if NULL given
	if(model == NULL){
		ui->itemName->setText(QString());
        hideDatasetSelection(true);
    }
    //fills view with model data
    else{
        bool saved = model->isSaved();
        ui->itemName->setText(model->name());
        if(!model->selectedNetworkName().isEmpty() && model->selectedNetwork() != NULL){
            ui->outputBox->setValue(model->output());
            outputChanged(model->output());
            if(model->plot() == NULL) drawGraph();
        }
        genNetworkList();
        connect(model, SIGNAL(changed(ChangeType)), this, SLOT(modelChanged(ChangeType)), Qt::UniqueConnection);
        model->setSaved(saved);
	}
}

/**
 * Called when model is changed.
 * @param type type of model change
 */
void OutputGraphWidget::modelChanged(ChangeType type){
	if(type == ModelRenamed)
		ui->itemName->setText(model->name());
	else if(type == SelectedNetworkRenamed)
        genNetworkList();
	else if(type == SelectedDatasetRenamed)
        genNetworkList();
	else if(type == SelectedNetworkDeleted)
        genNetworkList();
	else if(type == SelectedDatasetDeleted)
        genNetworkList();
}

/**
 * Draws and shows plot.
 */
void OutputGraphWidget::drawGraph(){
	model->drawPlot();
	setPlot();
}

/**
 * Adds model's plot to layout.
 * @param plot will be removed from layout when NULL given
 */
void OutputGraphWidget::setPlot(){
    //removes plot from layout and hides it
    if(!ui->graphFrame->layout()->isEmpty()){
        QWidget* wg = ui->graphFrame->layout()->takeAt(0)->widget();
        if(wg != NULL){
            ui->graphFrame->layout()->removeWidget(wg);
            wg->hide();
        }
    }

    //adds new plot to layout
    if(model->plot() != NULL){
        ui->graphFrame->layout()->addWidget(model->plot());
        model->plot()->show();
    }
}

/**
 * Hides or shows dataset selection.
 */
void OutputGraphWidget::hideDatasetSelection(bool hide){
    ui->datasetBox->setDisabled(hide);
    ui->datasetBox->setHidden(hide);
    ui->datasetLabel->setHidden(hide);
}

/**
 * Adds and selects saved network and dataset names to list boxes.
 */
void OutputGraphWidget::genNetworkList(){
    if(model == NULL) return;

    //clears selection box and adds existing networks names
    ui->networkBox->clear();
    ui->networkBox->addItem(QString(tr("<Choose neural network>")));
    QStringList nets = model->networkList();
    if(!nets.isEmpty()) ui->networkBox->addItems(nets);

    //looks for selected network name in selection box
    int index = ui->networkBox->findText(model->selectedNetworkName());

    //selects widget that was found
    if(index > 0){
        ui->networkBox->setCurrentIndex(index);
        networkSelected(model->selectedNetworkName());
    }
    //or just clears dataset selection box
    else{
        ui->datasetBox->clear();
        ui->datasetBox->addItem(QString(tr("<No network selected>")));
    }
}

/**
 * Called when neural network selected.
 * @param name selected network name
 */
void OutputGraphWidget::networkSelected(QString name){
    //clears selections and disables GUI items if
    //first item (dummy item) is selected
    if(ui->networkBox->currentIndex() < 1){
        model->selectNetwork(QString());
        ui->datasetBox->clear();
        ui->drawButton->setEnabled(false);
        ui->outputBox->setEnabled(false);
        return;
    }

    //stores selected network name in model
    model->selectNetwork(name);

    //clears and enable dataset selection box
    ui->datasetBox->clear();
    ui->datasetBox->setEnabled(true);

    //gets list of possible datasets for selected network
    QStringList list = model->datasetList(name);

    //if there is no possible datasets
    if(list.isEmpty()){
        ui->datasetBox->addItem(QString(tr("<No dataset available for this network>")));
    }
    //fills dataset selection box and tries to select selected name in select box
    else{
        ui->datasetBox->addItem(QString(tr("<Select testing dataset>")));
        ui->datasetBox->addItems(list);
        if(!model->selectedDatasetName().isEmpty()){
            int index = ui->datasetBox->findText(model->selectedDatasetName());
            if(index > 0){
                ui->datasetBox->setCurrentIndex(index);
                datasetSelected(model->selectedDatasetName());
            }else{
                model->selectDataset(QString());
            }
        }
    }

    //stores selected network name in model
    model->selectNetwork(name);

    //gets selected network model
    BaseModel* mdlBase = model->selectedNetwork();
    Q_ASSERT(mdlBase != NULL);
    TopologyEditModel* mdl = (TopologyEditModel*)mdlBase;

    //sets gui items
    ui->outputBox->setMaximum(mdl->outputCount());
    ui->outputBox->setEnabled(true);
    ui->drawButton->setEnabled(true);
}

/**
 * Called when dataset selected.
 */
void OutputGraphWidget::datasetSelected(QString name){
    //clears selections and disables GUI items if
    //first item (dummy item) is selected
    if(ui->datasetBox->currentIndex() < 1){
        model->selectDataset(QString());
        return;
    }

    //stores selected dataset name in model
    model->selectDataset(name);
}

/**
 * Called when output number is changed.
 */
void OutputGraphWidget::outputChanged(int value){
    if(value == 0 && (model->network()->inputCount() != 2 || model->network()->outputCount() <= 1)){
        ui->drawButton->setEnabled(false);
    }else if(value > 0){
        int index = ui->networkBox->findText(model->selectedNetworkName());
        if(index > 0) ui->drawButton->setEnabled(true);
        hideDatasetSelection(true);
    }else{
        hideDatasetSelection(false);
    }

	model->setOutput(value);
}

/**
 * Returns true if widget has some model.
 */
bool OutputGraphWidget::hasModel(){
	return model != NULL;
}

/**
 * Emits closePressed signal when close button is pressed.
 */
void OutputGraphWidget::closeBtnPressed(){
	emit closePressed(model);
}

}
