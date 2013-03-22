#include "PlotCls.h"
#include <Util/function.h>

namespace Application{

PlotCls::PlotCls(QWidget* parent)
    : Plot2D(parent)
{}

PlotCls::~PlotCls(){}

void PlotCls::classify(int x, int y, QList<double> outs){
    double max = -10E99;
    int out = 0;
    for(int i = 0; i < outs.length(); i++){
        if(outs[i] > max){
            max = outs[i];
            out = i;
        }
    }
    setPoint(x, y, Util::color(out));
}

}
