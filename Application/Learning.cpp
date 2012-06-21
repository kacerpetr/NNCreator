#include "Learning.h"
#include "ui_Learning.h"

Learning::Learning(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Learning)
{
	ui->setupUi(this);
}

Learning::~Learning()
{
	delete ui;
}
