#include "LrnConfMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>

namespace Parser{

LrnConfMdlParser::LrnConfMdlParser(){}

LrnConfMdlParser& LrnConfMdlParser::get(){
	static LrnConfMdlParser instance;
	return instance;
}

LearningConfigModel* LrnConfMdlParser::load(QString path) const{
	LearningConfigModel* mdl = new LearningConfigModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Open learning configuration");
		msgBox.setText("Learning configuration file can't be opened !!!");
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

	//reading
	while (!rd.atEnd()) {
		switch(rd.readNext()){
			case QXmlStreamReader::StartElement:
				elemName = rd.name().toString();
				if(rd.name() == "header")state = 1;	else
				if(rd.name() == "configuration") state = 2;
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header") state = 0; else
				if(rd.name() == "pattern") state = 0;
				break;

			case QXmlStreamReader::Characters:
				switch(state){
					case 1:
						if(elemName == "name") mdl->setName(rd.text().toString());
						break;

					case 2:
						if(elemName == "dataset") mdl->setDatasetName(rd.text().toString()); else
						if(elemName == "network") mdl->setNetworkName(rd.text().toString()); else
						if(elemName == "lrnCoef") mdl->setLrnCoef(rd.text().toString().toDouble()); else
						if(elemName == "maxIter") mdl->setMaxIter(rd.text().toString().toDouble()); else
						if(elemName == "maxErr") mdl->setMaxErr(rd.text().toString().toDouble()); else
						if(elemName == "maxTime") mdl->setMaxTime(rd.text().toString().toDouble());
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Open learning configuration");
		msgBox.setText("Error parsing learning configuration file !!!");
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

bool LrnConfMdlParser::save(LearningConfigModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save learning configuration");
		msgBox.setText("Learning configuration folder can't be created !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QFile file(mdl->projectPath() + "/" + mdl->path());
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save output graph");
		msgBox.setText("Learning configuration file can't be created !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QXmlStreamWriter wr(&file);
	wr.setAutoFormatting(true);
	wr.writeStartDocument();
	wr.writeStartElement("learningConfiguration");

	wr.writeStartElement("header");
	wr.writeTextElement("name", mdl->name());
	wr.writeEndElement();

	wr.writeStartElement("configuration");
	wr.writeTextElement("dataset", mdl->datasetName());
	wr.writeTextElement("network", mdl->networkName());
	wr.writeTextElement("lrnCoef", QString::number(mdl->lrnCoef()));
	wr.writeTextElement("maxIter", QString::number(mdl->maxIter()));
	wr.writeTextElement("maxErr", QString::number(mdl->maxErr()));
	wr.writeTextElement("maxTime", QString::number(mdl->maxTime()));
	wr.writeEndElement();

	wr.writeEndElement();
	file.close();
	return true;
}

}
