#include "LabelButton.h"

namespace Application{

/**
 * Class constructor.
 */
LabelButton::LabelButton(QWidget *parent) : QLabel(parent){}

void LabelButton::mousePressEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton){
		emit pressed();
		emit pressed(this);
	}
}

/**
 * Mouse enter event.
 */
void LabelButton::enterEvent(QEvent* event){
	QFont font;
	font.setUnderline(true);
	setFont(font);
}

/**
 * Mouse leave event.
 */
void LabelButton::leaveEvent(QEvent* event){
	QFont font;
	font.setUnderline(false);
	setFont(font);
}

}
