#ifndef TOPOLOGYWIDGET_H
#define TOPOLOGYWIDGET_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include "GuiPart/LayerEditWidget.h"
#include "Project/TopologyEditModel.h"
#include "GuiPart/NetParamWidget.h"
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
		bool hasModel();

	private slots:
		void closeBtnPressed();
		void widgetPressed(LayerEditWidget* widget);
		void appendLayer();
		void duplicateLayer(LayerEditWidget* widget);
		void removeLayer(LayerEditWidget* widget);
		void duplicateSelected();
		void removeSelected();
		void countChanged(LayerEditWidget* widget, int count);

	private:
		int selectedLayer();
		void makeView();
		void clearView();

	signals:
		void closePressed(BaseModel*);

	private:
		Ui::TopologyWidget *ui;
		QList<LayerEditWidget*> layerEditList;
		QList<QFrame*> layerLineList;
		QVBoxLayout* layerEditLayout;
		TopologyEditModel* model;
		NetParamWidget* npw;
};

}

#endif // TOPOLOGYWIDGET_H
