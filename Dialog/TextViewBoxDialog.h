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

#ifndef TEXTVIEWBOXDIALOG_H
#define TEXTVIEWBOXDIALOG_H

#include <QDialog>

namespace Ui{
	class TextViewBoxDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * Shows text in read only text edit.
 */
class TextViewBoxDialog : public QDialog{
	Q_OBJECT
		
	public:
        TextViewBoxDialog(QWidget *parent = 0);
        ~TextViewBoxDialog();
		void appendText(QString text);
		
	private:
        /** Text view box dialog in pointer. */
		Ui::TextViewBoxDialog *ui;
};

}

#endif // TEXTVIEWBOXDIALOG_H
