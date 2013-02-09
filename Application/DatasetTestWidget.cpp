#include "DatasetTestWidget.h"
#include "ui_DatasetTestWidget.h"

namespace Application{

DatasetTestWidget::DatasetTestWidget(QWidget *parent) : QWidget(parent), ui(new Ui::DatasetTestWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
}

DatasetTestWidget::~DatasetTestWidget(){
	delete ui;
}

void DatasetTestWidget::setModel(DatasetTestModel* model){
	if(model == NULL){
		ui->itemName->setText(QString());
	}else{
		ui->itemName->setText(model->name());
		ui->datasetView->setModel(new DatasetEditModel());

	}
	this->model = model;
}

bool DatasetTestWidget::hasModel(){
	return model != NULL;
}

void DatasetTestWidget::closeBtnPressed(){
	emit closePressed(model);
}

}
