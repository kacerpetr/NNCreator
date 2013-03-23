#include "GraphTestMdlParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>

namespace Parser{

GraphTestMdlParser::GraphTestMdlParser(){}

GraphTestMdlParser& GraphTestMdlParser::get(){
	static GraphTestMdlParser instance;
	return instance;
}

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
    wr.writeTextElement("output", QString::number(mdl->output()));
    wr.writeEndElement();

	wr.writeEndElement();
	file.close();
	return true;
}

}
