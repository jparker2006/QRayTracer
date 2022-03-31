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
        OBJ_PLANE,
        OBJ_CUBE,
        OBJ_CYLINDER,
        OBJ_TRIANGLE,
        OBJ_CONE
    };
    Body(Material *material, OBJ_TYPE type);
    QVector<Intersection *> intersection(Ray *ray);
    Vector *normal(Vector *point);
    Matrix *transformation = new Matrix(4, 4);
    void transform(Matrix *matrix);
    Material *material;
    int index;
    OBJ_TYPE type;

    // cylinder data
    float fMin = -Q_INFINITY, fMax = Q_INFINITY;
    bool bClosed = false;
};

#endif // BODY_H
