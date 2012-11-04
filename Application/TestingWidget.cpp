#include "TestingWidget.h"
#include "ui_TestingWidget.h"

TestingWidget::TestingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::TestingWidget)
{
	ui->setupUi(this);
}

TestingWidget::~TestingWidget()
{
	delete ui;
}
