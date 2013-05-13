#include "Plot2D.h"
#include <QDebug>
#include "GL/glu.h"
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageWriter>

namespace Application{

/**
 * Class constructor.
 */
Plot2D::Plot2D(QWidget *parent) :
	QGLWidget(parent),
    img(NULL),
    xLabel(tr("X axis name")),
    yLabel(tr("Y axis name")),
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
    bottomSpace(50),
    smoothTex(true)
{
    img = new QImage(64, 64, QImage::Format_RGB32);
    font.setFamily("Monospace");
    font.setBold(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu()));
}

/**
 * Class destructor.
 */
Plot2D::~Plot2D(){
    delete img;
}

/**
 * Sets pixmap resolution.
 */
void Plot2D::setRes(int xRes, int yRes){
    delete img;
    img = new QImage(xRes, yRes, QImage::Format_RGB32);
}

/**
 * Sets output range.
 */
void Plot2D::setRange(double min, double max){
    scale = 1.0 / (max - min);
}

/**
 * Sets X axis range.
 */
void Plot2D::setRangeX(double min, double max){
    xMin = min;
    xMax = max;
}

/**
 * Sets Y axis range.
 */
void Plot2D::setRangeY(double min, double max){
    yMin = min;
    yMax = max;
}

/**
 * Sets X axis label.
 */
void Plot2D::setLabelX(QString text){
    xLabel = text;
}

/**
 * Sets Y axis label.
 */
void Plot2D::setLabelY(QString text){
    yLabel = text;
}

/**
 * Enables or disables texture filtering.
 */
void Plot2D::setSmoothTex(bool enable){
    smoothTex = enable;
    repaint();
}

/**
 * Sets value at given pixmap coordinates.
 */
void Plot2D::setPoint(int x, int y, double val){
    QColor color;
    if(val >= 0) color.setRgbF((1.0/oMax)*val, 0, 0);
    else color.setRgbF(0, 0, (1.0/oMin)*val);
    img->setPixel(x, y, color.rgb());
}

/**
 * Sets color at given pixmap coordinates.
 */
void Plot2D::setPoint(int x, int y, QColor clr){
    img->setPixel(x, y, clr.rgb());
}

/**
 * Returns pixmap pointer.
 */
QImage* Plot2D::image(){
    return img;
}

/**
 * Appends point to array of points.
 */
void Plot2D::addPoint(Point2D pt){
    point.append(pt);
}

/**
 * Clears array of points.
 */
void Plot2D::clearPoints(){
    point.clear();
}

/**
 * Shows context menu.
 */
void Plot2D::contextMenu(){
    QMenu menu;
    menu.addAction(tr("Clear graph") , this , SLOT(clearGraph()));
    menu.addAction(tr("Save as .png") , this , SLOT(saveGraphPng()));
    menu.popup(QCursor::pos());
    menu.exec();
}

/**
 * Clears plot (range and plot pixmap).
 */
void Plot2D::clearGraph(){
    setRange(-1,1);
    setRangeX(-1,1);
    setRangeY(-1,1);
    delete img;
    img = NULL;
    repaint();
}

/**
 * Saves plot as image.
 */
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
void Plot2D::initializeGL(){
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glDisable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0);
}

/**
 * PaintGL method.
 */
void Plot2D::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT);
    if(!smoothTex){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glEnable(GL_TEXTURE_2D);
    drawGraph();
    glDisable(GL_TEXTURE_2D);
    drawXAxis();
    drawYAxis();
    drawPoints();
}

/**
 * ResizeGL method.
 */
void Plot2D::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * Draws plot pixmap.
 */
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

/**
 * Draws X axis and its label.
 */
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
        rendText(leftSpace+i*step, bottomSpace-15, QString::number(i*vStep+xMin));
    }

    rendText(width()/2.0, 15, xLabel);
}

/**
 * Draws Y axis and its label.
 */
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
        rendText(leftSpace-23, bottomSpace+i*step, QString::number(i*vStep+yMin));
    }

    rendTextV(15, height()/2, yLabel);
}

/**
 * Draws points.
 */
void Plot2D::drawPoints(){
    if(point.isEmpty()) return;
    float scaleX = (width() - leftSpace - rightSpace) / (xMax - xMin);
    float scaleY = (height() - bottomSpace - topSpace) / (yMax - yMin);
    glLoadIdentity();
    glLineWidth(2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for(int i = 0; i < point.length(); i++){
        int x = leftSpace   + (point[i].x) * scaleX;
        int y = bottomSpace + (point[i].y) * scaleY;
        glVertex2f(x-5, y-5);
        glVertex2f(x+5, y+5);
        glVertex2f(x-5, y+5);
        glVertex2f(x+5, y-5);
    }
    glEnd();
}

/**
 * Draws given text at given position.
 */
void Plot2D::rendText(float x, float y, QString text){
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(x - (text.length() * 7.7f)/2.0f, y - 5.0f, 0.0);
    renderText(0.0f, 0.0f, 0.0f, text, font);
}

/**
 * Draws given text verticaly at given position.
 */
void Plot2D::rendTextV(float x, float y, QString text){
    y += text.length()*6.0f;
    for(int i = text.length()-1; i >=0 ; i--){
        rendText(x, y-12.0*i, QString(text[i]));
    }
}

}
