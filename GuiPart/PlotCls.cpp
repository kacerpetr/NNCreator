#include "PlotCls.h"
#include <Util/Globaldef.h>

namespace Application{

/**
 * Class constructor.
 */
PlotCls::PlotCls(QWidget* parent)
    : Plot2D(parent)
{}

/**
 * Class destructor.
 */
PlotCls::~PlotCls(){}

/**
 * Determines class from given outputs and colors pixel in plot pixmap.
 */
void PlotCls::classify(int x, int y, QList<double> outs){
    double max = -10E99;
    int out = 0;
    for(int i = 0; i < outs.length(); i++){
        if(outs[i] > max){
            max = outs[i];
            out = i;
        }
    }
    setPoint(x, y, color(out));
}

}
