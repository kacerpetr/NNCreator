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
