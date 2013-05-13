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

#include "OpenedListItem.h"

namespace Application{

/**
 * Class constructor.
 */
OpenedListItem::OpenedListItem() : mdl(NULL){}

/**
 * Sets model pointer and item icon.
 */
void OpenedListItem::setModel(BaseModel* model){
	Q_ASSERT(model != NULL);
	mdl = model;

	QString name = mdl->name();
	if(!mdl->isSaved()) name += "*";
	setText(name);

	switch(mdl->type()){
		case DatasetEdit:
			setIcon(QIcon(":datasetIcon32"));
			break;
		case TopologyEdit:
			setIcon(QIcon(":topologyIcon32"));
			break;
		case LearningConfig:
			setIcon(QIcon(":learningIcon32"));
			break;
		case DatasetTest:
			setIcon(QIcon(":datasetTestIcon32"));
			break;
		case GraphTest:
			setIcon(QIcon(":testingIcon32"));
			break;
	}
}

/**
 * Returns stored model pointer.
 */
BaseModel* OpenedListItem::model(){
	return mdl;
}


}
