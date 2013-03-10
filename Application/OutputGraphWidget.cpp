#include "OutputGraphWidget.h"
#include "ui_OutputGraphWidget.h"
#include "GuiPart/Plot1D.h"
#include "Project/DatasetEditModel.h"

namespace Application{

OutputGraphWidget::OutputGraphWidget(QWidget *parent) : QWidget(parent), ui(new Ui::OutputGraphWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
	connect(ui->drawButton, SIGNAL(pressed()), this, SLOT(drawGraph()));
	connect(ui->outputBox, SIGNAL(valueChanged(int)), this, SLOT(outputChanged(int)));
	connect(ui->datasetBox, SIGNAL(activated(QString)), this, SLOT(datasetSelected(QString)));
	connect(ui->networkBox, SIGNAL(activated(QString)), this, SLOT(networkSelected(QString)));
	ui->drawButton->setEnabled(false);
	ui->outputBox->setEnabled(false);
}

OutputGraphWidget::~OutputGraphWidget(){
	delete ui;
}

void OutputGraphWidget::setModel(GraphTestModel* model){
	this->model = model;

	if(model == NULL){
		ui->itemName->setText(QString());
	}else{
		ui->itemName->setText(model->name());
		genSelectedLists();
		ui->outputBox->setValue(model->output());
		setPlot();
		connect(model, SIGNAL(changed(ChangeType)), this, SLOT(modelChanged(ChangeType)), Qt::UniqueConnection);
	}
}

void OutputGraphWidget::modelChanged(ChangeType type){
	if(type == ModelRenamed)
		ui->itemName->setText(model->name());
	else if(type == SelectedNetworkRenamed)
		genSelectedLists();
	else if(type == SelectedDatasetRenamed)
		genSelectedLists();
	else if(type == SelectedNetworkDeleted)
		genSelectedLists();
	else if(type == SelectedDatasetDeleted)
		genSelectedLists();
}

void OutputGraphWidget::setPlot(){
	if(!ui->graphFrame->layout()->isEmpty()){
		QWidget* wg = ui->graphFrame->layout()->takeAt(0)->widget();
		if(wg != NULL){
			ui->graphFrame->layout()->removeWidget(wg);
			wg->hide();
		}
	}
	if(model->plot() == NULL) return;
	ui->graphFrame->layout()->addWidget(model->plot());
	model->plot()->show();
}

void OutputGraphWidget::drawGraph(){
	model->drawPlot();
	setPlot();
}

void OutputGraphWidget::genSelectedLists(){
	ui->networkBox->clear();
	ui->networkBox->addItem(QString("<Choose neural network>"));

	QStringList nets = model->networkList();
	if(!nets.isEmpty()) ui->networkBox->addItems(nets);

	int index = ui->networkBox->findText(model->selectedNetworkName());
	if(index > 0){
		ui->networkBox->setCurrentIndex(index);
		networkSelected(model->selectedNetworkName());
	}
	else{
		ui->datasetBox->clear();
		ui->datasetBox->addItem(QString("<No network selected>"));
	}
}

void OutputGraphWidget::networkSelected(QString name){
	if(ui->networkBox->currentIndex() < 1){
		model->selectNetwork(QString());
		ui->drawButton->setEnabled(false);
		ui->outputBox->setEnabled(false);
		return;
	}

	ui->datasetBox->clear();
	QStringList list = model->datasetList(name);

	if(list.isEmpty()){
		ui->datasetBox->addItem(QString("<No dataset available for this network>"));
	}else{
		ui->datasetBox->addItem(QString("<Select training dataset>"));
		ui->datasetBox->addItems(list);
		if(!model->selectedDatasetName().isEmpty()){
			int index = ui->datasetBox->findText(model->selectedDatasetName());
			if(index > 0) ui->datasetBox->setCurrentIndex(index);
		}
	}

	model->selectNetwork(name);

	BaseModel* mdlBase = model->selectedNetwork();
	Q_ASSERT(mdlBase != NULL);
	TopologyEditModel* mdl = (TopologyEditModel*)mdlBase;

	ui->outputBox->setMaximum(mdl->outputCount());
	ui->outputBox->setEnabled(true);
	ui->drawButton->setEnabled(true);
}

void OutputGraphWidget::datasetSelected(QString name){
	if(ui->datasetBox->currentIndex() < 1){
		model->selectDataset(QString());
		return;
	}

	model->selectDataset(name);
}

void OutputGraphWidget::outputChanged(int value){
	model->setOutput(value);
}

bool OutputGraphWidget::hasModel(){
	return model != NULL;
}

void OutputGraphWidget::closeBtnPressed(){
	emit closePressed(model);
}

}
