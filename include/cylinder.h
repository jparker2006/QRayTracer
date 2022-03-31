#ifndef CYLINDER_H
#define CYLINDER_H


#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Cylinder: public Body {
public:
    Cylinder(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
    static bool check_caps(Ray *ray, float ft);
};

#endif // CYLINDER_H
