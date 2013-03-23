#include "NoModelWidget.h"
#include "ui_NoModelWidget.h"

namespace Application{

/**
 * Class constructor.
 */
NoModelWidget::NoModelWidget(QWidget *parent) : QWidget(parent), ui(new Ui::NoModelWidget){
	ui->setupUi(this);
}

/**
 * Class destructor.
 */
NoModelWidget::~NoModelWidget(){
	delete ui;
}

}
