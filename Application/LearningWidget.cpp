#include "LearningWidget.h"
#include "ui_LearningWidget.h"

namespace Application{

LearningWidget::LearningWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LearningWidget), model(NULL){
	ui->setupUi(this);
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
}

LearningWidget::~LearningWidget(){
	delete ui;
}

void LearningWidget::setModel(LearningConfigModel* model){
	if(model == NULL){
		ui->itemName->setText(QString());
	}else{
		ui->itemName->setText(model->name());
	}
	this->model = model;
}

bool LearningWidget::hasModel(){
	return model != NULL;
}

void LearningWidget::closeBtnPressed(){
	emit closePressed(model);
}

}
