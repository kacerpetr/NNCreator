#include "LearningWidget.h"
#include "ui_LearningWidget.h"

namespace Application{

LearningWidget::LearningWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LearningWidget), model(NULL){
	ui->setupUi(this);
}

LearningWidget::~LearningWidget(){
	delete ui;
}

void LearningWidget::setModel(LearningConfigModel* model){
	ui->itemName->setText(model->getName());
	this->model = model;
}

bool LearningWidget::hasModel(){
	return model != NULL;
}

}
