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

#include "GraphTestMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>

namespace Parser{

GraphTestMdlParser::GraphTestMdlParser(){}

/**
 * Returns reference to parser.
 */
GraphTestMdlParser& GraphTestMdlParser::get(){
	static GraphTestMdlParser instance;
	return instance;
}

/**
 * Loads model from xml file.
 */
GraphTestModel* GraphTestMdlParser::load(QString path) const{
	GraphTestModel* mdl = new GraphTestModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open output graph"));
        msgBox.setText(tr("Output graph file can't be opened !!!"));
        msgBox.setInformativeText(tr("Check if file exists or program have permission to read it."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		delete mdl;
		return NULL;
	}

	QXmlStreamReader rd;
	rd.setDevice(&file);

	QString elemName;
	int state = 0;

	//reading
	while (!rd.atEnd()) {
		switch(rd.readNext()){
			case QXmlStreamReader::StartElement:
				elemName = rd.name().toString();
				if(rd.name() == "header"){
					state = 1;
				}
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header"){
					state = 0;
				}
				break;

			case QXmlStreamReader::Characters:
				switch(state){
					case 1:
                        if(elemName == "name") mdl->setName(rd.text().toString()); else
                        if(elemName == "network") mdl->selectNetwork(rd.text().toString()); else
                        if(elemName == "dataset") mdl->selectDataset(rd.text().toString()); else
                        if(elemName == "output") mdl->setOutput(rd.text().toString().toInt());
						break;
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open output graph"));
        msgBox.setText(tr("Error parsing output graph file !!!"));
		msgBox.setInformativeText(rd.errorString());
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		file.close();
		delete mdl;
		return NULL;
	}

	file.close();
	return mdl;
}

/**
 * Saves model to xml file.
 */
bool GraphTestMdlParser::save(GraphTestModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save output graph"));
        msgBox.setText(tr("Output graph folder can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QFile file(mdl->pathName());
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save output graph"));
        msgBox.setText(tr("Ouptut graph file can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QXmlStreamWriter wr(&file);
	wr.setAutoFormatting(true);
	wr.writeStartDocument();
	wr.writeStartElement("outputGraph");

	wr.writeStartElement("header");
	wr.writeTextElement("name", mdl->name());
    wr.writeTextElement("network", mdl->selectedNetworkName());
    wr.writeTextElement("dataset", mdl->selectedDatasetName());
    wr.writeTextElement("output", QString::number(mdl->output()));
    wr.writeEndElement();

	wr.writeEndElement();
	file.close();
	return true;
}

}
