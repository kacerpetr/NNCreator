#include "DatasetEditWidget.h"
#include "ui_DatasetEditWidget.h"
#include <QDebug>
#include <QMenu>

namespace Application{

DatasetEditWidget::DatasetEditWidget(QWidget *parent) :
	QWidget(parent),
	editValOk(false),
	editVal(0),
	ui(new Ui::DatasetEditWidget),
	model(NULL),
	contextMenu(NULL)
{
	ui->setupUi(this);
	connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu()));
	connect(ui->patternCountBox, SIGNAL(valueChanged(int)), this, SLOT(changePatternCount(int)));
	connect(ui->inputCountBox, SIGNAL(valueChanged(int)), this, SLOT(changeInputCount(int)));
	connect(ui->outputCountBox, SIGNAL(valueChanged(int)), this, SLOT(changeOutputCount(int)));
	connect(ui->closeButton, SIGNAL(pressed()), this, SLOT(closeBtnPressed()));

	//context menu of editor
	contextMenu = new QMenu(this);
	contextMenu->addAction("Cut", this, SLOT(cutCell()), Qt::CTRL | Qt::Key_X);
	contextMenu->addAction("Copy", this, SLOT(copyCell()), Qt::CTRL | Qt::Key_C);
	contextMenu->addAction("Paste", this, SLOT(pasteCell()), Qt::CTRL | Qt::Key_V);
	contextMenu->addAction("Delete", this, SLOT(deleteCell()), Qt::Key_Delete);
	this->addActions(contextMenu->actions());
}

DatasetEditWidget::~DatasetEditWidget(){
	delete ui;
}

void DatasetEditWidget::showContextMenu(){
	contextMenu->popup(QCursor::pos());
	contextMenu->exec();
}

void DatasetEditWidget::changePatternCount(int value){
	if(model == NULL) return;
	model->setPatternCount(value);
}

void DatasetEditWidget::changeInputCount(int value){
	if(model == NULL) return;
	model->setInputCount(value);
}

void DatasetEditWidget::changeOutputCount(int value){
	if(model == NULL) return;
	model->setOutputCount(value);
}

void DatasetEditWidget::closeBtnPressed(){
	emit closePressed(model);
}

void DatasetEditWidget::copyCell(){
	QModelIndex index = ui->tableView->currentIndex();
	editVal = model->viewModel()->data(index, Qt::DisplayRole).toDouble(&editValOk);
	qDebug() << "copy:" << editVal << " null:" << !editValOk;
	ui->tableView->update(index);
}

void DatasetEditWidget::cutCell(){
	QModelIndex index = ui->tableView->currentIndex();
	editVal = model->viewModel()->data(index, Qt::DisplayRole).toDouble(&editValOk);
	model->viewModel()->clearCell(index);
	qDebug() << "cut:" << editVal << " null:" << !editValOk;
	ui->tableView->update(index);
}

void DatasetEditWidget::pasteCell(){
	QModelIndex index = ui->tableView->currentIndex();
	if(editValOk) model->viewModel()->setData(index, editVal, Qt::EditRole);
	else model->viewModel()->clearCell(index);
	qDebug() << "paste:" << editVal << " null:" << !editValOk;
	ui->tableView->update(index);
}

void DatasetEditWidget::deleteCell(){
	QModelIndex index = ui->tableView->currentIndex();
	model->viewModel()->clearCell(index);
	ui->tableView->update(index);
}

void DatasetEditWidget::setModel(DatasetEditModel* model){
	//sets model
	this->model = model;

	//sets view for NULL model
	if(model == NULL){
		ui->itemName->setText(QString());
		ui->tableView->setModel(NULL);
		ui->patternCountBox->setValue(1);
		ui->inputCountBox->setValue(1);
		ui->outputCountBox->setValue(1);
	}
	//sets view to show model data
	else{
		ui->itemName->setText(model->name());
		ui->tableView->setModel(model->viewModel());
		ui->patternCountBox->setValue(model->minPatternCount());
		ui->inputCountBox->setValue(model->minInputCount());
		ui->outputCountBox->setValue(model->minOutputCount());
	}
}

bool DatasetEditWidget::hasModel(){
	return model != NULL;
}

}
