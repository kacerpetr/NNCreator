#ifndef LABELBUTTON_H
#define LABELBUTTON_H

#include <QLabel>
#include <QMouseEvent>

namespace Application{

class LabelButton : public QLabel{
	Q_OBJECT

	public:
		LabelButton(QWidget *parent = 0);

	signals:
		void pressed();
		void pressed(LabelButton*);

	private:
		virtual void mousePressEvent(QMouseEvent * event);
		virtual void enterEvent(QEvent * event);
		virtual void leaveEvent(QEvent * event);
};

}

#endif // LABELBUTTON_H
