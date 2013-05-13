/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QList>
#include <QMap>

/** Informations about recently opened project. */
typedef struct{
    QString name; /**< Name of recent project. */
    QString path; /**< Path to project file. */
} TRecentProject;

/** Operator used for comparing recent project informations. */
bool operator==(TRecentProject a, TRecentProject b);

/**
 * Settings management singleton class.
 */
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
        /** Emitted when recent project is registered or unregistered. */
		void recentChanged();

	private:
        /** Sets name of organization and application. */
        Settings();
        /** Disables copy constructor calls by making it private. */
        Settings(Settings const&);
        /** Disables copy constructor calls by making it private. */
        void operator=(Settings const&);
        /** Reads value of key and writes default value if key does not exist. */
        QVariant readKey(QString key, QString defaultValue);

	private:
        /** Singleton class instance. */
		static Settings* instance;
        /** Organization name. */
		QString orgName;
        /** Application name. */
		QString appName;
        /** Maximal count of recent projects. */
		int maxRecPrjCnt;
};

#endif // SETTINGS_H
