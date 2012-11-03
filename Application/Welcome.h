#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <QToolButton>

namespace Ui{
	class Welcome;
}

class Welcome : public QWidget{
	Q_OBJECT

	public:
		explicit Welcome(QWidget *parent = 0);
		~Welcome();
		QToolButton* getNewProjectButton();

	private:
		Ui::Welcome *ui;
};

#endif // WELCOME_H
