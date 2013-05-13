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

#include "DatasetMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

namespace Parser{

DatasetMdlParser::DatasetMdlParser(){}

/**
 * Returns reference to parser.
 */
DatasetMdlParser& DatasetMdlParser::get(){
	static DatasetMdlParser instance;
	return instance;
}

/**
 * Loads model from xml file.
 */
DatasetEditModel* DatasetMdlParser::load(QString path) const{
	DatasetEditModel* mdl = new DatasetEditModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open dataset"));
        msgBox.setText(tr("Dataset file can't be opened !!!"));
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
	int pattern = 0;
	int input = -1;
	int output = -1;

	//reading
	while (!rd.atEnd()) {
		switch(rd.readNext()){
			case QXmlStreamReader::StartElement:
				elemName = rd.name().toString();
				if(rd.name() == "header"){
					state = 1;
				}
				else if(rd.name() == "pattern"){
					state = 2;
					mdl->setPatternCount(pattern+1);
					input = -1;
					output = -1;
				}
				else if(rd.name() == "input") input++;
				else if(rd.name() == "output") output++;
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header"){
					state = 0;
				}
				else if(rd.name() == "pattern"){
					pattern++;
					state = 0;
				}
				break;

			case QXmlStreamReader::Characters:
				switch(state){
					case 1:
						if(elemName == "name") mdl->setName(rd.text().toString());
						if(elemName == "inputCount") mdl->setInputCount(rd.text().toString().toInt());
						if(elemName == "outputCount") mdl->setOutputCount(rd.text().toString().toInt());
						break;

					case 2:
						if(elemName == "input") mdl->setInput(pattern, input, rd.text().toString().toDouble()); else
						if(elemName == "output") mdl->setOutput(pattern, output, rd.text().toString().toDouble());
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open dataset"));
        msgBox.setText(tr("Error parsing dataset file !!!"));
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
bool DatasetMdlParser::save(DatasetEditModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save dataset"));
        msgBox.setText(tr("Dataset folder can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QFile file(mdl->pathName());
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save dataset"));
        msgBox.setText(tr("Dataset file can't be saved !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QXmlStreamWriter wr(&file);
	wr.setAutoFormatting(true);
	wr.writeStartDocument();
	wr.writeStartElement("dataset");

	wr.writeStartElement("header");
	wr.writeTextElement("name", mdl->name());
    wr.writeTextElement("inputCount", QString::number(mdl->minInputCount()));
    wr.writeTextElement("outputCount", QString::number(mdl->minOutputCount()));
	wr.writeEndElement();

    for(int i = 0; i < mdl->minPatternCount(); i++){
		wr.writeStartElement("pattern");

        for(int j = 0; j < mdl->minInputCount(); j++){
			if(mdl->isInputNull(i,j))
				wr.writeEmptyElement("input");
			else
				wr.writeTextElement("input", QString::number(mdl->input(i,j)));
		}

        for(int j = 0; j < mdl->minOutputCount(); j++){
			if(mdl->isOutputNull(i,j))
				wr.writeEmptyElement("output");
			else
				wr.writeTextElement("output", QString::number(mdl->output(i,j)));
		}

		wr.writeEndElement();
	}

	wr.writeEndElement();
	file.close();
	return true;
}

}
