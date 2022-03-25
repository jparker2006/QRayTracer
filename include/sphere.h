#ifndef SPHERE_H
#define SPHERE_H

#include <QVector>

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"

class Sphere {
public:
    Sphere(Material *material);
    QVector<Intersection *> intersection(Ray *ray);
    Vector *normal(Vector *point);
    Matrix *transformation = new Matrix(4, 4);
    Material *material;
};

#endif // SPHERE_H