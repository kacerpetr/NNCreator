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

#ifndef OPENEDLISTITEM_H
#define OPENEDLISTITEM_H

#include <QListWidgetItem>
#include "Project/BaseModel.h"
using namespace ProjectData;

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * ListWidget item used for list of opened items.
 */
class OpenedListItem : public QListWidgetItem{
	public:
		OpenedListItem();
		void setModel(BaseModel* model);
		BaseModel* model();

	private:
        /** Model pointer. */
		BaseModel* mdl;
};

}

#endif // OPENEDLISTITEM_H
