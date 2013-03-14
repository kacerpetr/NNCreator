#include "Plot1D.h"
#include <QDebug>
#include "GL/glu.h"

namespace Application{

Plot1D::Plot1D(QWidget *parent) :
	QGLWidget(parent),
	xMax(-10000),
	oMax(-10000),
	leftSpace(75),
	rightSpace(10),
	topSpace(10),
	bottomSpace(45)
{
	font.setFamily("Monospace");
	font.setBold(true);
}

Plot1D::~Plot1D(){}

void Plot1D::addPoint(double x, double o){
	if(x > xMax) xMax = x;
	if(o > oMax) oMax = o;

	Point1D pt;
	pt.x = x;
	pt.o = o;

	point.append(pt);
	repaint();
}

void Plot1D::addPoint(Point1D point){
	if(point.x > xMax) xMax = point.x;
	if(point.o > oMax) oMax = point.o;
	this->point.append(point);
	repaint();
}

void Plot1D::setData(QList<Point1D> data){
	point = data;
	for(int i = 0; i < point.length(); i++){
		if(point[i].x > xMax) xMax = point[i].x;
		if(point[i].o > oMax) oMax = point[i].o;
	}
	repaint();
}

void Plot1D::clearGraph(){
	point.clear();
	xMax = -10000;
	oMax = -10000;
	repaint();
}

void Plot1D::initializeGL(){
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0);
}

void Plot1D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawXGrid();
	drawYGrid();
	drawXAxis();
	drawYAxis();
	drawXLabel();
	drawYLabel();
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

	double sx = (width()-(leftSpace+rightSpace)) / xMax;
	double sy = (height()-(topSpace+bottomSpace)) / oMax;

	glLoadIdentity();
	glColor3f(1.0, 0, 0);
	glLineWidth(2);

	glBegin(GL_LINES);
	for(int i = 1; i < point.length(); i++){
		glVertex2f(leftSpace+sx*point[i-1].x, bottomSpace+sy*point[i-1].o);
		glVertex2f(leftSpace+sx*point[i].x, bottomSpace+sy*point[i].o);
	}
	glEnd();
}

void Plot1D::drawXAxis(){
	glLoadIdentity();
	glColor3f(0,0,0);
	glLineWidth(2);

	glBegin(GL_LINES);
		//axis
		glVertex2f(leftSpace, bottomSpace);
		glVertex2f(width()-rightSpace, bottomSpace);
		//arrow
		glVertex2f(width()-rightSpace-15, bottomSpace-4);
		glVertex2f(width()-rightSpace, bottomSpace);
		//arrow
		glVertex2f(width()-rightSpace-15, bottomSpace+4);
		glVertex2f(width()-rightSpace, bottomSpace);
	glEnd();
}

void Plot1D::drawXGrid(){
	glLoadIdentity();
	glColor3f(0.7f, 0.7f, 0.7f);
	glLineWidth(1);

	glBegin(GL_LINES);
	for(int i = 1; i < 10; i++){
		glVertex2f(i * width()/10.0 + leftSpace, bottomSpace);
		glVertex2f(i * width()/10.0 + leftSpace, height()-topSpace);
	}
	glEnd();
}

void Plot1D::drawXLabel(){
	double xm = xMax;
	if(point.isEmpty()) xm = 1;

	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);
	for(int i = 1; i < 10; i++){
		double val = i * (xm / 10);
		rendText(i * width()/10.0 + leftSpace, bottomSpace-10, QString::number(val));
	}
	rendText(leftSpace, bottomSpace-10, QString("0"));

	rendText(width()/2.0, 15, QString("X axis name"));
}

void Plot1D::drawYAxis(){
	glLoadIdentity();
	glColor3f(0,0,0);
	glLineWidth(2);

	glBegin(GL_LINES);
		//axis
		glVertex2f(leftSpace, bottomSpace);
		glVertex2f(leftSpace, height()-topSpace);
		//arrow
		glVertex2f(leftSpace, height()-topSpace);
		glVertex2f(leftSpace+4, height()-topSpace-15);
		//arrow
		glVertex2f(leftSpace, height()-topSpace);
		glVertex2f(leftSpace-4, height()-topSpace-15);
	glEnd();
}

void Plot1D::drawYGrid(){
	glLoadIdentity();
	glColor3f(0.7f, 0.7f, 0.7f);
	glLineWidth(1);

	glBegin(GL_LINES);
	for(int i = 1; i < 10; i++){
		glVertex2f(leftSpace, i * height()/10.0 + bottomSpace);
		glVertex2f(width()-rightSpace, i * height()/10.0 + bottomSpace);
	}
	glEnd();
}

void Plot1D::drawYLabel(){
	double om = oMax;
	if(point.isEmpty()) om = 1;

	for(int i = 1; i < 10; i++){
		double val = i * (om / 10);
		rendText(leftSpace-23, i * height()/10.0 + bottomSpace, QString::number(val, 'g', 3));
	}

	rendTextV(15, height()/2, QString("Y axis name"));
}

void Plot1D::rendText(float x, float y, QString text){
	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(x - (text.length() * 7.7f)/2.0f, y - 5.0f, 0.0);
	renderText(0.0f, 0.0f, 0.0f, text, font);
}

void Plot1D::rendTextV(float x, float y, QString text){
	y += text.length()*6.0f;
	for(int i = text.length()-1; i >=0 ; i--){
		rendText(x, y-12.0*i, QString(text[i]));
	}
}

}
