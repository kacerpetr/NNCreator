#include "Edit.h"
#include "ui_Edit.h"

Edit::Edit(QWidget *parent) : QWidget(parent), ui(new Ui::Edit){
	ui->setupUi(this);

	Topology* t = new Topology(this);
	ui->fileList->addWidget(t);
}

Edit::~Edit(){
	delete ui;
}

