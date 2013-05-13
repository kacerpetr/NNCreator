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

#ifndef PROJECTPARSER_H
#define PROJECTPARSER_H

#include "Project/Project.h"
#include <QObject>

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Project parser class.
 */
class ProjectParser : public QObject{
    Q_OBJECT

	public:
		static ProjectParser& get();
		ProjectData::Project* load(QString path) const;
		bool save(ProjectData::Project* project) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		ProjectParser();
        /** Makes imposible to call copy constructor by making it private. */
		ProjectParser(ProjectParser const&);
        /** Makes imposible to call operator= by making it private. */
		void operator=(ProjectParser const&);
};

}

#endif // PROJECTPARSER_H
