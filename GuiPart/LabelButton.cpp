/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
