#ifndef CUBE_H
#define CUBE_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Cube: public Body {
public:
    Cube(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Vector *point);
    static QVector<float> check_axis(float fOrigin, float fDirection);
};

#endif // CUBE_H
