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

#ifndef TOPOLOGYMDLPARSER_H
#define TOPOLOGYMDLPARSER_H

#include <QXmlStreamReader>
#include "Project/TopologyEditModel.h"
#include <QObject>
using namespace ProjectData;

/**
 * Contains classes to load and save project data to xml files.
 */
namespace Parser{

/**
 * Topology model parser class.
 */
class TopologyMdlParser : public QObject{
    Q_OBJECT

	public:
		static TopologyMdlParser& get();
		TopologyEditModel* load(QString path) const;
		bool save(TopologyEditModel* mdl) const;

	private:
        /** Makes imposible to call class constructor by making it private. */
		TopologyMdlParser();
        /** Makes imposible to call copy constructor by making it private. */
        TopologyMdlParser(TopologyMdlParser const&);
        /** Makes imposible to call operator= by making it private. */
        void operator=(TopologyMdlParser const&);
};

}

#endif // TOPOLOGYMDLPARSER_H
