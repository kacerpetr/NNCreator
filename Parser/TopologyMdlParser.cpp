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

#include "TopologyMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include "Util/Globaldef.h"

namespace Parser{

TopologyMdlParser::TopologyMdlParser(){}

/**
 * Returns reference to parser.
 */
TopologyMdlParser& TopologyMdlParser::get(){
	static TopologyMdlParser instance;
	return instance;
}

/**
 * Loads model from xml file.
 */
TopologyEditModel* TopologyMdlParser::load(QString path) const{
	TopologyEditModel* mdl = new TopologyEditModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open neural network"));
        msgBox.setText(tr("Neural network file can't be opened !!!"));
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
	int layer = 0;
	int neuron = 0;
	int weight = 0;

	//reading
	while (!rd.atEnd()){
		switch(rd.readNext()){
			case QXmlStreamReader::StartElement:
				elemName = rd.name().toString();
				if(rd.name() == "network"){
					int layerCount = rd.attributes().at(0).value().toString().toInt();
					for(int i = 1; i < layerCount; i++) mdl->appendLayer();
				}
				if(rd.name() == "header"){
					state = 1;
				}
				else if(rd.name() == "neuron"){
					state = 2;
					weight = 0;
				}
				else if(rd.name() == "layer"){
					int neuronCount = rd.attributes().at(0).value().toString().toInt();
					mdl->setNeuronCount(layer, neuronCount);
					neuron = 0;
				}
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header"){
					state = 0;
				}
				else if(rd.name() == "neuron"){
					neuron++;
					state = 0;
				}
				else if(rd.name() == "layer"){
					layer++;
				}
				else if(rd.name() == "weight"){
					weight++;
				}
				break;

			case QXmlStreamReader::Characters:
				if(elemName.isEmpty()) break;
				switch(state){
					case 1:
						if(elemName == "name") mdl->setName(rd.text().toString()); else
						if(elemName == "inputCount") mdl->setInputCount(rd.text().toString().toInt()); else
                        if(elemName == "trFcn") mdl->setTransferFunction((TransferFcn)rd.text().toString().toInt()); else
						if(elemName == "biasSeed") mdl->setBiasSeed(rd.text().toString().toInt()); else
						if(elemName == "biasMax") mdl->setBiasMax(rd.text().toString().toDouble()); else
						if(elemName == "biasMin") mdl->setBiasMin(rd.text().toString().toDouble()); else
						if(elemName == "weightSeed") mdl->setWeightSeed(rd.text().toString().toInt()); else
						if(elemName == "weightMax") mdl->setWeightMax(rd.text().toString().toDouble()); else
						if(elemName == "weightMin") mdl->setWeightMin(rd.text().toString().toDouble()); else
                        if(elemName == "slopeSeed") mdl->setSlopeSeed(rd.text().toString().toInt()); else
                        if(elemName == "slopeMax") mdl->setSlopeMax(rd.text().toString().toDouble()); else
                        if(elemName == "slopeMin") mdl->setSlopeMin(rd.text().toString().toDouble()); else
						if(elemName == "selectedLayer") mdl->setSelectedLayer(rd.text().toString().toInt());
						break;

					case 2:
						if(elemName == "trFcn") (*mdl)[layer][neuron].setTrFcn((TransferFcn)rd.text().toString().toInt()); else
						if(elemName == "bias") (*mdl)[layer][neuron].setBias(rd.text().toString().toDouble()); else
                        if(elemName == "slope") (*mdl)[layer][neuron].setSlope(rd.text().toString().toDouble()); else
						if(elemName == "weight") (*mdl)[layer][neuron][weight] = rd.text().toString().toDouble();
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open neural network"));
        msgBox.setText(tr("Error parsing neural network file !!!"));
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
bool TopologyMdlParser::save(TopologyEditModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save output graph"));
        msgBox.setText(tr("Neural network folder can't be created !!!"));
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
        msgBox.setText(tr("Neural network file can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QXmlStreamWriter wr(&file);
	wr.setAutoFormatting(true);
	wr.writeStartDocument();
	wr.writeStartElement("network");
	wr.writeAttribute("layerCount", QString::number(mdl->layerCount()));

	wr.writeStartElement("header");
	wr.writeTextElement("name", mdl->name());
	wr.writeTextElement("inputCount", QString::number(mdl->inputCount()));
    wr.writeTextElement("trFcn", QString::number(mdl->transferFunction()));
    wr.writeTextElement("weightSeed", QString::number(mdl->weightSeed()));
    wr.writeTextElement("weightMax", QString::number(mdl->weightMax()));
    wr.writeTextElement("weightMin", QString::number(mdl->weightMin()));
	wr.writeTextElement("biasSeed", QString::number(mdl->biasSeed()));
	wr.writeTextElement("biasMax", QString::number(mdl->biasMax()));
	wr.writeTextElement("biasMin", QString::number(mdl->biasMin()));
    wr.writeTextElement("slopeSeed", QString::number(mdl->slopeSeed()));
    wr.writeTextElement("slopeMax", QString::number(mdl->slopeMax()));
    wr.writeTextElement("slopeMin", QString::number(mdl->slopeMin()));
	wr.writeTextElement("selectedLayer", QString::number(mdl->selectedLayer()));
	wr.writeEndElement();

	for(int i = 0; i < mdl->layerCount(); i++){
		wr.writeStartElement("layer");
		wr.writeAttribute("neuronCount", QString::number(mdl->neuronCount(i)));
		for(int j = 0; j < mdl->neuronCount(i); j++){
			wr.writeStartElement("neuron");
			wr.writeAttribute("weightCount", QString::number((*mdl)[i][j].weightCount()));
			wr.writeTextElement("trFcn", QString::number((*mdl)[i][j].trFcn()));
			wr.writeTextElement("bias", QString::number((*mdl)[i][j].bias()));
            wr.writeTextElement("slope", QString::number((*mdl)[i][j].slope()));
			for(int k = 0; k < (*mdl)[i][j].weightCount(); k++){
				wr.writeTextElement("weight", QString::number((*mdl)[i][j][k]));
			}
			wr.writeEndElement();
		}
		wr.writeEndElement();
	}

	wr.writeEndElement();
	file.close();
	return true;
}

}
