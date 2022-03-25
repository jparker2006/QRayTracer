#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>

#include "include/ray.h"
#include "include/vector.h"

class Intersection {
public:
    Intersection(float ft); // store object
    static Intersection *hit(QVector<Intersection *> intersections);
    float ft;
};

#endif // INTERSECTION_H
