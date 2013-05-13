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

#ifndef NETPARAMWIDGET_H
#define NETPARAMWIDGET_H

#include <QWidget>
#include "Project/TopologyEditModel.h"
using namespace ProjectData;

namespace Ui {
	class NetParamWidget;
}

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Network parameter widget class.
 */
class NetParamWidget : public QWidget{
	Q_OBJECT
		
	public:
        NetParamWidget(QWidget *parent = 0);
		~NetParamWidget();
		void setModel(TopologyEditModel* model);
		bool hasModel();		

	private slots:
		void modelChanged(ChangeType type);
		void randomizeWeights();
		void randomizeBias();
        void randomizeSlope();
		void setBiasSeed(int val);
		void setBiasMin(double val);
		void setBiasMax(double val);
		void setWgSeed(int val);
		void setWgMin(double val);
		void setWgMax(double val);
        void setSlopeSeed(int val);
        void setSlopeMin(double val);
        void setSlopeMax(double val);
		void trFcnSelected(int index);

	private:
		void setNetStats();
		void setRandGenParams();
		void setTrFcnBox();

	private:
        /** Net param widget ui pointer. */
        Ui::NetParamWidget *ui;
        /** Topology edit model pointer. */
		TopologyEditModel* mdl;
};

}

#endif // NETPARAMWIDGET_H
