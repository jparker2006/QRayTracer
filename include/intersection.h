#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>

#include "include/ray.h"
#include "include/vector.h"

class Intersection {
public:
    Intersection(float ft, int index); // store object
    static Intersection* hit(QVector<Intersection *> intersections);
    float ft;
    int index; // objects index
};

#endif // INTERSECTION_H
