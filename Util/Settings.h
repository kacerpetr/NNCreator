#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QList>

namespace Util{

typedef struct{
	QString name;
	QString path;
} TRecentProject;

bool operator==(TRecentProject a, TRecentProject b);

class Settings : public QObject{
	Q_OBJECT

	public:
		~Settings();
		static Settings& get();
		static Settings* getPointer();
		QList<TRecentProject> recentProject();
		void registerProject(QString name, QString path);
		int maxRecPrjCount();

	signals:
		void recentChanged();

	private:
		Settings();
		Settings(Settings const&);
		void operator=(Settings const&);

	private:
		static Settings* instance;
		QString orgName;
		QString appName;
		int maxRecPrjCnt;
};

}

#endif // SETTINGS_H
