#ifndef CUBE_H
#define CUBE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Cube: public Body {
public:
    Cube(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
    static QVector<float> check_axis(float fOrigin, float fDirection);
};

#endif // CUBE_H
