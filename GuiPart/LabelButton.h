#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QLabel>
#include <QMouseEvent>

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Button based on QLabel that looks like html link.
 */
class LabelButton : public QLabel{
	Q_OBJECT

	public:
		LabelButton(QWidget *parent = 0);

	signals:
        /** Emmited when label text pressed. */
		void pressed();
        /** Emmited when label text pressed. */
		void pressed(LabelButton*);

	private:
		virtual void mousePressEvent(QMouseEvent * event);
		virtual void enterEvent(QEvent * event);
		virtual void leaveEvent(QEvent * event);
};

}

#endif // LABELBUTTON_H
