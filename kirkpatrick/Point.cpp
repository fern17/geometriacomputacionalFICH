#include "Point.h"

bool Point::operator ==(const Point &P) {
    return ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

bool Point::operator !=(const Point &P) {
    return not ((fabs(x - P.x) < EPSILON) and (fabs(y - P.y) < EPSILON));
}

