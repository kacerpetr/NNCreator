#include "LayerEditWidget.h"
#include "ui_LayerEditWidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>

namespace Application{

/**
 * Class constructor.
 */
LayerEditWidget::LayerEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LayerEditWidget){
	ui->setupUi(this);
	setSelected(false);
	setAsInputLayer(false);
	setNeuronCount(1);
	connect(ui->neuronCountSpinBox, SIGNAL(valueChanged(int)), this, SLOT(neuronCountChange(int)));
	connect(ui->duplicateButton, SIGNAL(pressed()), this, SLOT(duplicateButtonPress()));
	connect(ui->removeButton, SIGNAL(pressed()), this, SLOT(removeButtonPress()));
}

/**
 * Class destructor.
 */
LayerEditWidget::~LayerEditWidget(){
	delete ui;
}

/**
 * Returns true if layer is selected.
 */
bool LayerEditWidget::isSelected(){
	return selected;
}

/**
 * Set layer as selected.
 */
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

/**
 * Sets layer name.
 */
void LayerEditWidget::setLayerName(QString name){
	ui->layerNameLabel->setText(name);
}

/**
 * Returns layer name.
 */
QString LayerEditWidget::getLayerName(){
	return ui->layerNameLabel->text();
}

/**
 * Returns true if layer is marked as input layer.
 */
bool LayerEditWidget::isInputLayer(){
	return inputLayer;
}

/**
 * Sets layer as input layer.
 */
void LayerEditWidget::setAsInputLayer(bool inputLayer){
	this->inputLayer = inputLayer;
	setNeuronImageFrame();
}

/**
 * Sets count of neurons in layer.
 */
void LayerEditWidget::setNeuronCount(int neuronCount){
	ui->neuronCountSpinBox->setValue(neuronCount);
	setNeuronImageFrame();
}

/**
 * Returns count of neurons in layer.
 */
int LayerEditWidget::getNeuronCount(){
	return ui->neuronCountSpinBox->value();
}

/**
 * Disables or enables dupplicate button.
 */
void LayerEditWidget::setDuplicateButtonDisabled(bool disabled){
	ui->duplicateButton->setDisabled(disabled);
}

/**
 * Disables or enables rename button.
 */
void LayerEditWidget::setRemoveButtonDisabled(bool disabled){
	ui->removeButton->setDisabled(disabled);
}

/**
 * Returns true if dupplicate button is disabled.
 */
bool LayerEditWidget::isDuplicateButtonDisabled(){
	return !ui->duplicateButton->isEnabled();
}

/**
 * Returns true if remove button is disabled.
 */
bool LayerEditWidget::isRemoveButtonDisabled(){
	return !ui->removeButton->isEnabled();
}

/**
 * Called when neuron count is changed.
 */
void LayerEditWidget::neuronCountChange(int count){
	setNeuronImageFrame();
	emit countChanged(this, count);
}

/**
 * Called when dupplicate button is pressed.
 */
void LayerEditWidget::duplicateButtonPress(){
	emit duplicatePressed(this);
}

/**
 * Called when remove button is pressed.
 */
void LayerEditWidget::removeButtonPress(){
	emit removePressed(this);
}

/**
 * Draws neural network layer topology.
 */
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

/**
 * Mouse press event implementation.
 */
void LayerEditWidget::mousePressEvent(QMouseEvent* e){
	if(!selected) setSelected(true);
	emit widgetPressed(this);
}

}
