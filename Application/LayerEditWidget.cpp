#include "LayerEditWidget.h"
#include "ui_LayerEditWidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>

LayerEditWidget::LayerEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LayerEditWidget){
	ui->setupUi(this);
	setSelected(false);
	setAsInputLayer(false);
	setNeuronCount(1);
	connect(ui->neuronCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(neuronCountChange(int)));
	connect(ui->duplicateButton, SIGNAL(pressed()), this, SLOT(duplicateButtonPress()));
	connect(ui->removeButton, SIGNAL(pressed()), this, SLOT(renameButtonPress()));
}

LayerEditWidget::~LayerEditWidget(){
	delete ui;
}

bool LayerEditWidget::isSelected(){
	return selected;
}

void LayerEditWidget::setSelected(bool selected){
	this->selected = selected;
	if(selected){
		QString str =
		"#backgroundFrame{"
		"	background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(0, 0, 139, 8), stop:1 rgba(227, 227, 255, 3))"
		"}";
		ui->backgroundFrame->setStyleSheet(str);
	}else{
		QString str =
		"#backgroundFrame:hover{"
		"	background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0 rgba(0, 0, 0, 8), stop:1 rgba(227, 227, 255, 3))"
		"}";
		ui->backgroundFrame->setStyleSheet(str);
	}
}

void LayerEditWidget::setLayerName(QString name){
	ui->layerNameLabel->setText(name);
}

QString LayerEditWidget::getLayerName(){
	return ui->layerNameLabel->text();
}

bool LayerEditWidget::isInputLayer(){
	return inputLayer;
}

void LayerEditWidget::setAsInputLayer(bool inputLayer){
	this->inputLayer = inputLayer;
	setNeuronImageFrame();
}

void LayerEditWidget::setNeuronCount(int neuronCount){
	ui->neuronCountSpinBox->setValue(neuronCount);
	setNeuronImageFrame();
}

int LayerEditWidget::getNeuronCount(){
	return ui->neuronCountSpinBox->value();
}

void LayerEditWidget::setDuplicateButtonDisabled(bool disabled){
	ui->duplicateButton->setDisabled(disabled);
}

void LayerEditWidget::setRemoveButtonDisabled(bool disabled){
	ui->removeButton->setDisabled(disabled);
}

bool LayerEditWidget::isDuplicateButtonDisabled(){
	return !ui->duplicateButton->isEnabled();
}

bool LayerEditWidget::isRemoveButtonDisabled(){
	return !ui->removeButton->isEnabled();
}

void LayerEditWidget::neuronCountChange(int count){
	emit neuronCountChanged(this, count);
	setNeuronImageFrame();
}

void LayerEditWidget::duplicateButtonPress(){
	emit duplicateButtonPressed(this);
}

void LayerEditWidget::renameButtonPress(){
	emit renameButtonPressed(this);
}

void LayerEditWidget::setNeuronImageFrame(){
	QString labelStyle;

	if(inputLayer){
		labelStyle =
		"background-image: url(:/neuron1w);"
		"background-position: center center;"
		"background-repeat: no-repeat;";
	}else{
		labelStyle =
		"background-image: url(:/neuron3w);"
		"background-position: center center;"
		"background-repeat: no-repeat;";
	}

	for(int i = 0; i < neuronList.count(); i++){
		ui->neuronImageFrame->layout()->removeWidget(neuronList[i]);
		delete neuronList[i];
	}
	neuronList.clear();

	if(ui->neuronCountSpinBox->value() <= 7){
		for(int i = 1; i < ui->neuronCountSpinBox->value()+1; i++){
			QLabel* neuron = new QLabel(ui->neuronImageFrame);
			neuron->setMaximumWidth(36);
			neuron->setMinimumWidth(36);
			neuron->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			neuron->setStyleSheet(labelStyle);
			neuron->setText(QString::number(i));
			neuronList.append(neuron);
			ui->neuronImageFrame->layout()->addWidget(neuron);
		}
	}else{
		for(int i = 1; i < 8; i++){
			QLabel* neuron = new QLabel(ui->neuronImageFrame);
			neuron->setMaximumWidth(36);
			neuron->setMinimumWidth(36);
			neuron->setStyleSheet(labelStyle);
			neuron->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			if(i == 7) neuron->setText(QString::number(ui->neuronCountSpinBox->value()));
			else if(i == 6)	neuron->setText(QString("..."));
			else neuron->setText(QString::number(i));
			neuronList.append(neuron);
			ui->neuronImageFrame->layout()->addWidget(neuron);
		}
	}
}

void LayerEditWidget::mousePressEvent(QMouseEvent* e){
	if(!selected) setSelected(true);
	emit widgetPressed(this);
}
