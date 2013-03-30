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
};

}

#endif // PLOTCLS_H
