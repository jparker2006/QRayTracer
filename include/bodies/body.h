#ifndef BODY_H
#define BODY_H

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"

class Body {
public:
    enum OBJ_TYPE {
        OBJ_SPHERE,
        OBJ_PLANE,
        OBJ_CUBE,
        OBJ_CYLINDER,
        OBJ_TRIANGLE,
        OBJ_CONE,
        OBJ_GROUP,
        OBJ_SMOOTH_TRIANGLE
    };
    Body(Material *material, OBJ_TYPE type);
    QVector<Intersection *> intersection(Ray *ray);
    Vector *normal(Vector *point, Intersection *hit);
    Matrix *transformation = new Matrix(4, 4);
    void transform(Matrix *matrix);
    Material *material;
    int index;
    OBJ_TYPE type;
    Matrix *mInverse;

    // cylinder data
    float fMin = -10, fMax = 10;
    bool bClosed = false;

    // group data
    Body *parent = nullptr;
    QVector<Body*> vChildren;

    // triangle data
    Vector *p0, *p1, *p2, *e0, *e1, *n0, *n1, *n2;
};

#endif // BODY_H
