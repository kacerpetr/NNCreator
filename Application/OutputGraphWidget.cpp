#include "OutputGraphWidget.h"
#include "ui_OutputGraphWidget.h"

namespace Application{

OutputGraphWidget::OutputGraphWidget(QWidget *parent) : QWidget(parent), ui(new Ui::OutputGraphWidget), model(NULL){
	ui->setupUi(this);
}

OutputGraphWidget::~OutputGraphWidget(){
	delete ui;
}

void OutputGraphWidget::setModel(GraphTestModel* model){
	this->model = model;
	ui->itemName->setText(model->getName());
}

bool OutputGraphWidget::hasModel(){
	return model != NULL;
}

}
