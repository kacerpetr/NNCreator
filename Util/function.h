#ifndef FCN_H
#define FCN_H

#include <string>

namespace Util{

double stringToDouble(const std::string& str);
double round(double value, int digit);
double random(double min, double max);
int random(int from, int to);

}

#endif
