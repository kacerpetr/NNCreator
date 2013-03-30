#include "LrnConfMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

namespace Parser{

LrnConfMdlParser::LrnConfMdlParser(){}

/**
 * Returns reference to parser.
 */
LrnConfMdlParser& LrnConfMdlParser::get(){
	static LrnConfMdlParser instance;
	return instance;
}

/**
 * Loads model from xml file.
 */
LearningConfigModel* LrnConfMdlParser::load(QString path) const{
	LearningConfigModel* mdl = new LearningConfigModel();

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open learning configuration"));
        msgBox.setText(tr("Learning configuration file can't be opened !!!"));
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
				if(rd.name() == "header")state = 1;	else
                if(rd.name() == "configuration") state = 2; else
                if(rd.name() == "plot") state = 3;
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header") state = 0; else
                if(rd.name() == "pattern") state = 0; else
                if(rd.name() == "plot") state = 0;
				break;

			case QXmlStreamReader::Characters:
				switch(state){
					case 1:
						if(elemName == "name") mdl->setName(rd.text().toString());
						break;

					case 2:
						if(elemName == "dataset") mdl->selectDataset(rd.text().toString()); else
						if(elemName == "network") mdl->selectNetwork(rd.text().toString()); else
						if(elemName == "lrnCoef") mdl->setLrnCoef(rd.text().toString().toDouble()); else
						if(elemName == "maxIter") mdl->setMaxIter(rd.text().toString().toDouble()); else
						if(elemName == "maxErr") mdl->setMaxErr(rd.text().toString().toDouble()); else
						if(elemName == "maxTime") mdl->setMaxTime(rd.text().toString().toDouble());

                    case 3:
                        if(elemName == "plot") mdl->fillPlot(rd.text().toString());
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open learning configuration"));
        msgBox.setText(tr("Error parsing learning configuration file !!!"));
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
bool LrnConfMdlParser::save(LearningConfigModel* mdl) const{
	bool succ = true;

	QDir dir(mdl->projectPath());
	if(!dir.exists(mdl->folder()))
		succ = dir.mkdir(mdl->folder());

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save learning configuration"));
        msgBox.setText(tr("Learning configuration folder can't be created !!!"));
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
        msgBox.setText(tr("Learning configuration file can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
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
	wr.writeTextElement("dataset", mdl->selectedDatasetName());
	wr.writeTextElement("network", mdl->selectedNetworkName());
	wr.writeTextElement("lrnCoef", QString::number(mdl->lrnCoef()));
	wr.writeTextElement("maxIter", QString::number(mdl->maxIter()));
	wr.writeTextElement("maxErr", QString::number(mdl->maxErr()));
	wr.writeTextElement("maxTime", QString::number(mdl->maxTime()));
	wr.writeEndElement();

    wr.writeTextElement("plot", mdl->plot()->toString());

	wr.writeEndElement();
	file.close();
	return true;
}

}
