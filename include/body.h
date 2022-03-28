#ifndef BODY_H
#define BODY_H

#include "include/vector.h"
#include "include/ray.h"
#include "include/intersection.h"
#include "include/matrix.h"
#include "include/material.h"

class Body {
public:
    enum OBJ_TYPE {
        OBJ_SPHERE,
        OBJ_PLANE
    };
    Body(Material *material, int index, OBJ_TYPE type);
    QVector<Intersection *> intersection(Ray *ray);
    Vector *normal(Vector *point);
    Matrix *transformation = new Matrix(4, 4);
    Material *material;
    int index;
    OBJ_TYPE type;
};

#endif // BODY_H
