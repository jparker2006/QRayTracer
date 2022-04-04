#ifndef CYLINDER_H
#define CYLINDER_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Cylinder: public Body {
public:
    Cylinder(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
    static bool check_caps(Ray *ray, float ft);
};

#endif // CYLINDER_H
