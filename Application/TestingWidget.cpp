#include "TestingWidget.h"
#include "ui_TestingWidget.h"

TestingWidget::TestingWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TestingWidget), model(NULL){
	ui->setupUi(this);
}

TestingWidget::~TestingWidget(){
	delete ui;
}

void TestingWidget::setModel(TestingScenarioModel* model){
	this->model = model;
	ui->itemName->setText(model->getName());
	ui->datasetView->setModel(model->getDatasetModel());
}

bool TestingWidget::hasModel(){
	return model != NULL;
}
