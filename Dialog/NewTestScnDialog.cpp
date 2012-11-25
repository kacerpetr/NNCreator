#include "NewTestScnDialog.h"
#include "ui_NewTestScnDialog.h"

NewTestScnDialog::NewTestScnDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewTestScnDialog), confirmed(false){
	ui->setupUi(this);
	connect(ui->okButton, SIGNAL(pressed()), this, SLOT(ok()));
}

NewTestScnDialog::~NewTestScnDialog(){
	delete ui;
}

QString NewTestScnDialog::getName(){
	return ui->scenarioNameEdit->text();
}

Project::TestingScenarioType NewTestScnDialog::getType(){
	switch(ui->scenarioTypeBox->currentIndex()){
		case 0:
			return Project::TEST_BY_DATASET;
		case 1:
			return Project::OUTPUT_SPACE_GRAPH;
		case 2:
			return Project::TESTING_SCRIPT;
	}
	return Project::TEST_BY_DATASET;
}

bool NewTestScnDialog::isConfirmed(){
	return confirmed;
}

void NewTestScnDialog::ok(){
	confirmed = true;
	close();
}
