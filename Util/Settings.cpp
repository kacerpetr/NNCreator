#include "Settings.h"
#include <QSettings>
#include <QDebug>
#include <QStringList>
#include <QLocale>

/**
 * Operator used for comparing recent project informations.
 */
bool operator==(TRecentProject a, TRecentProject b){
	return a.name == b.name && a.path == b.path;
}

//inititalizes singleton instance to NULL
Settings* Settings::instance = NULL;

/**
 * Sets name of organization and application.
 */
Settings::Settings() : QObject(),
	orgName("NeuralNetCreator"),
	appName("NeuralNetCreator"),
	maxRecPrjCnt(10)
{}

/**
 * Class destructor.
 */
Settings::~Settings(){
	delete instance;
}

/**
 * Returns reference to class singleton instance.
 */
Settings& Settings::get(){
	if(instance == NULL)
		instance = new Settings();

	return *instance;
}

/**
 * Returns pointer to class singleton instance.
 */
Settings* Settings::getPointer(){
	if(instance == NULL)
		instance = new Settings();

	return instance;
}

/**
 * Returns list of recent projects.
 */
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

/**
 * Registers new project to recent project list.
 */
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

/**
 * Unegisters project from recent project list.
 */
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

/**
 * Returns maximal count of recent projects in list.
 */
int Settings::maxRecPrjCount(){
	return maxRecPrjCnt;
}

/**
 * Reads value of key and writes default value if key does not exist.
 */
QVariant Settings::readKey(QString key, QString defaultValue){
    QSettings settings(orgName, appName);

    if(settings.contains(key)){
        return settings.value(key);
    }
    else{
        settings.setValue(key, defaultValue);
        return settings.value(key);
    }
}

/**
 * Returns language file name or "default" for english.
 */
QString Settings::language(){
    QString defaultLang =  "default";
    QLocale loc = QLocale::system();
    if(loc.language() == QLocale::Czech)
        defaultLang = "lang_cs";
    return readKey("language", defaultLang).toString();
}

/**
 * Resolution of Plot1D in graph test (number of points).
 */
int Settings::outPlot1DRes(){
    return readKey("outPlot1DRes", "500").toInt();
}

/**
 * X axis resolution of Plot2D image.
 */
int Settings::outPlot2DResX(){
    return readKey("outPlot2DResX", "100").toInt();
}

/**
 * Y axis resolution of Plot2D image.
 */
int Settings::outPlot2DResY(){
    return readKey("outPlot2DResY", "100").toInt();
}

/**
 * X axis resolution of Plot3D images.
 */
int Settings::outPlot3DResX(){
    return readKey("outPlot3DResX", "30").toInt();
}

/**
 * Y axis resolution of Plot3D images.
 */
int Settings::outPlot3DResY(){
    return readKey("outPlot3DResY", "30").toInt();
}

/**
 * Number of Plot3D layyers.
 */
int Settings::outPlot3DResZ(){
    return readKey("outPlot3DResZ", "30").toInt();
}

/**
 * X axis resolution of classification diagram.
 */
int Settings::classifDiagResX(){
    return readKey("classifDiagResX", "100").toInt();
}

/**
 * Y axis resolution of classification diagram.
 */
int Settings::classifDiagResY(){
    return readKey("classifDiagResY", "100").toInt();
}

/**
 * Returns all settings as QMap.
 */
QMap<QString,QString> Settings::allData(){
    QSettings settings(orgName, appName);
    QStringList keys = settings.allKeys();

    QMap<QString,QString> map;
    for(int i = 0; i < keys.length(); i++){
        map.insert(keys[i], settings.value(keys[i]).toString());
    }

    return map;
}

/**
 * Saves changes of settings.
 */
void Settings::saveData(const QMap<QString,QString>& map){
    QSettings settings(orgName, appName);
    QList<QString> keys = map.keys();

    for(int i = 0; i < keys.length(); i++){
        if(settings.value(keys[i]) != map.value(keys[i])){
            if(map.value(keys[i]).isEmpty()){
                settings.remove(keys[i]);
            }else{
                settings.setValue(keys[i], map.value(keys[i]));
            }
        }
    }
}
