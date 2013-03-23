#include "Settings.h"
#include <QSettings>
#include <QDebug>
#include <QStringList>

namespace Util{

bool operator==(TRecentProject a, TRecentProject b){
	return a.name == b.name && a.path == b.path;
}

Settings* Settings::instance = NULL;

Settings::Settings() : QObject(),
	orgName("NeuralNetCreator"),
	appName("NeuralNetCreator"),
	maxRecPrjCnt(10)
{}

Settings::~Settings(){
	delete instance;
}

Settings& Settings::get(){
	if(instance == NULL)
		instance = new Settings();

	return *instance;
}

Settings* Settings::getPointer(){
	if(instance == NULL)
		instance = new Settings();

	return instance;
}

QList<TRecentProject> Settings::recentProject(){
	QSettings settings(orgName, appName);
	QList<TRecentProject> recPrj;
	int size = settings.beginReadArray("recentProjects");

	for(int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);

		QString prjName = settings.value("name").toString();
		QString prjPath = settings.value("path").toString();

		if(!prjName.isEmpty() && !prjPath.isEmpty()){
			TRecentProject prj;
			prj.name = prjName;
			prj.path = prjPath;
			recPrj.append(prj);
		}
	}

	return recPrj;
}

void Settings::registerProject(QString name, QString path){
	Q_ASSERT(!name.isEmpty() && !path.isEmpty());

	//provides persistent platform-independent application settings
	QSettings settings(orgName, appName);

	QList<TRecentProject> recPrj;
	int size = settings.beginReadArray("recentProjects");

	//reading of informations about recent projects
	for(int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);

		//informations about recent project
		QString prjName = settings.value("name").toString();
		QString prjPath = settings.value("path").toString();

		//adds project to array
		if(!prjName.isEmpty() && !prjPath.isEmpty()){
			TRecentProject prj;
			prj.name = prjName;
			prj.path = prjPath;
			recPrj.append(prj);
		}

		//removes item
		settings.remove("");
	}

	//end of array reading and deleting
	settings.endArray();

	//prepends new recent project
	TRecentProject prj;
	prj.name = name;
	prj.path = path;
	recPrj.removeAll(prj);
	recPrj.prepend(prj);

	//shorten array to its maximum predefined length - maxRecPrjCount
	if(recPrj.length() > maxRecPrjCnt){
		for(int i = 0; i < recPrj.length() - maxRecPrjCnt; i++){
			recPrj.removeLast();
		}
	}

	//writes modified array
	settings.beginWriteArray("recentProjects");
	for (int i = 0; i < recPrj.length(); i++) {
		settings.setArrayIndex(i);
		settings.setValue("name", recPrj[i].name);
		settings.setValue("path", recPrj[i].path);
	}
	settings.endArray();

	//tells that recent project list was changed
	emit recentChanged();
}

void Settings::unregisterProject(QString pathName){
	Q_ASSERT(!pathName.isNull());

	//provides persistent platform-independent application settings
	QSettings settings(orgName, appName);

	QList<TRecentProject> recPrj;
	int size = settings.beginReadArray("recentProjects");

	//reading of informations about recent projects
	for(int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);

		//informations about recent project
		QString prjName = settings.value("name").toString();
		QString prjPath = settings.value("path").toString();

		//adds project to array
		if(!prjName.isEmpty() && !prjPath.isEmpty()){
			TRecentProject prj;
			prj.name = prjName;
			prj.path = prjPath;
			recPrj.append(prj);
		}

		//removes item
		settings.remove("");
	}

	//end of array reading and deleting
	settings.endArray();

	//finds and removes given not existing project
	for(int i = 0; i < recPrj.length(); i++){
		if(recPrj[i].path == pathName)
			recPrj.removeAt(i);
	}

	//writes modified array
	settings.beginWriteArray("recentProjects");
	for (int i = 0; i < recPrj.length(); i++) {
		settings.setArrayIndex(i);
		settings.setValue("name", recPrj[i].name);
		settings.setValue("path", recPrj[i].path);
	}
	settings.endArray();

	//tells that recent project list was changed
	emit recentChanged();
}

int Settings::maxRecPrjCount(){
	return maxRecPrjCnt;
}

QMap<QString,QString> Settings::allData(){
    QSettings settings(orgName, appName);
    QStringList keys = settings.allKeys();

    QMap<QString,QString> map;
    for(int i = 0; i < keys.length(); i++){
        map.insert(keys[i], settings.value(keys[i]).toString());
    }

    return map;
}

void Settings::saveData(const QMap<QString,QString>& map){
    QSettings settings(orgName, appName);
    QList<QString> keys = map.keys();

    for(int i = 0; i < keys.length(); i++){
        if(settings.value(keys[i]) != map.value(keys[i])){
            settings.setValue(keys[i], map.value(keys[i]));
        }
    }
}

}
