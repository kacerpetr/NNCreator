#include "TopologyWidget.h"
#include "ui_TopologyWidget.h"

TopologyWidget::TopologyWidget(QWidget *parent) : QWidget(parent), ui(new Ui::TopologyWidget){
	ui->setupUi(this);
}

TopologyWidget::~TopologyWidget(){
	delete ui;
}
