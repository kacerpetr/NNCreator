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

#ifndef PLOTCLS_H
#define PLOTCLS_H

#include <GuiPart/Plot2D.h>

/**
 * Contains main application graphical user interface classes.
 */
namespace Application{

/**
 * Two dimensional classification diagram.
 */
class PlotCls : public Plot2D{
    Q_OBJECT

    public:
        PlotCls(QWidget *parent = NULL);
        virtual ~PlotCls();
        void classify(int x, int y, QList<double> outs);
        void classifyPoint(double x, double y, QList<double> outs);
};

}

#endif // PLOTCLS_H
