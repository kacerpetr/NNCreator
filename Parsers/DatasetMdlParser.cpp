#include "DatasetMdlParser.h"

namespace Parsers{

DatasetMdlParser::DatasetMdlParser(){}

DatasetMdlParser& DatasetMdlParser::get(){
	static DatasetMdlParser instance;
	return instance;
}

DatasetEditModel* DatasetMdlParser::load(QString path) const{

}

bool DatasetMdlParser::save(DatasetEditModel* project) const{
	/*bool succ = false;

	QDir dir(project->getPath());
	if(!dir.exists(project->getName()))
		succ = dir.mkdir(project->getName());

	if(!succ){
		QMessageBox msgBox;
		msgBox.setWindowTitle("Save dataset");
		msgBox.setText("Dataset folder can't be created !!!");
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
	}*/
}

}
