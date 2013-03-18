#include "Plot2D.h"
#include <QDebug>
#include "GL/glu.h"
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>

namespace Application{

Plot2D::Plot2D(QWidget *parent) :
	QGLWidget(parent),
    img(NULL),
    xLabel("X axis name"),
    yLabel("Y axis name"),
    scale(1),
    xMax(1),
    xMin(-1),
    yMax(1),
    yMin(-1),
    oMax(1),
    oMin(-1),
    leftSpace(70),
    rightSpace(20),
    topSpace(20),
    bottomSpace(50)
{
    img = new QImage(64, 64, QImage::Format_RGB32);
    font.setFamily("Monospace");
    font.setBold(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu()));
}

Plot2D::~Plot2D(){
    delete img;
}

void Plot2D::setRes(int xRes, int yRes){
    delete img;
    img = new QImage(xRes, yRes, QImage::Format_RGB32);
}

void Plot2D::setRange(double min, double max){
    scale = 1.0 / (max - min);
}

void Plot2D::setRangeX(double min, double max){
    xMin = min;
    xMax = max;
}

void Plot2D::setRangeY(double min, double max){
    yMin = min;
    yMax = max;
}

void Plot2D::setLabelX(QString text){
    xLabel = text;
}

void Plot2D::setLabelY(QString text){
    yLabel = text;
}

void Plot2D::setPoint(int x, int y, double val){
    QColor color;
    if(val >= 0) color.setRgbF(scale * val, 0, 0);
    else color.setRgbF(0, 0, scale * (-val));
    img->setPixel(x, y, color.rgb());
}

QImage* Plot2D::image(){
    return img;
}

void Plot2D::contextMenu(){
    QMenu menu;
    menu.addAction("Clear graph" , this , SLOT(clearGraph()));
    menu.addAction("Save as .csv" , this , SLOT(saveGraphCsv()));
    menu.addAction("Save as .png" , this , SLOT(saveGraphPng()));
    menu.popup(QCursor::pos());
    menu.exec();
}

void Plot2D::clearGraph(){
    setRange(-1,1);
    setRangeX(-1,1);
    setRangeY(-1,1);
    delete img;
    img = NULL;
    repaint();
}

void Plot2D::saveGraphCsv(){

}

void Plot2D::saveGraphPng(){
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

void Plot2D::initializeGL(){
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0);
}

void Plot2D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
    drawGraph();
    drawXAxis();
    drawYAxis();
}

void Plot2D::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Plot2D::drawGraph(){
    if(img != NULL){
        glLoadIdentity();
        glColor3f(0.7f, 0.7f, 0.7f);
        bindTexture(*img, GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(leftSpace, bottomSpace);
            glTexCoord2f(0, 1);
            glVertex2f(width()-rightSpace, bottomSpace);
            glTexCoord2f(1, 1);
            glVertex2f(width()-rightSpace, height()-topSpace);
            glTexCoord2f(1, 0);
            glVertex2f(leftSpace, height()-topSpace);
        glEnd();
    }

    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    //bottom
    glVertex2f(leftSpace, bottomSpace);
    glVertex2f(width()-rightSpace, bottomSpace);
    //right
    glVertex2f(width()-rightSpace, bottomSpace);
    glVertex2f(width()-rightSpace, height()-topSpace);
    //top
    glVertex2f(width()-rightSpace, height()-topSpace);
    glVertex2f(leftSpace, height()-topSpace);
    //left
    glVertex2f(leftSpace, height()-topSpace);
    glVertex2f(leftSpace, bottomSpace);
    glEnd();
}

void Plot2D::drawXAxis(){
    double step = (width() - leftSpace - rightSpace) / 10.0;
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    for(int i = 0; i <= 10; i++){
        glVertex2f(leftSpace+i*step, bottomSpace);
        glVertex2f(leftSpace+i*step, bottomSpace-5);
    }
    glEnd();

    double vStep = (xMax - xMin) / 10.0;
    for(int i = 0; i <= 10; i++){
        rendText(leftSpace+i*step, bottomSpace-15, QString::number(i*vStep+oMin));
    }

    rendText(width()/2.0, 15, xLabel);
}

void Plot2D::drawYAxis(){
    double step = (height() - bottomSpace - topSpace) / 10.0;
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    for(int i = 0; i <= 10; i++){
        glVertex2f(leftSpace, bottomSpace+i*step);
        glVertex2f(leftSpace-5, bottomSpace+i*step);
    }
    glEnd();

    double vStep = (yMax - yMin) / 10.0;
    for(int i = 0; i <= 10; i++){
        rendText(leftSpace-23, bottomSpace+i*step, QString::number(i*vStep+oMin));
    }

    rendTextV(15, height()/2, yLabel);
}

void Plot2D::rendText(float x, float y, QString text){
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(x - (text.length() * 7.7f)/2.0f, y - 5.0f, 0.0);
    renderText(0.0f, 0.0f, 0.0f, text, font);
}

void Plot2D::rendTextV(float x, float y, QString text){
    y += text.length()*6.0f;
    for(int i = text.length()-1; i >=0 ; i--){
        rendText(x, y-12.0*i, QString(text[i]));
    }
}

}
