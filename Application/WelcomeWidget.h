#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QToolButton>
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

	private slots:
		void newBtnPressed();
		void openBtnPressed();
		void slotOnePressed();
		void slotTwoPressed();
		void slotThreePressed();
		void slotFourPressed();
		void slotFivePressed();

	signals:
		void newProject();
		void openProject();
		void openRecent(QString path);

	private:
		Ui::WelcomeWidget *ui;
};

}

#endif // WELCOME_H
