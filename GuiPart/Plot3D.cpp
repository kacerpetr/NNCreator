#include "Plot3D.h"
#include <QDebug>
#include "GL/glu.h"

namespace Application{

Plot3D::Plot3D(QWidget *parent) :
	QGLWidget(parent),
	xMax(-10000),
	yMax(-10000),
	zMax(-10000),
	oMax(-10000),
	rotX(0),
	rotY(0),
	scale(1),
	pressed(false),
	mouseX(0),
	mouseY(0)
{}

Plot3D::~Plot3D(){}

void Plot3D::addPoint(double x, double y, double z, double o){
	if(x > xMax) xMax = x;
	if(y > yMax) yMax = y;
	if(z > zMax) zMax = z;
	if(o > oMax) oMax = o;

	Point3D p;
	p.x = x;
	p.y = y;
	p.z = z;
	p.o = o;

	point.append(p);
	repaint();
}

void Plot3D::clearGraph(){
	xMax = - 10000;
	yMax = - 10000;
	zMax = - 10000;
	oMax = - 10000;
	point.clear();
	repaint();
}

void Plot3D::initializeGL(){
	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Plot3D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawXAxis();
	drawYAxis();
	drawZAxis();
	drawGraph();
}

void Plot3D::resizeGL(int w, int h){
	if(h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Plot3D::drawXAxis(){

}

void Plot3D::drawYAxis(){

}

void Plot3D::drawZAxis(){

}

void Plot3D::drawGraph(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -2.0f);
	glRotatef(rotY, 1, 0, 0);
	glRotatef(rotX, 0, 1, 0);
	glScalef(scale, scale, scale);

	glPointSize(10);
	glBegin(GL_POINTS);

	double sx = 1.0 / xMax;
	double sy = 1.0 / yMax;
	double sz = 1.0 / zMax;
	double so = 1.0 / oMax;

	for(int i = 0; i < point.length(); i++){
		glColor3f(0, 0, so * point[i].o);
		qDebug() << sz * point[i].z;
		glVertex3f(sx * point[i].x-0.5, sy * point[i].y-0.5, sz * point[i].z-0.5);
	}

	glEnd();
}

void Plot3D::mouseMoveEvent(QMouseEvent* event){
	if(pressed){
		rotX += (event->x() - mouseX)/2.0;
		rotY += (event->y() - mouseY)/2.0;
		repaint();
	}
	mouseX = event->x();
	mouseY = event->y();
}

void Plot3D::mousePressEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton){
		pressed = true;
		mouseX = event->x();
		mouseY = event->y();
	}
}

void Plot3D::mouseReleaseEvent(QMouseEvent* event){
	if(event->button() == Qt::LeftButton) pressed = false;
}

void Plot3D::wheelEvent(QWheelEvent* event){
	scale += event->delta()*0.0005;
	repaint();
}


}
