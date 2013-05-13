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

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
	class NewProjectDialog;
}

/**
 * Contains dialog classes.
 */
namespace Dialog{

/**
 * New project dialog class.
 */
class NewProjectDialog : public QDialog{
	Q_OBJECT
		
	public:
        NewProjectDialog(QWidget *parent = 0);
		~NewProjectDialog();
		bool isConfirmed();
		QString getPath();
		QString getName();

    private:
        QString checkPath();

	public slots:
		void browse();
		void ok();

	private:
        /** New project dialog ui pointer. */
		Ui::NewProjectDialog *ui;
        /** True if dialog is closed by ok button. */
		bool confirmed;
};

}

#endif // NEWPROJECTDIALOG_H
