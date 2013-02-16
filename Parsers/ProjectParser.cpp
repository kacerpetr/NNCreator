#include "ProjectParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDir>

namespace Parsers{

ProjectParser::ProjectParser(){}

ProjectParser& ProjectParser::get(){
	static ProjectParser instance;
	return instance;
}

ProjectData::Project* ProjectParser::load(QString path) const{
	ProjectData::Project* prj = new ProjectData::Project();
	prj->setPath(path);
	prj->setName("blabla");
	prj->createModel("sdfsd",ProjectData::DatasetEdit);
	prj->createModel("jkjj",ProjectData::DatasetEdit);
	return prj;
}

bool ProjectParser::save(ProjectData::Project* project) const{
	bool succ = false;

	QDir dir(project->getPath());
	if(!dir.exists(project->getName()))
		succ = dir.mkdir(project->getName());

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save project");
		msgBox.setText("Project folder can't be created !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
		return false;
	}

	QFile file(project->getPath() + "/" + project->getName() + "/project.xml");
	succ = file.open(QIODevice::WriteOnly);

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save project");
		msgBox.setText("Project file can't be saved !!!");
		msgBox.setInformativeText("Check if given path exists or program have permission to read and write.");
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
	wr.writeStartElement("fileList");

	for(int i = 0; i < project->count(); i++){
		wr.writeStartElement("file");
		wr.writeTextElement("name", project->getModel(i)->name());
		wr.writeTextElement("path", project->getModel(i)->path());
		wr.writeTextElement("type", QString::number((int)project->getModel(i)->type()));
		wr.writeEndElement();
	}

	wr.writeEndElement();
	wr.writeEndElement();

	file.close();
	return true;
}

}
