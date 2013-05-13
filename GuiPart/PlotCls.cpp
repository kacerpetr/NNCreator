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

#include "PlotCls.h"
#include <Util/Globaldef.h>
#include <QDebug>

namespace Application{

/**
 * Class constructor.
 */
PlotCls::PlotCls(QWidget* parent)
    : Plot2D(parent)
{}

/**
 * Class destructor.
 */
PlotCls::~PlotCls(){}

/**
 * Determines class from given outputs and colors pixel in plot pixmap.
 */
void PlotCls::classify(int x, int y, QList<double> outs){
    double max = -10E99;
    int out = 0;
    for(int i = 0; i < outs.length(); i++){
        if(outs[i] > max){
            max = outs[i];
            out = i;
        }
    }
    setPoint(x, y, color(out));
}

/**
 * Determines class from given points and shows point in diagram.
 */
void PlotCls::classifyPoint(double x, double y, QList<double> outs){
    double max = -10E99;
    int out = 0;

    for(int i = 0; i < outs.length(); i++){
        if(outs[i] > max){
            max = outs[i];
            out = i;
        }
    }

    Point2D pt;
    pt.x = x;
    pt.y = y;

    addPoint(pt, color(out));
}

}
