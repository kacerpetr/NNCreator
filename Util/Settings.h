#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>

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
        QMap<QString,QString> allData();
        void saveData(const QMap<QString,QString>& map);

        //recent project management
		QList<TRecentProject> recentProject();
		void registerProject(QString name, QString path);
		void unregisterProject(QString pathName);
        int maxRecPrjCount();

        //setting value getters
        QString language();
        int outPlot1DRes();
        int outPlot2DResX();
        int outPlot2DResY();
        int outPlot3DResX();
        int outPlot3DResY();
        int outPlot3DResZ();
        int classifDiagResX();
        int classifDiagResY();

	signals:
		void recentChanged();

	private:
		Settings();
		Settings(Settings const&);
		void operator=(Settings const&);
        QVariant readKey(QString key, QString defaultValue);

	private:
		static Settings* instance;
		QString orgName;
		QString appName;
		int maxRecPrjCnt;
};

}

#endif // SETTINGS_H
