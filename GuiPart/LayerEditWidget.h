/*
 * This file is part of Neural network Creator, backpropagation
 * simulator and multilayer neural network IDE.
 * Copyright (C) 2013  Petr Kačer <kacerpetr@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
