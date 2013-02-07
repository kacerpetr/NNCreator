#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
namespace Ui{class HelpWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The HelpWidget class.
 */
class HelpWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit HelpWidget(QWidget *parent = 0);
		~HelpWidget();
		
	private:
		Ui::HelpWidget *ui;
};

}

#endif // HELPWIDGET_H
