#include "ProjectParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>
#include <QDebug>

namespace Parser{

ProjectParser::ProjectParser(){}

/**
 * Returns reference to parser.
 */
ProjectParser& ProjectParser::get(){
	static ProjectParser instance;
	return instance;
}

/**
 * Loads model from xml file.
 */
ProjectData::Project* ProjectParser::load(QString path) const{
	ProjectData::Project* prj = new ProjectData::Project();	

	QFileInfo info(path);
	info = QFileInfo(info.path() + "/../");
	prj->setPath(info.canonicalFilePath());

	QFile file(path);
	bool succ = file.open(QIODevice::ReadOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open project"));
        msgBox.setText(tr("Project file can't be opened !!!"));
        msgBox.setInformativeText(tr("Check if file exists or program have permission to read it."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		delete prj;
		return NULL;
	}

	QXmlStreamReader rd;
	rd.setDevice(&file);

	int state = 0;
	QString elemName;
	QString mdlPath;
	ModelType mdlType;

	//reading
	while (!rd.atEnd()) {
		switch(rd.readNext()){
			case QXmlStreamReader::StartElement:
				elemName = rd.name().toString();
				if(rd.name() == "header") state = 1; else
				if(rd.name() == "file") state = 2;
				break;

			case QXmlStreamReader::EndElement:
				elemName = "";
				if(rd.name() == "header"){
					state = 0;
				}
				else if(rd.name() == "file"){
					prj->openModel(mdlPath, mdlType);
					state = 0;
				}
				break;

			case QXmlStreamReader::Characters:
				switch(state){
					case 1:
						if(elemName == "name") prj->setName(rd.text().toString());
						break;

					case 2:
						if(elemName == "path") mdlPath = rd.text().toString(); else
						if(elemName == "type") mdlType = (ModelType)rd.text().toString().toInt();
				}
				break;

			default:
				break;
		}
	}

	//error handling
	if(rd.hasError()){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Open project"));
        msgBox.setText(tr("Error parsing project file !!!"));
		msgBox.setInformativeText(rd.errorString());
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		file.close();
		delete prj;
		return NULL;
	}

	file.close();
	return prj;
}

/**
 * Saves model to xml file.
 */
bool ProjectParser::save(ProjectData::Project* project) const{
	bool succ = true;

	QDir dir(project->path());
	if(!dir.exists(project->getName()))
		succ = dir.mkdir(project->getName());

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save project"));
        msgBox.setText(tr("Project folder can't be created !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}


	QFile file(project->path() + "/" + project->getName() + "/" + "/project.xml");
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Save project"));
        msgBox.setText(tr("Project file can't be saved !!!"));
        msgBox.setInformativeText(tr("Check if given path exists or program have permission to read and write."));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QXmlStreamWriter wr(&file);
	wr.setAutoFormatting(true);
	wr.writeStartDocument();
	wr.writeStartElement("project");
	wr.writeStartElement("header");
	wr.writeTextElement("name", project->getName());
	wr.writeEndElement();

	for(int i = 0; i < project->count(); i++){
		wr.writeStartElement("file");
		wr.writeTextElement("path", project->getModel(i)->relPathName());
		wr.writeTextElement("type", QString::number((int)project->getModel(i)->type()));
		wr.writeEndElement();
	}

	wr.writeEndElement();

	file.close();
	return true;
}

}
