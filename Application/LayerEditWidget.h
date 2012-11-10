#ifndef LAYEREDITWIDGET_H
#define LAYEREDITWIDGET_H

#include <QWidget>
#include <QList>
#include <QLabel>
#include <Project/NeuralNetworkModel.h>

namespace Ui {
	class LayerEditWidget;
}

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
		void setMoveUpButtonDisabled(bool disabled);
		void setMoveDownButtonDisabled(bool disabled);
		void setDuplicateButtonDisabled(bool disabled);
		void setRemoveButtonDisabled(bool disabled);
		bool isMoveUpButtonDisabled();
		bool isMoveDownButtonDisabled();
		bool isDuplicateButtonDisabled();
		bool isRemoveButtonDisabled();

	public slots:
		void neuronCountChange(int count);
		void moveUpButtonPress();
		void moveDownButtonPress();
		void duplicateButtonPress();
		void renameButtonPress();

	signals:
		void widgetPressed(LayerEditWidget*);
		void neuronCountChanged(LayerEditWidget*, int);
		void moveUpButtonPressed(LayerEditWidget*);
		void moveDownButtonPressed(LayerEditWidget*);
		void duplicateButtonPressed(LayerEditWidget*);
		void renameButtonPressed(LayerEditWidget*);

	private:
		void setNeuronImageFrame();
		void mousePressEvent(QMouseEvent * e);

	private:
		Ui::LayerEditWidget *ui;
		NeuralNetworkModel* model;
		QList<QLabel*> neuronList;
		bool selected;
		bool inputLayer;
};

#endif // LAYEREDITWIDGET_H
