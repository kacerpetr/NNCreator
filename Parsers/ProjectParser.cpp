#include "ProjectParser.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace Parsers{

ProjectParser::ProjectParser(){}

ProjectParser& ProjectParser::get(){
	static ProjectParser instance;
	return instance;
}

Project::Project* ProjectParser::load(QString path) const{
	Project::Project* prj = new Project::Project();
	prj->setPath(path);
	prj->setName("blabla");
	prj->createModel("sdfsd",Project::DatasetEdit);
	prj->createModel("jkjj",Project::DatasetEdit);
	return prj;
}

bool ProjectParser::save(Project::Project* project) const{
	QFile file(project->getPath() + "/" + project->getName() + "/project.prj");
	bool succ = file.open(QIODevice::WriteOnly);
	if(!succ) return false;

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
