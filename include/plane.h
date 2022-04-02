#ifndef PLANE_H
#define PLANE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"
#include "include/body.h"

class Plane: public Body {
public:
    Plane(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
};

#endif // PLANE_H
