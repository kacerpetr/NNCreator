#include "DatasetTestWidget.h"
#include "ui_DatasetTestWidget.h"

DatasetTestWidget::DatasetTestWidget(QWidget *parent) : QWidget(parent), ui(new Ui::DatasetTestWidget), model(NULL){
	ui->setupUi(this);
}

DatasetTestWidget::~DatasetTestWidget(){
	delete ui;
}

void DatasetTestWidget::setModel(DatasetTestModel* model){
	this->model = model;
	ui->itemName->setText(model->getName());
	ui->datasetView->setModel(new DatasetEditModel());
}

bool DatasetTestWidget::hasModel(){
	return model != NULL;
}
