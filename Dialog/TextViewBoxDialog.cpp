#include "TextViewBoxDialog.h"
#include "ui_TextViewBoxDialog.h"

TextViewBoxDialog::TextViewBoxDialog(QWidget *parent) : QDialog(parent), ui(new Ui::TextViewBoxDialog){
	ui->setupUi(this);
}

void TextViewBoxDialog::appendText(QString text){
	ui->textBrowser->append(text);
}

TextViewBoxDialog::~TextViewBoxDialog(){
	delete ui;
}
