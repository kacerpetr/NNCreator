#include "Testing.h"
#include "ui_Testing.h"

Testing::Testing(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Testing)
{
	ui->setupUi(this);
}

Testing::~Testing()
{
	delete ui;
}
