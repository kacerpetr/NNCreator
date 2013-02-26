#include "Plot1D.h"
#include <QDebug>
#include "GL/glu.h"

namespace Application{

Plot1D::Plot1D(QWidget *parent) : QGLWidget(parent){}

void Plot1D::addPoint(double x, double y){
	if(x > xMax) xMax = x;
	if(y > yMax) yMax = y;
	Point1D pt;
	pt.x = x;
	pt.o = y;
	point.append(pt);
	repaint();
}

void Plot1D::addPoint(Point1D point){
	if(point.x > xMax) xMax = point.x;
	if(point.o > yMax) yMax = point.o;
	this->point.append(point);
	repaint();
}

void Plot1D::setData(QList<Point1D> data){
	point = data;
	for(int i = 0; i < point.length(); i++){
		if(point[i].x > xMax) xMax = point[i].x;
		if(point[i].o > yMax) yMax = point[i].o;
	}
	repaint();
}

void Plot1D::clearGraph(){
	point.clear();
	repaint();
}

void Plot1D::initializeGL(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.9, 0.9, 0.9, 0);
}

void Plot1D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawXAxis();
	drawYAxis();
	drawGraph();
}

void Plot1D::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Plot1D::drawGraph(){
	if(point.length() < 2) return;

	double sx = (width()-20) / xMax;
	double sy = (height()-20) / yMax;

	glColor3f(0,0,0);
	glBegin(GL_LINES);

	for(int i = 1; i < point.length(); i++){
		glVertex2f(10+sx*point[i-1].x, 10+sy*point[i-1].o);
		glVertex2f(10+sx*point[i].x, 10+sy*point[i].o);
	}

	glEnd();
}

void Plot1D::drawXAxis(){
	glColor3f(0,0,0);

	glBegin(GL_LINES);
		//axis
		glVertex2f(10, 10);
		glVertex2f(width()-10, 10);
		//arrow
		glVertex2f(width()-25, 6);
		glVertex2f(width()-10, 10);
		//arrow
		glVertex2f(width()-25, 14);
		glVertex2f(width()-10, 10);
	glEnd();
}

void Plot1D::drawYAxis(){
	glColor3f(0,0,0);

	glBegin(GL_LINES);
		//axis
		glVertex2f(10, 10);
		glVertex2f(10, height()-10);
		//arrow
		glVertex2f(10, height()-10);
		glVertex2f(14, height()-25);
		//arrow
		glVertex2f(10, height()-10);
		glVertex2f(6, height()-25);
	glEnd();
}

}
