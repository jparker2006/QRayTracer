#include "include/cone.h"

Cone::Cone(Material *material): Body(material, Body::OBJ_TYPE::OBJ_CONE) {}

QVector<Intersection *> Cone::intersection(Body *body, Ray *ray) {
    Matrix *mInverse = body->transformation->inverse();
    ray = ray->transform(mInverse);
    delete mInverse;
    float fa = qPow(ray->direction->fx, 2) - qPow(ray->direction->fy, 2) + qPow(ray->direction->fz, 2);
    float fb = 2.0 * ray->origin->fx * ray->direction->fx - 2.0 * ray->origin->fy * ray->direction->fy+ 2.0 * ray->origin->fz * ray->direction->fz;
    float fc = qPow(ray->origin->fx, 2) - qPow(ray->origin->fy, 2) + qPow(ray->origin->fz, 2);
    float fEPSILON = 0.0001;
    if (qAbs(fa) < fEPSILON && qAbs(fb) < fEPSILON)
        return {};
    if (qAbs(fa) < fEPSILON)
        return { new Intersection(-fc / (2.0 * fb), body->index) };
    float fDiscriminant = qPow(fb, 2) - (4.0 * fa * fc);
    if (fDiscriminant < 0)
        return {};
    QVector<Intersection *> intersections = {};
    float ft0 = (-fb - qSqrt(fDiscriminant)) / (2.0 * fa);
    float ft1 = (-fb + qSqrt(fDiscriminant)) / (2.0 * fa);
    if (ft0 > ft1) {
        float fTemp = ft0;
        ft0 = ft1;
        ft1 = fTemp;
    }
    float fy0 = ray->origin->fy + ft0 * ray->direction->fy;
    if (body->fMin < fy0 && fy0 < body->fMax)
        intersections.push_back(new Intersection(ft0, body->index));
    float fy1 = ray->origin->fy + ft1 * ray->direction->fy;
    if (body->fMin < fy1 && fy1 < body->fMax)
        intersections.push_back(new Intersection(ft1, body->index));
    if (!body->bClosed)
        return intersections;
    float ft_cap = (body->fMin - ray->origin->fy) / ray->direction->fy;
    if (Cone::check_caps(ray, ft_cap))
        intersections.push_back(new Intersection(ft_cap, body->index));
    ft_cap = (body->fMax - ray->origin->fy) / ray->direction->fy;
    if (Cone::check_caps(ray, ft_cap))
        intersections.push_back(new Intersection(ft_cap, body->index));
    return intersections;
}

Vector* Cone::normal(Body *body, Vector *point) {
    float fEPSILON = 0.0001;
    float fDist = qPow(point->fx, 2) + qPow(point->fz, 2);
    if (fDist < 1.0 && point->fy >= body->fMax - fEPSILON)
        return new Vector(0, 1, 0, 0);
    else if (fDist < 1.0 && point->fy <= body->fMin + fEPSILON)
        return new Vector(0, -1, 0, 0);
    float fy = qSqrt(qPow(point->fx, 2) + qPow(point->fz, 2));
    if (fy > 0)
        fy *= -1;
    return new Vector(point->fx, fy, point->fz, 0);
}

bool Cone::check_caps(Ray *ray, float ft) {
    float fx = ray->origin->fx + ft * ray->direction->fx;
    float fz = ray->origin->fz + ft * ray->direction->fz;
    return (qPow(fx, 2) + qPow(fz, 2)) <= 1.0;
}
