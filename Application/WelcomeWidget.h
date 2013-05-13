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

#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QList>
#include "GuiPart/LabelButton.h"
namespace Ui{class WelcomeWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The WelcomeWidget class.
 */
class WelcomeWidget : public QWidget{
	Q_OBJECT

	public:
        WelcomeWidget(QWidget *parent = 0);
		~WelcomeWidget();

	private:
		void createRecentBtn();
		void removeRecentBtn();

	private slots:
		void newButtonPressed();
		void openButtonPressed();
		void openRecentPressed(LabelButton* button);
		void recentChanged();

	signals:
        /** Emited when new project button is pressed. */
        void newProject();
        /** Emited when open project button is pressed. */
        void openProject();
        /** Emited when recent project button is pressed. */
        void openRecent(QString path);

	private:
		/** Welcome widget ui pointer. */
		Ui::WelcomeWidget *ui;
		/** New project button pointer. */
		LabelButton* newBtn;
        /** Open project button pointer. */
		LabelButton* openBtn;
		/** List of recent project buttons. */
		QList<LabelButton*> btn;
};

}

#endif // WELCOME_H
