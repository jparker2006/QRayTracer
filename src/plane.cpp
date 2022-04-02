#include "include/plane.h"

Plane::Plane(Material *material): Body(material, Body::OBJ_TYPE::OBJ_PLANE) {}

QVector<Intersection *> Plane::intersection(Body *body, Ray *ray) {
    Matrix *mInverse = body->transformation->inverse();
    ray = ray->transform(mInverse);
    delete mInverse;
    float fEPSILON = 0.0001;
    if (qAbs(ray->direction->fy) < fEPSILON)
        return {};
    float ft = -ray->origin->fy / ray->direction->fy;
    return { new Intersection(ft, body->index) };
}
