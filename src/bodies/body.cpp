#include "include/bodies/body.h"
#include "include/bodies/sphere.h"
#include "include/bodies/plane.h"
#include "include/bodies/cube.h"
#include "include/bodies/cylinder.h"
#include "include/bodies/cone.h"
//#include "include/bodies/group.h"
#include "include/bodies/triangle.h"
#include "include/bodies/smoothtriangle.h"
#include <QDebug>

Body::Body(Material *material, OBJ_TYPE type) {
    this->material = material;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
    this->mInverse = Matrix::identity_matrix();;
}

// transformation ! del original array
QVector<Intersection *> Body::intersection(Ray *ray) {
    switch (this->type) {
        case OBJ_SMOOTH_TRIANGLE: {
            return SmoothTriangle::intersection(this, ray);
        }
        case OBJ_TRIANGLE: {
            return Triangle::intersection(this, ray);
        }
        case OBJ_PLANE: {
            return Plane::intersection(this, ray);
        }
        case OBJ_SPHERE: {
            return Sphere::intersection(this, ray);
        }
        case OBJ_CUBE: {
            return Cube::intersection(this, ray);
        }
        case OBJ_CYLINDER: {
            return Cylinder::intersection(this, ray);
        }
        case OBJ_CONE: {
            return Cone::intersection(this, ray);
        }
    }
    return {};
}

Vector* Body::normal(Vector *point, Intersection *hit) {
    point = this->mInverse->vector_multiply(point);
    switch (this->type) {
        case OBJ_SMOOTH_TRIANGLE: {
            return SmoothTriangle::normal(this, point, hit);
        }
        case OBJ_TRIANGLE: {
            return this->n0;
        }
        case OBJ_SPHERE: {
            return Sphere::normal(this, point);
        }
        case OBJ_PLANE: {
            return new Vector(0, 1, 0, 0);
        }
        case OBJ_CUBE: {
            return Cube::normal(point);
        }
        case OBJ_CYLINDER: {
            return Cylinder::normal(this, point);
        }
        case OBJ_CONE: {
            return Cone::normal(this, point);
        }
    }
    return new Vector(0, 0, 0, 0);
}

void Body::transform(Matrix *matrix) {
    this->bTransformed = true;
    this->transformation = this->transformation->dot_product(matrix);
    this->mInverse = this->transformation->inverse();
}

