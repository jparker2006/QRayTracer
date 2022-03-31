#include "include/plane.h"

Plane::Plane(Material *material): Body(material, Body::OBJ_TYPE::OBJ_PLANE) {}

QVector<Intersection *> Plane::intersection(Body *body, Ray *ray) {
    ray = ray->transform(body->transformation->inverse());
    float fEPSILON = 0.0001;
    if (qAbs(ray->direction->fy) < fEPSILON)
        return {};
    float ft = -ray->origin->fy / ray->direction->fy;
    return { new Intersection(ft, body->index) };
}

Vector* Plane::normal(Body *body, Vector *point) {
    Q_UNUSED(body);
    Q_UNUSED(point);
    return new Vector(0, 1, 0, 0);
}
