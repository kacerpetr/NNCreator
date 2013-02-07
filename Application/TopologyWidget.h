#ifndef TOPOLOGYWIDGET_H
#define TOPOLOGYWIDGET_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include "LayerEditWidget.h"
#include "Project/TopologyEditModel.h"
namespace Ui{class TopologyWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The TopologyWidget class.
 */
class TopologyWidget : public QWidget{
	Q_OBJECT

	public:
		explicit TopologyWidget(QWidget *parent = 0);
		~TopologyWidget();
		void setModel(TopologyEditModel* model);
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
		TopologyEditModel* model;
};

}

#endif // TOPOLOGYWIDGET_H
