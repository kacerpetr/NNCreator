#ifndef LAYEREDITWIDGET_H
#define LAYEREDITWIDGET_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <Project/TopologyEditModel.h>

using namespace Project;
namespace Ui{class LayerEditWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * The LayerEditWidget class.
 */
class LayerEditWidget : public QWidget{
	Q_OBJECT
		
	public:
		explicit LayerEditWidget(QWidget *parent = 0);
		~LayerEditWidget();
		bool isSelected();
		void setSelected(bool selected);
		void setLayerName(QString name);
		QString getLayerName();
		bool isInputLayer();
		void setAsInputLayer(bool inputLayer);
		void setNeuronCount(int neuronCount);
		int getNeuronCount();
		void setDuplicateButtonDisabled(bool disabled);
		void setRemoveButtonDisabled(bool disabled);
		bool isDuplicateButtonDisabled();
		bool isRemoveButtonDisabled();

	public slots:
		void neuronCountChange(int count);
		void duplicateButtonPress();
		void removeButtonPress();

	signals:
		void widgetPressed(LayerEditWidget*);
		void countChanged(LayerEditWidget*, int);
		void duplicatePressed(LayerEditWidget*);
		void removePressed(LayerEditWidget*);

	private:
		void setNeuronImageFrame();
		void mousePressEvent(QMouseEvent * e);

	private:
		Ui::LayerEditWidget *ui;
		TopologyEditModel* model;
		QList<QLabel*> neuronList;
		bool selected;
		bool inputLayer;
};

}

#endif // LAYEREDITWIDGET_H
