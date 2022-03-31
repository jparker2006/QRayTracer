#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Triangle: public Body {
public:
    Triangle(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
};

#endif // TRIANGLE_H
