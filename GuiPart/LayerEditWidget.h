#ifndef LAYEREDITWIDGET_H
#define LAYEREDITWIDGET_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <Project/TopologyEditModel.h>

using namespace ProjectData;
namespace Ui{class LayerEditWidget;}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Widget used for edition topology of one layer in neural network.
 */
class LayerEditWidget : public QWidget{
	Q_OBJECT
		
	public:
        LayerEditWidget(QWidget *parent = 0);
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
        /** Emitted when widget is pressed. */
		void widgetPressed(LayerEditWidget*);
        /** Emitted when neuron count is changed. */
		void countChanged(LayerEditWidget*, int);
        /** Emitted when dupplicate button is pressed. */
		void duplicatePressed(LayerEditWidget*);
        /** Emitted when remove button is pressed. */
		void removePressed(LayerEditWidget*);

	private:
		void setNeuronImageFrame();
		void mousePressEvent(QMouseEvent * e);

	private:
        /** Layer edit widget ui pointer. */
		Ui::LayerEditWidget *ui;
        /** Topology edit model pointer. */
		TopologyEditModel* model;
        /** List of neuron image labels. */
		QList<QLabel*> neuronList;
        /** True if label is selected. */
		bool selected;
        /** True if label is marked as input layer. */
		bool inputLayer;
};

}

#endif // LAYEREDITWIDGET_H
