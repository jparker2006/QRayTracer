#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>

#include "include/ray/ray.h"
#include "include/math/vector.h"

class Intersection {
public:
    Intersection(float ft, int index); // store object
    Intersection(float ft, int index, float fu, float fv);
    static Intersection* hit(QVector<Intersection *> intersections);
    float ft;
    int index; // objects index
    float fu, fv;
};

#endif // INTERSECTION_H
