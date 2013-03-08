#include "TopologyWidget.h"
#include "ui_TopologyWidget.h"
#include "GuiPart/LayerEditWidget.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLine>
#include <QDebug>

namespace Application{

////////////////////////////////////////////////////////
////// Public methods //////////////////////////////////
////////////////////////////////////////////////////////

TopologyWidget::TopologyWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TopologyWidget), model(NULL){
	ui->setupUi(this);

	npw = new NetParamWidget(this);
	ui->splitterH->addWidget(npw);

	//connects signal slots
	connect(ui->appendButton, SIGNAL(pressed()), this, SLOT(appendLayer()));
	connect(ui->removeButton, SIGNAL(pressed()), this, SLOT(removeSelected()));
	connect(ui->duplicateButton, SIGNAL(pressed()), this, SLOT(duplicateSelected()));
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));

	//adds layout to layer editor
	layerEditLayout = new QVBoxLayout(ui->layerScrollAreaContent);
	ui->layerScrollAreaContent->setLayout(layerEditLayout);
	layerEditLayout->setMargin(0);
	layerEditLayout->setSpacing(0);
	layerEditLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

TopologyWidget::~TopologyWidget(){
	//clears layer edit widgets
	for(int i = 0; i < layerEditList.length(); i++){
		delete layerEditList[i];
		layerEditList[i] = NULL;
	}

	//clears lines between widgets
	for(int i = 0; i < layerLineList.length(); i++){
		delete layerLineList[i];
		layerLineList[i] = NULL;
	}

	delete layerEditLayout;
	delete ui;
}

void TopologyWidget::setModel(TopologyEditModel* model){
	this->model = model;
	if(model == NULL){
		ui->itemName->setText(QString());
		clearView();
	}else{
		ui->itemName->setText(model->name());
		clearView();
		makeView();
		connect(
			model, SIGNAL(changed(ChangeType)),
			this, SLOT(modelChanged(ChangeType)),
			Qt::UniqueConnection
		);
		layerEditList[model->selectedLayer()]->setSelected(true);
		widgetPressed(layerEditList[model->selectedLayer()]);
	}
	npw->setModel(model);
}

bool TopologyWidget::hasModel(){
	return model != NULL;
}

////////////////////////////////////////////////////////
////// Private slots //////////////////////////////////
////////////////////////////////////////////////////////

void TopologyWidget::closeBtnPressed(){
	emit closePressed(model);
}

void TopologyWidget::widgetPressed(LayerEditWidget* widget){
	for(int i = 0; i < layerEditList.count(); i++){
		if(widget != layerEditList[i]){
			layerEditList[i]->setSelected(false);
		}
		else if(i == 0){
			ui->removeButton->setDisabled(true);
		}else{
			ui->removeButton->setDisabled(false);
		}
		if(widget == layerEditList[i]) model->setSelectedLayer(i);
	}

	if(layerEditList.count() == 2){
		ui->removeButton->setDisabled(true);
	}

	fillWeightTable();
}

void TopologyWidget::appendLayer(){
	model->appendLayer();
	clearView();
	makeView();
	model->modelChanged(TopologyChange);
}

void TopologyWidget::duplicateLayer(LayerEditWidget* widget){
	int layer = layerEditList.indexOf(widget)-1;
	model->duplicateLayer(layer);
	clearView();
	makeView();
	model->modelChanged(TopologyChange);
}

void TopologyWidget::removeLayer(LayerEditWidget* widget){
	int layer = layerEditList.indexOf(widget)-1;
	model->removeLayer(layer);
	clearView();
	makeView();
	model->modelChanged(TopologyChange);
}

void TopologyWidget::duplicateSelected(){
	int layer = selectedLayer();
	if(layer == -2) return;
	model->duplicateLayer(layer);
	clearView();
	makeView();
	model->modelChanged(TopologyChange);
}

void TopologyWidget::removeSelected(){
	int layer = selectedLayer();
	if(layer == -2) return;
	model->removeLayer(layer);
	clearView();
	makeView();
	model->modelChanged(TopologyChange);
}

void TopologyWidget::countChanged(LayerEditWidget* widget, int count){
	int index = layerEditList.indexOf(widget)-1;
	if(index == -1) model->setInputCount(count);
	else model->setNeuronCount(index, count);
	model->modelChanged(TopologyChange);
}

void TopologyWidget::modelChanged(ChangeType type){
	if(type == WeightChange || type == TopologyChange)
		fillWeightTable();
	if(type == ModelRenamed)
		ui->itemName->setText(model->name());
}

////////////////////////////////////////////////////////
////// Private methods /////////////////////////////////
////////////////////////////////////////////////////////

