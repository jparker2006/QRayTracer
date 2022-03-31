#include "include/intersection.h"
#include <QDebug>

Intersection::Intersection(float ft, int index) {
    this->ft = ft;
    this->index = index;
}

// this function is wrong
Intersection* Intersection::hit(QVector<Intersection*> intersections) {
    if (0 == intersections.length())
        return {};
    float fMin = Q_INFINITY;
    int nIndex = 0;
    for (int i=0; i<intersections.length(); i++) {
        if (intersections[i]->ft > 0.0 && intersections[i]->ft < fMin) {
            fMin = intersections[i]->ft;
            nIndex = i;
        }
    }
    return intersections[nIndex];
}


