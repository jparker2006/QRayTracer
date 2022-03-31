#include "include/body.h"
#include "include/sphere.h"
#include "include/plane.h"
#include "include/cube.h"
#include "include/cylinder.h"
#include "include/cone.h"
#include "include/triangle.h"

Body::Body(Material *material, OBJ_TYPE type) {
    this->material = material;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
}

QVector<Intersection *> Body::intersection(Ray *ray) {
    switch (this->type) {
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
//        case OBJ_TRIANGLE:
//            return Triangle::intersection(this, ray);
    }
    return {};
}

Vector* Body::normal(Vector *point) {
    switch (this->type) {
        case OBJ_SPHERE:
            return Sphere::normal(this, point);
        case OBJ_PLANE:
            return Plane::normal(this, point);
        case OBJ_CUBE:
            return Cube::normal(this, point);
        case OBJ_CYLINDER:
            return Cylinder::normal(this, point);
        case OBJ_CONE:
            return Cone::normal(this, point);
//        case OBJ_TRIANGLE:
//            return Triangle::normal(this, point);
    }
    return new Vector(0, 0, 0, 0);
}

void Body::transform(Matrix *matrix) {
    this->transformation = this->transformation->dot_product(matrix);
}

