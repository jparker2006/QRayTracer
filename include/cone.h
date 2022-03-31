#ifndef CONE_H
#define CONE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Cone: public Body {
public:
    Cone(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
    static bool check_caps(Ray *ray, float ft);
};

#endif // CONE_H
