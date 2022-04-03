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
    Triangle(Material *material, Vector *p0, Vector *p1, Vector *p2);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
};

#endif // TRIANGLE_H
