#ifndef LRNGRAPHWIDGET_H
#define LRNGRAPHWIDGET_H

#include "qwt/qwt_plot.h"

namespace Application{

class LrnGraphWidget : public QwtPlot{
	Q_OBJECT

	public:
		explicit LrnGraphWidget(QWidget *parent = 0);
		
	signals:
		
	public slots:
		
};

}

#endif // LRNGRAPHWIDGET_H
