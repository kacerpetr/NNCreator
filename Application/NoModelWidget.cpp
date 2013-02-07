#include "NoModelWidget.h"
#include "ui_NoModelWidget.h"

namespace Application{

NoModelWidget::NoModelWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NoModelWidget){
	ui->setupUi(this);
}

NoModelWidget::~NoModelWidget(){
	delete ui;
}

}
