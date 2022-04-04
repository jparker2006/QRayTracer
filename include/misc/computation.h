#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "include/math/vector.h"
#include "include/bodies/sphere.h"
#include "include/bodies/body.h"

class Computation {
public:
    Computation();
    static Computation* prepare_computations(Ray *ray, Body* body, Intersection *intersection, QVector<Intersection*> xs, QVector<Body*> world);
    float ft;
    Vector *point, *eye, *normal, *over_point, *under_point, *reflect;
    Body *object;
    bool bInside;
    float n1, n2;
};

#endif // COMPUTATION_H
