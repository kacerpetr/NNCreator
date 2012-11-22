#ifndef TOPOLOGYWIDGET_H
#define TOPOLOGYWIDGET_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include "LayerEditWidget.h"
#include "Project/NeuralNetworkModel.h"

namespace Ui{
	class TopologyWidget;
}

class TopologyWidget : public QWidget{
	Q_OBJECT

	public:
		explicit TopologyWidget(QWidget *parent = 0);
		~TopologyWidget();
		void setModel(NeuralNetworkModel* model);
		void createBasicLayers();
		bool hasModel();

	public slots:
		void appendInnerLayer();
		void removeLayer(int index);
		void widgetPressed(LayerEditWidget* widget);

	private:
		Ui::TopologyWidget *ui;
		QList<LayerEditWidget*> layerEditList;
		QVBoxLayout* layerEditLayout;
		NeuralNetworkModel* model;
};

#endif // TOPOLOGYWIDGET_H