void TopologyWidget::fillWeightTable(){
	//index of selected layer
	int layer = selectedLayer();
	if(layer == -2) return;

	//clears weight table
	ui->weightTable->clear();

	//input layer selected
	if(layer == -1){
		ui->layerLabel->setText("[0] input layer:");
		ui->weightTable->setRowCount(model->inputCount());
		ui->weightTable->setColumnCount(2);

		QStringList hList;
		hList.append("Bias");
		hList.append("Weight 1");
		ui->weightTable->setHorizontalHeaderLabels(hList);

		QStringList vList;
		for(int i = 0; i < model->inputCount(); i++)
			vList.append("Neuron " + QString::number(i+1));
		ui->weightTable->setVerticalHeaderLabels(vList);

		for(int i = 0; i < model->inputCount(); i++){
			//bias
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setText("0");
			ui->weightTable->setItem(i, 0, item);
			//weight
			item = new QTableWidgetItem();
			item->setText("1");
			ui->weightTable->setItem(i, 1, item);
		}

		return;
	};

	//generats weight table header
	if(layer < model->layerCount()-1)
		ui->layerLabel->setText("[" + QString::number(layer+1) + "]" + " inner layer:");
	else
		ui->layerLabel->setText("[" + QString::number(layer+1) + "]" + " output layer:");

	//sets table size
	ui->weightTable->setRowCount(model->neuronCount(layer));
	ui->weightTable->setColumnCount(model->weightCount(layer)+1);

	//column headers
	QStringList hList;
	hList.append("Bias");
	for(int i = 0; i < model->weightCount(layer); i++)
		hList.append("Weight " + QString::number(i+1));
	ui->weightTable->setHorizontalHeaderLabels(hList);

	//row headers
	QStringList vList;
	for(int i = 0; i < model->neuronCount(layer); i++)
		vList.append("Neuron " + QString::number(i+1));
	ui->weightTable->setVerticalHeaderLabels(vList);

	//fills table with content
	for(int i = 0; i < model->neuronCount(layer); i++){
		QList<double> weight = (*model)[layer][i].weights();

		//bias
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText(QString::number((*model)[layer][i].bias()));
		ui->weightTable->setItem(i, 0, item);

		//weights
		for(int j = 0; j < weight.length(); j++){
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setText(QString::number(weight[j]));
			ui->weightTable->setItem(i, j+1, item);
		}
	}
}

int TopologyWidget::selectedLayer(){
	for(int i = 0; i < layerEditList.count(); i++){
		if(layerEditList[i]->isSelected()){
			return i-1;
		}
	}
	return -2;
}

void TopologyWidget::makeView(){
	Q_ASSERT(model != NULL);

	//input layer

	LayerEditWidget* inputLayer = new LayerEditWidget(ui->layerScrollAreaContent);
	inputLayer->setLayerName("[0] input layer: ");
	inputLayer->setAsInputLayer(true);
	inputLayer->setRemoveButtonDisabled(true);
	inputLayer->setNeuronCount(model->inputCount());

	QFrame* line = new QFrame(ui->layerScrollAreaContent);
	line->setObjectName(QString::fromUtf8("line"));
	line->setMaximumHeight(2);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	connect(inputLayer, SIGNAL(widgetPressed(LayerEditWidget*)), this, SLOT(widgetPressed(LayerEditWidget*)));
	connect(inputLayer, SIGNAL(removePressed(LayerEditWidget*)), this, SLOT(removeLayer(LayerEditWidget*)));
	connect(inputLayer, SIGNAL(duplicatePressed(LayerEditWidget*)), this, SLOT(duplicateLayer(LayerEditWidget*)));
	connect(inputLayer, SIGNAL(countChanged(LayerEditWidget*,int)), this, SLOT(countChanged(LayerEditWidget*, int)));

	layerEditList.append(inputLayer);
	layerLineList.append(line);
	layerEditLayout->insertWidget(0, line);
	layerEditLayout->insertWidget(0, inputLayer);

	//output layer and inner layers

	for(int i = 0; i <  model->layerCount(); i++){
		LayerEditWidget* layer = new LayerEditWidget(ui->layerScrollAreaContent);

		if(i < model->layerCount()-1)
			layer->setLayerName("[" + QString::number(i+1) + "] inner layer: ");
		else
			layer->setLayerName("[" + QString::number(i+1) + "] output layer: ");

		if(model->layerCount() <= 1) layer->setRemoveButtonDisabled(true);
		layer->setNeuronCount(model->neuronCount(i));

		QFrame* line = new QFrame(ui->layerScrollAreaContent);
		line->setObjectName(QString::fromUtf8("line"));
		line->setMaximumHeight(2);
		line->setFrameShape(QFrame::HLine);
		line->setFrameShadow(QFrame::Sunken);

		connect(layer, SIGNAL(widgetPressed(LayerEditWidget*)), this, SLOT(widgetPressed(LayerEditWidget*)));
		connect(layer, SIGNAL(removePressed(LayerEditWidget*)), this, SLOT(removeLayer(LayerEditWidget*)));
		connect(layer, SIGNAL(duplicatePressed(LayerEditWidget*)), this, SLOT(duplicateLayer(LayerEditWidget*)));
		connect(layer, SIGNAL(countChanged(LayerEditWidget*,int)), this, SLOT(countChanged(LayerEditWidget*, int)));

		layerEditList.append(layer);
		layerLineList.append(line);
		layerEditLayout->insertWidget(0, line);
		layerEditLayout->insertWidget(0, layer);
	}
}

void TopologyWidget::clearView(){
	//deletes layer edit widgets
	for(int i = 0; i < layerEditList.length(); i++){
		layerEditLayout->removeWidget(layerEditList[i]);
		delete layerEditList[i];
		layerEditList[i] = NULL;
	}
	layerEditList.clear();

	//deletes lines
	for(int i = 0; i < layerLineList.length(); i++){
		layerEditLayout->removeWidget(layerLineList[i]);
		delete layerLineList[i];
		layerLineList[i] = NULL;
	}
	layerLineList.clear();
}

}
