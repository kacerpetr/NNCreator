#ifndef FCN_H
#define FCN_H

#include <string>
#include <QColor>

namespace Util{

double stringToDouble(const std::string& str);
double round(double value, int digit);
double random(double min, double max);
double random(int seed, double from, double to);
int random(int from, int to);
int random(int from, int to, int seed);
QColor color(int index);

}
#endif
