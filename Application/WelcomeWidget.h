#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QList>
#include "LabelButton.h"

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
		void newProject();
		void openProject();
		void openRecent(QString path);

	private:
		Ui::WelcomeWidget *ui;
		LabelButton* newBtn;
		LabelButton* openBtn;
		QList<LabelButton*> btn;
};

}

#endif // WELCOME_H
