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
		/** Creates and connects widget buttons. */
		WelcomeWidget(QWidget *parent = 0);
		/** Class destructor. */
		~WelcomeWidget();

	private:
		/** Creates buttons to open recent projects. */
		void createRecentBtn();
		/** Removes recent project buttons. */
		void removeRecentBtn();

	private slots:
		/** Emits newProject signal. */
		void newButtonPressed();
		/** Emits openProject signal. */
		void openButtonPressed();
		/** Emits openRecent signal. */
		void openRecentPressed(LabelButton* button);
		/** Recreates open recent project buttons. */
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
