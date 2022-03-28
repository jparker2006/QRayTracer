#ifndef SPHERE_H
#define SPHERE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Sphere: public Body {
public:
    Sphere(Material *material, int index);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
};

#endif // SPHERE_H
