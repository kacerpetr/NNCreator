#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QToolButton>

namespace Ui{
	class WelcomeWidget;
}

class WelcomeWidget : public QWidget{
	Q_OBJECT

	public:
		explicit WelcomeWidget(QWidget *parent = 0);
		~WelcomeWidget();
		QToolButton* getNewProjectButton();

	private:
		Ui::WelcomeWidget *ui;
};

#endif // WELCOME_H
