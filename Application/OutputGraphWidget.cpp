#include "OutputGraphWidget.h"
#include "ui_OutputGraphWidget.h"

namespace Application{

OutputGraphWidget::OutputGraphWidget(QWidget *parent) : QWidget(parent), ui(new Ui::OutputGraphWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
}

OutputGraphWidget::~OutputGraphWidget(){
	delete ui;
}

void OutputGraphWidget::setModel(GraphTestModel* model){
	if(model == NULL){
		ui->itemName->setText(QString());
	}else{
		ui->itemName->setText(model->name());
	}
	this->model = model;
}

bool OutputGraphWidget::hasModel(){
	return model != NULL;
}

void OutputGraphWidget::closeBtnPressed(){
	emit closePressed(model);
}

}
