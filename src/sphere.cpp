#include "include/sphere.h"

Sphere::Sphere(Material *material, int index) {
    this->material = material;
    this->index = index;
    this->transformation = Matrix::identity_matrix();
}

QVector<Intersection *> Sphere::intersection(Ray *ray) {
    ray = ray->transform(this->transformation->inverse());
    Vector *sphere_to_ray = ray->origin->ew_subtract(new Vector(0, 0, 0, 1));
    float fa = ray->direction->dot_product(ray->direction);
    float fb = 2.0 * ray->direction->dot_product(sphere_to_ray);
    float fc = sphere_to_ray->dot_product(sphere_to_ray) - 1.0;
    float fDiscriminant = qPow(fb, 2) - (4.0 * fa * fc);
    if (fDiscriminant < 0)
        return {};
    QVector<Intersection *> intersections = {};
    intersections.push_back(new Intersection((-fb - qSqrt(fDiscriminant)) / (fa * 2), this->index));
    intersections.push_back(new Intersection((-fb + qSqrt(fDiscriminant)) / (fa * 2), this->index));
    return intersections;
}

Vector* Sphere::normal(Vector *point) {
    Vector *obj_point = this->transformation->inverse()->vector_multiply(point);
    Vector *obj_normal = obj_point->ew_subtract(new Vector(0, 0, 0, 1));
    Vector *wrld_normal = this->transformation->inverse()->transpose()->vector_multiply(obj_normal);
    wrld_normal->fw = 0.0;
    return wrld_normal->normalize();
}
