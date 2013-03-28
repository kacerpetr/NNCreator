#include "TextViewBoxDialog.h"
#include "ui_TextViewBoxDialog.h"

namespace Dialog{

/**
 * Class constructor.
 */
TextViewBoxDialog::TextViewBoxDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TextViewBoxDialog){
	ui->setupUi(this);
}

/**
 * Class destructor.
 */
TextViewBoxDialog::~TextViewBoxDialog(){
    delete ui;
}

/**
 * Appends text at end of text box.
 */
void TextViewBoxDialog::appendText(QString text){
	ui->textBrowser->append(text);
}

}
