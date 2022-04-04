#ifndef PLANE_H
#define PLANE_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Plane: public Body {
public:
    Plane(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
};

#endif // PLANE_H
