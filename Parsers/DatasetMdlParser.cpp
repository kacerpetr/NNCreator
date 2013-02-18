#include "DatasetMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

namespace Parsers{

DatasetMdlParser::DatasetMdlParser(){}

DatasetMdlParser& DatasetMdlParser::get(){
	static DatasetMdlParser instance;
	return instance;
}

DatasetEditModel* DatasetMdlParser::load(QString path) const{
	DatasetEditModel* mdl = new DatasetEditModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Open dataset");
		msgBox.setText("Dataset file can't be opened !!!");
		msgBox.setInformativeText("Check if file exists or program have permission to read it.");
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
						if(elemName == "input") mdl->getDataset()->setInput(pattern, input, rd.text().toString().toDouble()); else
						if(elemName == "output") mdl->getDataset()->setOutput(pattern, output, rd.text().toString().toDouble());
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Open dataset");
		msgBox.setText("Error parsing dataset file !!!");
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

bool DatasetMdlParser::save(DatasetEditModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save dataset");
		msgBox.setText("Dataset folder can't be created !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QFile file(mdl->projectPath() + "/" + mdl->path());
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save dataset");
		msgBox.setText("Dataset file can't be saved !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
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
	wr.writeTextElement("inputCount", QString::number(mdl->inputCount()));
	wr.writeTextElement("outputCount", QString::number(mdl->outputCount()));
	wr.writeEndElement();

	for(int i = 0; i < mdl->patternCount(); i++){
		wr.writeStartElement("pattern");

		for(int j = 0; j < mdl->inputCount(); j++){
			if(mdl->getDataset()->isInputNull(i,j))
				wr.writeEmptyElement("input");
			else
				wr.writeTextElement("input", QString::number(mdl->getDataset()->input(i,j)));
		}

		for(int j = 0; j < mdl->outputCount(); j++){
			if(mdl->getDataset()->isOutputNull(i,j))
				wr.writeEmptyElement("output");
			else
				wr.writeTextElement("output", QString::number(mdl->getDataset()->output(i,j)));
		}

		wr.writeEndElement();
	}

	wr.writeEndElement();
	file.close();
	return true;
}

}
