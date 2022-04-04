#include "include/bodies/cube.h"
#include <QDebug>

Cube::Cube(Material *material): Body(material, OBJ_CUBE) { }

Vector* Cube::normal(Vector *point) {
    float fmaxc = qMax( qMax( qAbs(point->fx), qAbs(point->fy) ), qAbs(point->fz) );
    if (qAbs(point->fx) == fmaxc)
        return new Vector(point->fx, 0, 0, 0);
    else if (qAbs(point->fy) == fmaxc)
        return new Vector(0, point->fy, 0, 0);
    else if (qAbs(point->fz) == fmaxc)
        return new Vector(0, 0, point->fz, 0);
    return nullptr;
}

QVector<Intersection *> Cube::intersection(Body *body, Ray *ray) {
    QVector<float> v_xt = Cube::check_axis(ray->origin->fx, ray->direction->fx);
    QVector<float> v_yt = Cube::check_axis(ray->origin->fy, ray->direction->fy);
    QVector<float> v_zt = Cube::check_axis(ray->origin->fz, ray->direction->fz);
    float ftmin = qMax(qMax(v_xt[0], v_yt[0]), v_zt[0]);
    float ftmax = qMin(qMin(v_xt[1], v_yt[1]), v_zt[1]);
    if (ftmin > ftmax)
        return {};
    return {new Intersection(ftmin, body->index), new Intersection(ftmax, body->index)};
}

QVector<float> Cube::check_axis(float fOrigin, float fDirection) {
    float ftMinNumerator = -1 - fOrigin;
    float ftMaxNumerator = 1 - fOrigin;
    float fEPSILON = 0.0001;
    float ftmin, ftmax;
    if (qAbs(fDirection) >= fEPSILON) {
        ftmin = ftMinNumerator / fDirection;
        ftmax = ftMaxNumerator / fDirection;
    }
    else {
        ftmin = ftMinNumerator * Q_INFINITY;
        ftmax = ftMaxNumerator * Q_INFINITY;
    }
    if (ftmin > ftmax) {
        float fTemp = ftmin;
        ftmin = ftmax;
        ftmax = fTemp;
    }
    return { ftmin, ftmax };
}
