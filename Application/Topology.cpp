#include "Topology.h"
#include "ui_Topology.h"

Topology::Topology(QWidget *parent) : QWidget(parent), ui(new Ui::Topology){
	ui->setupUi(this);
}

Topology::~Topology(){
	delete ui;
}
