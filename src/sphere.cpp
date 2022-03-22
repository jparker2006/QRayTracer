#include "include/sphere.h"

Sphere::Sphere() {

}

QVector<Intersection *> Sphere::intersection(Ray *ray, bool bTransform) {
    if (bTransform)
        ray = ray->transform(this->transformation->inverse());
    Vector *sphere_to_ray = ray->origin->ew_subtract(new Vector(0, 0, 0, 1));
    float fa = ray->direction->dot_product(ray->direction);
    float fb = 2.0 * ray->direction->dot_product(sphere_to_ray);
    float fc = sphere_to_ray->dot_product(sphere_to_ray) - 1.0;
    float fDiscriminant = qPow(fb, 2) - (4.0 * fa * fc);
    if (fDiscriminant < 0)
        return {};
    QVector<Intersection *> intersections = {};
    intersections.push_back(new Intersection((-fb - qSqrt(fDiscriminant)) / (fa * 2), Intersection::Object::OBJ_SPHERE));
    intersections.push_back(new Intersection((-fb + qSqrt(fDiscriminant)) / (fa * 2), Intersection::Object::OBJ_SPHERE));
    return intersections;
}
