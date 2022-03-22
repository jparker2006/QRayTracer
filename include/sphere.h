#ifndef SPHERE_H
#define SPHERE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"

class Sphere {
public:
    Sphere();
    QVector<Intersection *> intersection(Ray *ray, bool bTransform);
    Matrix *transformation = new Matrix(4, 4);
};

#endif // SPHERE_H
