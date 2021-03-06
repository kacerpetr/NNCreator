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

#ifndef DATASETEDITWIDGET_H
#define DATASETEDITWIDGET_H

#include <QMenu>
#include <QWidget>
#include "Project/DatasetEditModel.h"

using namespace ProjectData;
namespace Ui{class DatasetEditWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The DatasetEditWidget class.
 */
class DatasetEditWidget : public QWidget{
	Q_OBJECT
		
	public:
        DatasetEditWidget(QWidget *parent = 0);
		~DatasetEditWidget();
		void setModel(DatasetEditModel* model);
		bool hasModel();

	private slots:
		void modelChanged(ChangeType type);
		void closeBtnPressed();
		void showContextMenu();
		void changePatternCount(int value);
		void changeInputCount(int value);
		void changeOutputCount(int value);
		void copyCell();
		void cutCell();
		void pasteCell();
		void deleteCell();

	signals:
        /** Emmited when close button is pressed. */
		void closePressed(BaseModel*);

	private:
        /** Autogenerated stuff, user interface class pointer. */
        Ui::DatasetEditWidget *ui;
        /** Current model pointer. */
		ProjectData::DatasetEditModel* model;
        /** Context menu pointer. */
		QMenu* contextMenu;
};

}

#endif // DATASETEDITWIDGET_H
