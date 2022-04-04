#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Triangle: public Body {
public:
    Triangle(Material *material, Vector *p0, Vector *p1, Vector *p2);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
};

#endif // TRIANGLE_H
