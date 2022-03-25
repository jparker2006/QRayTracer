#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "include/vector.h"
#include "include/sphere.h"

class Computation {
public:
    Computation();
    static Computation* prepare_computations(Ray *ray, Sphere* sphere,  Intersection *intersection);
    float ft;
    Vector *point, *eye, *normal;
    Sphere *object; // polymorph this when adding more objects
    bool bInside;
};

#endif // COMPUTATION_H
