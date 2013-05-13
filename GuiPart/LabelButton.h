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

#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QLabel>
#include <QMouseEvent>

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Button based on QLabel that looks like html link.
 */
class LabelButton : public QLabel{
	Q_OBJECT

	public:
		LabelButton(QWidget *parent = 0);

	signals:
        /** Emmited when label text pressed. */
		void pressed();
        /** Emmited when label text pressed. */
		void pressed(LabelButton*);

	private:
		virtual void mousePressEvent(QMouseEvent * event);
		virtual void enterEvent(QEvent * event);
		virtual void leaveEvent(QEvent * event);
};

}

#endif // LABELBUTTON_H
