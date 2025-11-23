#include "double_compare.h"
#include <math.h>

static const double EPSILON = 1e-9;

int DoubleCompare(double a, double b) {
    if (fabs(a - b) < EPSILON) return 0;
    if (a - b > 0) return 1;
    return -1;
}