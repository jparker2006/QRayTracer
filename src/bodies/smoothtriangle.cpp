#include "include/bodies/smoothtriangle.h"
#include <QDebug>

SmoothTriangle::SmoothTriangle(Material *material, Vector *p0, Vector *p1, Vector *p2, Vector *n0, Vector *n1, Vector *n2): Body(material, Body::OBJ_SMOOTH_TRIANGLE) {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;
    this->n0 = n0;
    this->n1 = n1;
    this->n2 = n2;
    this->e0 = p1->ew_subtract(p0);
    this->e1 = p2->ew_subtract(p0);
}

QVector<Intersection *> SmoothTriangle::intersection(Body *body, Ray *ray) {
    Vector *dir_cross_e1 = ray->direction->cross_product(body->e1);
    float fDet = body->e0->dot_product(dir_cross_e1);
    float fEPSILON = 0.0001;
    if (qAbs(fDet) < fEPSILON) {
        delete dir_cross_e1;
        return {};
    }
    float f = 1.0 / fDet;
    Vector *p0_to_origin = ray->origin->ew_subtract(body->p0);
    float u = f * p0_to_origin->dot_product(dir_cross_e1);
    delete dir_cross_e1;
    if (u < 0 || u > 1) {
        delete p0_to_origin;
        return {};
    }
    Vector *origin_cross_e0 = p0_to_origin->cross_product(body->e0);
    delete p0_to_origin;
    float v = f * ray->direction->dot_product(origin_cross_e0);
    if (v < 0 || (u + v) > 1) {
        delete origin_cross_e0;
        return {};
    }
    float ft = f * body->e1->dot_product(origin_cross_e0);
    delete origin_cross_e0;
    return { new Intersection(ft, body->index, u, v) };
}

Vector* SmoothTriangle::normal(Body *body, Vector *point, Intersection *intersection) { // mem op
    Q_UNUSED(point);
    Vector *ep0 = body->n1->scalar_multiply(intersection->fu);
    Vector *ep1 = body->n2->scalar_multiply(intersection->fv);
    float uvData = 1.0 - intersection->fu - intersection->fv;
    Vector *ep2 = body->n0->scalar_multiply(uvData);
    return ep0->ew_add(ep1->ew_add(ep2))->normalize();
}
