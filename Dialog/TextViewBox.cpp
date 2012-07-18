#include "TextViewBox.h"
#include "ui_TextViewBox.h"

TextViewBox::TextViewBox(QWidget *parent) : QDialog(parent), ui(new Ui::TextViewBox){
	ui->setupUi(this);
}

void TextViewBox::appendText(QString text){
	ui->textBrowser->append(text);
}

TextViewBox::~TextViewBox(){
	delete ui;
}
