#include "include/sphere.h"
#include <QDebug>

Sphere::Sphere(Material *material): Body(material, Body::OBJ_TYPE::OBJ_SPHERE) {}

QVector<Intersection *> Sphere::intersection(Body *body, Ray *ray) {
    Vector *sphere_to_ray = ray->origin->ew_subtract(new Vector(0, 0, 0, 1));
    float fa = ray->direction->dot_product(ray->direction);
    float fb = 2.0 * ray->direction->dot_product(sphere_to_ray);
    float fc = sphere_to_ray->dot_product(sphere_to_ray) - 1.0;
    delete sphere_to_ray;
    float fDiscriminant = qPow(fb, 2) - (4.0 * fa * fc);
    if (fDiscriminant < 0)
        return {};
    QVector<Intersection *> intersections = {};
    intersections.push_back(new Intersection((-fb - qSqrt(fDiscriminant)) / (2.0 * fa), body->index));
    intersections.push_back(new Intersection((-fb + qSqrt(fDiscriminant)) / (2.0 * fa), body->index));
    return intersections;
}

Vector* Sphere::normal(Body *body, Vector *point) {
    Vector *obj_normal = point->ew_subtract(new Vector(0, 0, 0, 1));
    Matrix *mtInverse = body->mInverse->transpose();
    Vector *wrld_normal = mtInverse->vector_multiply(obj_normal);
    wrld_normal->fw = 0.0;
    delete obj_normal;
    delete mtInverse;
    return wrld_normal->normalize();
}
