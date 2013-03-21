#include "Plot1D.h"
#include <QDebug>
#include "GL/glu.h"
#include <QMenu>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>
#include <QTextStream>

namespace Application{

Plot1D::Plot1D(QWidget *parent) :
	QGLWidget(parent),
    autorange(true),
    xrMin(-1),
    xrMax(1),
    orMin(-1),
    orMax(1),
    xMin(1E99),
    xMax(-1E99),
    oMin(1E99),
	oMax(-10000),
	leftSpace(75),
    rightSpace(25),
    topSpace(20),
    bottomSpace(45),
    xLbl("X axis"),
    yLbl("Y axis")
{
	font.setFamily("Monospace");
	font.setBold(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu()));
}

Plot1D::Plot1D(QString data, QWidget *parent) :
    QGLWidget(parent),
    xMax(-10000),
    oMax(-10000),
    leftSpace(75),
    rightSpace(25),
    topSpace(20),
    bottomSpace(45),
    xLbl("X axis"),
    yLbl("Y axis")
{
    font.setFamily("Monospace");
    font.setBold(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu()));
    fromString(data);
}


Plot1D::~Plot1D(){}

void Plot1D::contextMenu(){
    QMenu menu;
    menu.addAction("Clear graph" , this , SLOT(clearGraph()));
    menu.addAction("Save as .csv" , this , SLOT(saveGraphCsv()));
    menu.addAction("Save as .png" , this , SLOT(saveGraphPng()));
    menu.popup(QCursor::pos());
    menu.exec();
}

void Plot1D::addPoint(double x, double o){
    if(x < xMin) xMin = x;
    if(x > xMax) xMax = x;
    if(o < oMin) oMin = o;
	if(o > oMax) oMax = o;

	Point1D pt;
	pt.x = x;
	pt.o = o;

	point.append(pt);
}

void Plot1D::clearGraph(){
	point.clear();
	xMax = -10000;
	oMax = -10000;
	repaint();
}

void Plot1D::saveGraphCsv(){
    QString filename = QFileDialog::getSaveFileName(
        this,
        tr("Save plot as .csv"),
        QDir::homePath(),
        tr("Csv files (*.csv)")
    );

    if(!filename.isNull()){
        QFile file(filename);

        if(!file.open(QFile::WriteOnly)){
            QMessageBox msgBox;
            msgBox.setWindowTitle("Save plot as .csv");
            msgBox.setText("Error");
            msgBox.setInformativeText("Unable to write file");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
            return;
        }

        QTextStream stream;
        stream.setDevice(&file);
        stream << toString();
        file.close();
    }
}

void Plot1D::saveGraphPng(){
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
            msgBox.setWindowTitle("Save plot as .png");
            msgBox.setText("Error");
            msgBox.setInformativeText(writer.errorString());
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
}

QString Plot1D::toString(){
    QString text;

    for(int i = 0; i < point.length(); i++){
        text += QString::number(point[i].x);
        text += "; ";
        text += QString::number(point[i].o);
        text += "\n";
    }

    return text;
}

void Plot1D::fromString(QString data){
    clearGraph();

    double xVal = 0;
    double yVal = 0;
    QString subText;
    int state = 0;

    for(int i = 0; i < data.length(); i++){
        switch(state){
            case 0:
                if(data[i] == ';'){
                    xVal = subText.toDouble();
                    subText = "";
                    state = 1;
                    break;
                }
                subText += data[i];
                break;

            case 1:
                if(data[i] == '\n'){
                    yVal = subText.toDouble();
                    subText = "";
                    addPoint(xVal, yVal);
                    state = 0;
                    break;
                }
                subText += data[i];
                break;

            default:
                break;
        }
    }

    repaint();
}

void Plot1D::setAutorange(bool enabled){
    autorange = enabled;
}

void Plot1D::setRange(double min, double max){
    orMin = min;
    orMax = max;
}

void Plot1D::setRangeX(double min, double max){
    xrMin = min;
    xrMax = max;
}

double Plot1D::maxX(){
    if(point.empty()) return 0;
    return xMax;
}

double Plot1D::maxO(){
    if(point.empty()) return 0;
    return oMax;
}

void Plot1D::setLabelX(QString label){
    xLbl = label;
}

void Plot1D::setLabelY(QString label){
    yLbl = label;
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

    double sx = 1;
    double sy = 1;
    if(autorange){
        sx = graphWidth() / (xMax-xMin);
        sy = graphHeight() / (oMax-oMin);
    }else{
        sx = graphWidth() / (xrMax-xrMin);
        sy = graphHeight() / (orMax-orMin);
    }

	glLoadIdentity();
	glColor3f(1.0, 0, 0);
	glLineWidth(2);

	glBegin(GL_LINES);
	for(int i = 1; i < point.length(); i++){
        glVertex2f(leftSpace+sx*(point[i-1].x-xMin), bottomSpace+sy*(point[i-1].o-oMin));
        glVertex2f(leftSpace+sx*(point[i].x-xMin), bottomSpace+sy*(point[i].o-oMin));
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
    for(int i = 1; i <= 10; i++){
        glVertex2f(i * graphWidth()/10.0 + leftSpace, bottomSpace);
        glVertex2f(i * graphWidth()/10.0 + leftSpace, height()-topSpace);
	}
	glEnd();
}

void Plot1D::drawXLabel(){
    double xm = autorange ? (xMax-xMin) : (xrMax-xrMin);
	if(point.isEmpty()) xm = 1;

	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 0.0f);
    for(int i = 0; i <= 10; i++){
        double val = i * (xm / 10) + (autorange?xMin:xrMin);
        rendText(i * graphWidth()/10.0 + leftSpace, bottomSpace-10, QString::number(val));
	}
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
    for(int i = 1; i <= 10; i++){
        glVertex2f(leftSpace, i * graphHeight()/10.0 + bottomSpace);
        glVertex2f(width()-rightSpace, i * graphHeight()/10.0 + bottomSpace);
	}
	glEnd();
}

void Plot1D::drawYLabel(){
    double om = autorange ? (oMax-oMin) : (orMax-orMin);
	if(point.isEmpty()) om = 1;

    for(int i = 0; i <= 10; i++){
        double val = i * (om / 10) + (autorange?oMin:orMin);
        rendText(leftSpace-23, i * graphHeight()/10.0 + bottomSpace, QString::number(val, 'g', 3));
	}

    rendTextV(15, height()/2, yLbl);
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

double Plot1D::graphWidth(){
    return width() - (leftSpace+rightSpace);
}

double Plot1D::graphHeight(){
    return height() - (bottomSpace+topSpace);
}

}
