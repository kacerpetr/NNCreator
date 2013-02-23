#include "LabelButton.h"

namespace Application{

LabelButton::LabelButton(QWidget *parent) : QLabel(parent){}

void LabelButton::mousePressEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton){
		emit pressed();
		emit pressed(this);
	}
}

void LabelButton::enterEvent(QEvent* event){
	QFont font;
	font.setUnderline(true);
	setFont(font);
}

void LabelButton::leaveEvent(QEvent* event){
	QFont font;
	font.setUnderline(false);
	setFont(font);
}

}
