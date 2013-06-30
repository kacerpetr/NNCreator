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

#include <QApplication>
#include <QTranslator>
#include "Application/MainWindow.h"
#include "Util/Settings.h"

/**
 * Main function.
 */
int main(int argc, char *argv[]){
	//runs application
	QApplication a(argc, argv);

    Settings& sts = Settings::get();

    QTranslator trr(&a);
    trr.load(sts.language(), "./Translation");
    a.installTranslator(&trr);

	Application::MainWindow w;
	w.show();
	w.showMaximized();
	return a.exec();
}

