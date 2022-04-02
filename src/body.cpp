#include "include/body.h"
#include "include/sphere.h"
#include "include/plane.h"
#include "include/cube.h"
#include "include/cylinder.h"
#include "include/cone.h"
#include "include/group.h"
#include "include/triangle.h"

Body::Body(Material *material, OBJ_TYPE type) {
    this->material = material;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
}

QVector<Intersection *> Body::intersection(Ray *ray) {
    switch (this->type) {
        case OBJ_GROUP:
            return Group::intersection(this, ray);
        case OBJ_SPHERE:
            return Sphere::intersection(this, ray);
        case OBJ_PLANE:
            return Plane::intersection(this, ray);
        case OBJ_CUBE:
            return Cube::intersection(this, ray);
        case OBJ_CYLINDER:
            return Cylinder::intersection(this, ray);
        case OBJ_CONE:
            return Cone::intersection(this, ray);
        case OBJ_TRIANGLE:
            return {};
    }
    return {};
}

Vector* Body::normal(Vector *point) {
    Matrix *mInverse = this->transformation->inverse();
    Vector *obj_point = mInverse->vector_multiply(point);
    delete mInverse;
    switch (this->type) {
        case OBJ_GROUP:
            return Group::normal(this, point);
        case OBJ_SPHERE:
            if (OBJ_GROUP == this->parent->type)
                return Sphere::normal(this, point);
            return Sphere::normal(this, obj_point);
        case OBJ_PLANE:
            return new Vector(0, 1, 0, 0);
        case OBJ_CUBE:
            if (OBJ_GROUP == this->parent->type)
                return Cube::normal(point);
            return Cube::normal(obj_point);
        case OBJ_CYLINDER:
            if (OBJ_GROUP == this->parent->type)
                return Cylinder::normal(this, point);
            return Cylinder::normal(this, obj_point);
        case OBJ_CONE:
            if (OBJ_GROUP == this->parent->type)
                return Cone::normal(this, point);
            return Cone::normal(this, obj_point);
        case OBJ_TRIANGLE:
            return new Vector(0, 0, 0, 0);
    }
    return new Vector(0, 0, 0, 0);
}

void Body::transform(Matrix *matrix) {
    this->transformation = this->transformation->dot_product(matrix);
}

