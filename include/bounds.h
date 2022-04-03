#ifndef BOUNDS_H
#define BOUNDS_H

#include "include/vector.h"
#include "include/body.h"

class Bounds {
public:
    Bounds(Vector *min, Vector *max);
    Vector *min, *max;
    static Bounds *get_bounds(Body *body);
};

#endif // BOUNDS_H
