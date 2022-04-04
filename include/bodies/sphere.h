#ifndef SPHERE_H
#define SPHERE_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Sphere: public Body {
public:
    Sphere(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
};

#endif // SPHERE_H
