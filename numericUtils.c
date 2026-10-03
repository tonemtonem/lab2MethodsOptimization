#include "numericUtils.h"
#include <math.h>
#include <float.h>

bool IsZero(const double x) {
    return fabs(x) <= DBL_EPSILON * 100;
}
bool IsPositive(const double x) {
    return !IsZero(x) && x > 0;
}
bool IsNegative(const double x) {
    return !IsZero(x) && x < 0;
}
