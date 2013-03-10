#include "Plot2D.h"
#include <QDebug>
#include "GL/glu.h"

namespace Application{

Plot2D::Plot2D(QWidget *parent) :
	QGLWidget(parent),
	xMax(-10000),
	yMax(-10000),
	oMax(-10000)
{}

Plot2D::~Plot2D(){}

void Plot2D::addPoint(double x, double y, double o){
	if(x > xMax) xMax = x;
	if(y > yMax) yMax = y;
	if(o > oMax) oMax = o;

	Point2D p;
	p.x = x;
	p.y = y;
	p.o = o;

	point.append(p);
	repaint();
}

void Plot2D::clearGraph(){
	xMax = - 10000;
	yMax = - 10000;
	oMax = - 10000;
	point.clear();
	repaint();
}

void Plot2D::initializeGL(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0);
}

void Plot2D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawXAxis();
	drawYAxis();
	drawGraph();
}

void Plot2D::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h); // set origin to bottom left corner
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Plot2D::drawXAxis(){

}

void Plot2D::drawYAxis(){

}

void Plot2D::drawGraph(){
	glPointSize(10);

	glBegin(GL_POINTS);

	double sx = (double)(width()-20) / xMax;
	double sy = (double)(height()-20) / yMax;

	double so = 1.0 / oMax;

	for(int i = 0; i < point.length(); i++){
		glColor3f(0, 0, so * point[i].o);
		//glColor3f(0, 0, 0);
		glVertex2f(10 + sx * point[i].x, 10 + sy * point[i].y);
	}

	glEnd();
}

}
