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

#include "Plot3D.h"
#include <QDebug>
#include "GL/glu.h"
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>

namespace Application{

/**
 * Class constructor.
 */
Plot3D::Plot3D(QWidget *parent) :
	QGLWidget(parent),
    xMin(-1),
    xMax(1),
    yMin(-1),
    yMax(1),
    zMin(-1),
    zMax(1),
    oMin(-1),
    oMax(1),
    cut(0),
    xRot(-35),
    yRot(-47),
    scale(1),
    lbPressed(false),
    rbPressed(false),
    mouseX(0),
    mouseY(0)
{}

/**
 * Class destructor.
 */
Plot3D::~Plot3D(){
    font.setFamily("Monospace");
    font.setBold(true);
    setContextMenuPolicy(Qt::CustomContextMenu);

    for(int i = 0; i < 20; i++){
        layer.append(new QImage(20, 20, QImage::Format_RGB32));
    }
}

/**
 * Sets pixmap count and resolution.
 */
void Plot3D::setRes(int xRes, int yRes, int zRes){
    clearGraph();
    for(int i = 0; i < zRes; i++){
        layer.append(new QImage(xRes, yRes, QImage::Format_RGB32));
    }
}

/**
 * Sets value at given pixmap coordinates.
 */
void Plot3D::setPoint(int x, int y, int z, double val){
    QColor color;
    if(val >= 0) color.setRgbF((1.0/oMax)*val, 0, 0);
    else color.setRgbF(0, 0, (1.0/oMin)*val);
    layer[z]->setPixel(x, layer[z]->height()-1-y, color.rgb());
}

/**
 * Sets output range.
 */
void Plot3D::setRange(double min, double max){
    oMin = min;
    oMax = max;
}

/**
 * Sets X axis range.
 */
void Plot3D::setRangeX(double min, double max){
    xMin = min;
    xMax = max;
}

/**
 * Sets Y axis range.
 */
void Plot3D::setRangeY(double min, double max){
    yMin = min;
    yMax = max;
}

/**
 * Sets Z axis range.
 */
void Plot3D::setRangeZ(double min, double max){
    zMin = min;
    zMax = max;
}

/**
 * Shows context menu.
 */
void Plot3D::contextMenu(){
    QMenu menu;
    menu.addAction(tr("Reset view") , this , SLOT(resetView()));
    menu.addAction(tr("Clear graph") , this , SLOT(clearGraph()));
    menu.addAction(tr("Save as .png") , this , SLOT(saveGraphPng()));
    menu.popup(QCursor::pos());
    menu.exec();
}

/**
 * Returns view to its default state.
 */
void Plot3D::resetView(){
    yRot = -35;
    xRot = -47;
    scale = 1;
    cut = 0;
    repaint();
}

/**
 * Clears plot (range and plot pixmaps).
 */
void Plot3D::clearGraph(){
    for(int i = 0; i < layer.length(); i++){
        delete layer[i];
        layer[i] = NULL;
    }
    layer.clear();
}

/**
 * Saves image as png.
 */
void Plot3D::saveGraphPng(){
    QString filename = QFileDialog::getSaveFileName(
        this,
        tr("Save plot as .png"),
        QDir::homePath(),
        tr("Png images (*.png)")
    );

    if(!filename.isNull()){
        QImageWriter writer(filename, "png");
        writer.write(grabFrameBuffer());

        if(writer.error() != QImageWriter::UnknownError){
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Save plot as .png"));
            msgBox.setText(tr("Error"));
            msgBox.setInformativeText(writer.errorString());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

/**
 * OpenGL initialization.
 */
void Plot3D::initializeGL(){
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
}

/**
 * PaintGL method.
 */
void Plot3D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);

    gluPerspective(45.0f, (float)width() / (float)height(), 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	drawGraph();
    drawGrid();

    glLoadIdentity();
    gluOrtho2D(0, width(), 0, height());
    glMatrixMode(GL_PROJECTION);

    drawLegend();
}

/**
 * ResizeGL method.
 */
void Plot3D::resizeGL(int w, int h){
	if(h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Draws plot pixmaps.
 */
void Plot3D::drawGraph(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

    if(layer.isEmpty()) return;
    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glScalef(scale, scale, scale);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 1.0f, 1.0f);

    float step = 2.0 / (layer.length()-1);
    for(int i = 0; i < layer.length()-cut; i++){
        bindTexture(*layer[i], GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            glTexCoord2f(0.02, 0.02);
            glVertex3f(-1.0, -1.0, i*step-1.0);
            glTexCoord2f(0.02, 0.98);
            glVertex3f(-1.0, 1.0, i*step-1.0);
            glTexCoord2f(0.98, 0.98);
            glVertex3f(1.0, 1.0, i*step-1.0);
            glTexCoord2f(0.98, 0.02);
            glVertex3f(1.0, -1.0, i*step-1.0);
        glEnd();
    }
}

/**
 * Draws plot grid.
 */
void Plot3D::drawGrid(){
    glDisable(GL_TEXTURE_2D);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    glScalef(scale, scale, scale);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glLineWidth(2);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.5f, 0.0f, 0.0f);
    glVertex3f( 1.5f, 0.0f, 0.0f);
    glVertex3f( 1.5f, 0.0f, 0.0f);
    glVertex3f( 1.4f, 0.05f, 0.0f);
    glVertex3f( 1.5f, 0.0f, 0.0f);
    glVertex3f( 1.4f,-0.05f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.5f, 0.0f);
    glVertex3f(0.0f, 1.5f, 0.0f);
    glVertex3f(0.0f, 1.5f, 0.0f);
    glVertex3f(0.0f, 1.4f, 0.05f);
    glVertex3f(0.0f, 1.5f, 0.0f);
    glVertex3f(0.0f, 1.4f, -0.05f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -1.5f);
    glVertex3f(0.0f, 0.0f, 1.5f);
    glVertex3f(0.0f, 0.0f, 1.5f);
    glVertex3f(0.05f, 0.0f, 1.4f);
    glVertex3f(0.0f, 0.0f, 1.5f);
    glVertex3f(-0.05f, 0.0f, 1.4f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    //top
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    //bottom
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    //side
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glEnd();

    glLineWidth(1);
    glColor3f(0.3f, 0.3f, 0.3f);

    glBegin(GL_LINES);
    //ax1
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, 0.0f);
    //ax2
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, -1.0f,  1.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(0.0f,  1.0f, -1.0f);
    glVertex3f(0.0f,  1.0f,  1.0f);
    glVertex3f(0.0f, -1.0f,  1.0f);
    glVertex3f(0.0f,  1.0f,  1.0f);
    glVertex3f(0.0f,  1.0f, -1.0f);
    //ax3
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f,  1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f( 1.0f, 0.0f, -1.0f);
    glVertex3f( 1.0f, 0.0f,  1.0f);
    glVertex3f(-1.0f, 0.0f,  1.0f);
    glVertex3f( 1.0f, 0.0f,  1.0f);
    glVertex3f( 1.0f, 0.0f, -1.0f);
    glEnd();
}

/**
 * Draws plot legend.
 */
void Plot3D::drawLegend(){
    glLoadIdentity();
    glLineWidth(2);
    font.setBold(true);

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(210.0f, 10.0f , 0.0f);
    glVertex3f(210.0f, 94.0f, 0.0f);
    glVertex3f(10.0f , 94.0f, 0.0f);
    glVertex3f(10.0f , 10.0f , 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(10.0f , 10.0f );
    glVertex2f(210.0f, 10.0f);
    glVertex2f(210.0f, 10.0f);
    glVertex2f(210.0f, 94.0f);
    glVertex2f(210.0f, 94.0f);
    glVertex2f(10.0f , 94.0f );
    glVertex2f(10.0f , 94.0f);
    glVertex2f(10.0f , 10.0f );
    glEnd();

    //x axis
    glColor3f(1.0f, 0.0f, 0.0f);
    renderText(20.0f, 16.0f, 0.0f, "X", font);
    glBegin(GL_LINES);
    glVertex2f(35.0f , 20.0f);
    glVertex2f(200.0f, 20.0f);
    glVertex2f(200.0f, 20.0f);
    glVertex2f(190.0f, 23.0f);
    glVertex2f(200.0f, 20.0f);
    glVertex2f(190.0f, 17.0f);
    glEnd();

    //y axis
    glColor3f(0.0f, 1.0f, 0.0f);
    renderText(20.0f, 41.0f, 0.0f, "Y", font);
    glBegin(GL_LINES);
    glVertex2f(35.0f , 45.0f);
    glVertex2f(200.0f, 45.0f);
    glVertex2f(200.0f, 45.0f);
    glVertex2f(190.0f, 48.0f);
    glVertex2f(200.0f, 45.0f);
    glVertex2f(190.0f, 42.0f);
    glEnd();

    // z axis
    glColor3f(0.0f, 0.0f, 1.0f);
    renderText(20.0f, 66.0f, 0.0f, "Z", font);
    glBegin(GL_LINES);
    glVertex2f(35.0f , 70.0f);
    glVertex2f(200.0f, 70.0f);
    glVertex2f(200.0f, 70.0f);
    glVertex2f(190.0f, 73.0f);
    glVertex2f(200.0f, 70.0f);
    glVertex2f(190.0f, 67.0f);
    glEnd();

    font.setBold(false);
    glColor3f(1.0f, 0.0f, 0.0f);
    rendText(120, 30, "(" + QString::number(xMin) + tr(" to ") + QString::number(xMax) + ")");
    glColor3f(0.0f, 1.0f, 0.0f);
    rendText(120, 55, "(" + QString::number(yMin) + tr(" to ") + QString::number(yMax) + ")");
    glColor3f(0.0f, 0.0f, 1.0f);
    rendText(120, 80, "(" + QString::number(zMin) + tr(" to ") + QString::number(zMax) + ")");
}

/**
 * Rotates and cuts plot on mouse move.
 */
void Plot3D::mouseMoveEvent(QMouseEvent* event){
    if(lbPressed){
        yRot += (event->x() - mouseX)/2.0;
        xRot += (event->y() - mouseY)/2.0;
		repaint();
    }
    else if(rbPressed){
        int num = event->y() - mouseY;
        if(num < 0 && cut >= 1) cut--;
        else if(num > 0 && cut < layer.length()-1) cut++;
        repaint();
    }
	mouseX = event->x();
	mouseY = event->y();
}

/**
 * Initiates plot rotation, cut and context menu.
 */
void Plot3D::mousePressEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton){
        lbPressed = true;
		mouseX = event->x();
		mouseY = event->y();
	}
    if(event->button() == Qt::RightButton){
        if(mouseY != event->y()){
            rbPressed = true;
            mouseX = event->x();
            mouseY = event->y();
        }
        else{
            contextMenu();
        };
    }
}

/**
 * Sets mouse button state variables to false.
 */
void Plot3D::mouseReleaseEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton) lbPressed = false;
    if(event->button() == Qt::RightButton) rbPressed = false;
}

/**
 * Plot zooming.
 */
void Plot3D::wheelEvent(QWheelEvent* event){
	scale += event->delta()*0.0005;
	repaint();
}

/**
 * Draws given text at given position.
 */
void Plot3D::rendText(float x, float y, QString text){
    float xp = x - (text.length() * 7.7f)/2.0f;
    float yp = y - 5.0f;
    renderText(xp, yp, 0.0f, text, font);
}

}
