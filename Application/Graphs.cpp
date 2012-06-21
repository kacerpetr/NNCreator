#include "Graphs.h"
#include "ui_Graphs.h"

Graphs::Graphs(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Graphs)
{
	ui->setupUi(this);
}

Graphs::~Graphs()
{
	delete ui;
}
