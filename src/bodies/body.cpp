#include "include/bodies/body.h"
#include "include/bodies/sphere.h"
#include "include/bodies/plane.h"
#include "include/bodies/cube.h"
#include "include/bodies/cylinder.h"
#include "include/bodies/cone.h"
#include "include/bodies/group.h"
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
        case OBJ_SMOOTH_TRIANGLE:
            return SmoothTriangle::intersection(this, ray);
        case OBJ_TRIANGLE:
            return Triangle::intersection(this, ray);
//            if (this->parent && OBJ_GROUP == this->parent->type)
//                return Triangle::intersection(this, ray);
//            return Triangle::intersection(this, ray->transform(this->mInverse));
        case OBJ_PLANE:
//            if (this->parent && OBJ_GROUP == this->parent->type)
            return Plane::intersection(this, ray);
//            return Plane::intersection(this, ray->transform(this->mInverse));
        case OBJ_GROUP:
            return Group::intersection(this, ray);
        case OBJ_SPHERE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Sphere::intersection(this, ray);
            return Sphere::intersection(this, ray->transform(this->mInverse));
        case OBJ_CUBE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cube::intersection(this, ray);
            return Cube::intersection(this, ray->transform(this->mInverse));
        case OBJ_CYLINDER:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cylinder::intersection(this, ray);
            return Cylinder::intersection(this, ray->transform(this->mInverse));
        case OBJ_CONE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cone::intersection(this, ray);
            return Cone::intersection(this, ray->transform(this->mInverse));
    }
    return {};
}

Vector* Body::normal(Vector *point, Intersection *hit) {
    switch (this->type) {
        case OBJ_SMOOTH_TRIANGLE:
            return SmoothTriangle::normal(this, point, hit);
        case OBJ_TRIANGLE:
            return this->n0;
        case OBJ_GROUP:
            return Group::normal(this, point);
        case OBJ_SPHERE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Sphere::normal(this, point);
            return Sphere::normal(this, this->mInverse->vector_multiply(point));
        case OBJ_PLANE:
            return new Vector(0, 1, 0, 0);
        case OBJ_CUBE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cube::normal(point);
            return Cube::normal(this->mInverse->vector_multiply(point));
        case OBJ_CYLINDER:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cylinder::normal(this, point);
            return Cylinder::normal(this, this->mInverse->vector_multiply(point));
        case OBJ_CONE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cone::normal(this, point);
            return Cone::normal(this, this->mInverse->vector_multiply(point));
    }
    return new Vector(0, 0, 0, 0);
}

void Body::transform(Matrix *matrix) { // possible mem leak
    this->transformation = this->transformation->dot_product(matrix);
    this->mInverse = this->transformation->inverse();
}

