#include "AboutDialog.h"
#include "ui_AboutDialog.h"

namespace Dialog{

/**
 * Class constructor.
 */
AboutDialog::AboutDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
}

/**
 * Class destructor.
 */
AboutDialog::~AboutDialog(){
	delete ui;
}

}
