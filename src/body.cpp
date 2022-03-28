#include "include/body.h"
#include "include/sphere.h"
#include "include/plane.h"

Body::Body(Material *material, int index, OBJ_TYPE type) {
    this->material = material;
    this->index = index;
    this->transformation = Matrix::identity_matrix();
    this->type = type;
}

QVector<Intersection *> Body::intersection(Ray *ray) {
    switch (this->type) {
        case OBJ_SPHERE:
            return Sphere::intersection(this, ray);
        case OBJ_PLANE:
            return Plane::intersection(this, ray);
    }
}

Vector* Body::normal(Vector *point) {
    switch (this->type) {
        case OBJ_SPHERE:
            return Sphere::normal(this, point);
        case OBJ_PLANE:
            return Plane::normal(this, point);
    }
}

