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
    Matrix *mInverse = this->transformation->inverse();
    Ray *ray_t = ray->transform(mInverse);
    delete mInverse;
    switch (this->type) {
        case OBJ_TRIANGLE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Triangle::intersection(this, ray);
            return Triangle::intersection(this, ray_t);
        case OBJ_GROUP:
            return Group::intersection(this, ray);
        case OBJ_SPHERE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Sphere::intersection(this, ray);
            return Sphere::intersection(this, ray_t);
        case OBJ_PLANE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Plane::intersection(this, ray);
            return Plane::intersection(this, ray_t);
        case OBJ_CUBE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cube::intersection(this, ray);
            return Cube::intersection(this, ray_t);
        case OBJ_CYLINDER:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cylinder::intersection(this, ray);
            return Cylinder::intersection(this, ray_t);
        case OBJ_CONE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cone::intersection(this, ray);
            return Cone::intersection(this, ray_t);
    }
    return {};
}

Vector* Body::normal(Vector *point) {
    Matrix *mInverse = this->transformation->inverse();
    Vector *obj_point = mInverse->vector_multiply(point);
    delete mInverse;
    switch (this->type) {
        case OBJ_TRIANGLE:
            return this->norm;
        case OBJ_GROUP:
            return Group::normal(this, point);
        case OBJ_SPHERE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Sphere::normal(this, point);
            return Sphere::normal(this, obj_point);
        case OBJ_PLANE:
            return new Vector(0, 1, 0, 0);
        case OBJ_CUBE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cube::normal(point);
            return Cube::normal(obj_point);
        case OBJ_CYLINDER:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cylinder::normal(this, point);
            return Cylinder::normal(this, obj_point);
        case OBJ_CONE:
            if (this->parent && OBJ_GROUP == this->parent->type)
                return Cone::normal(this, point);
            return Cone::normal(this, obj_point);
    }
    return new Vector(0, 0, 0, 0);
}

void Body::transform(Matrix *matrix) {
    this->transformation = this->transformation->dot_product(matrix);
}

