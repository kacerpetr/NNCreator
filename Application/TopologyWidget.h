#ifndef TOPOLOGYWIDGET_H
#define TOPOLOGYWIDGET_H

#include <QWidget>

namespace Ui{
	class TopologyWidget;
}

class TopologyWidget : public QWidget{
	Q_OBJECT

	public:
		explicit TopologyWidget(QWidget *parent = 0);
		~TopologyWidget();

	private:
		Ui::TopologyWidget *ui;
};

#endif // TOPOLOGYWIDGET_H
