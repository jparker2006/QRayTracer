#ifndef SMOOTHTRIANGLE_H
#define SMOOTHTRIANGLE_H


#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class SmoothTriangle: public Body {
public:
    SmoothTriangle(Material *material, Vector *p0, Vector *p1, Vector *p2, Vector *n0, Vector *n1, Vector *n2);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point, Intersection *intersection);
};

#endif // SMOOTHTRIANGLE_H
