#ifndef NOMODELWIDGET_H
#define NOMODELWIDGET_H

#include <QWidget>
namespace Ui{class NoModelWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The NoModelWidget class.
 *
 * Widget is shown when left menu button is pressed and
 * no item from category of this button is opened.
 */
class NoModelWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit NoModelWidget(QWidget *parent = 0);
		~NoModelWidget();
		
	private:
		/** NoModelWidget ui pointer. */
		Ui::NoModelWidget *ui;
};

}

#endif // NOMODELWIDGET_H
