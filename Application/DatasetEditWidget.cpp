#include "DatasetEditWidget.h"
#include "ui_DatasetEditWidget.h"
#include <QDebug>
#include <QMenu>

namespace Application{

DatasetEditWidget::DatasetEditWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DatasetEditWidget),
  model(NULL)
{
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
	connect(ui->patternCountBox, SIGNAL(editingFinished()), this, SLOT(changePatternCount()));
	connect(ui->inputCountBox, SIGNAL(editingFinished()), this, SLOT(changeInputCount()));
	connect(ui->outputCountBox, SIGNAL(editingFinished()), this, SLOT(changeOutputCount()));
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));
}

DatasetEditWidget::~DatasetEditWidget(){
	delete ui;
}

void DatasetEditWidget::showContextMenu(){
	QMenu* contextMenu = new QMenu(this);
	Q_CHECK_PTR(contextMenu);
	contextMenu->addAction("Cut" , this , SLOT(newUnitBtnSlot()));
	contextMenu->addAction("Copy" , this , SLOT(cloneUnitBtnSlot()));
	contextMenu->addAction("Paste" , this , SLOT(newUnitBtnSlot()));
	contextMenu->addAction("Delete" , this , SLOT(cloneUnitBtnSlot()));
	contextMenu->popup(QCursor::pos());
	contextMenu->exec();
	delete contextMenu;
	contextMenu = 0;
}

void DatasetEditWidget::changePatternCount(){
	model->setPatternCount(ui->patternCountBox->value());
}

void DatasetEditWidget::changeInputCount(){
	model->setInputCount(ui->inputCountBox->value());
}

void DatasetEditWidget::changeOutputCount(){
	model->setOutputCount(ui->outputCountBox->value());
}

void DatasetEditWidget::closeBtnPressed(){
	emit closePressed(model);
}

void DatasetEditWidget::setModel(DatasetEditModel* model){
	if(model == NULL){
		ui->itemName->setText(QString());
		ui->tableView->setModel(NULL);
		ui->patternCountBox->setValue(1);
		ui->inputCountBox->setValue(1);
		ui->outputCountBox->setValue(1);
	}else{
		ui->itemName->setText(model->getName());
		ui->tableView->setModel(model);
		ui->patternCountBox->setValue(model->patternCount());
		ui->inputCountBox->setValue(model->inputCount());
		ui->outputCountBox->setValue(model->outputCount());
	}
	this->model = model;
}

bool DatasetEditWidget::hasModel(){
	return model != NULL;
}

}
