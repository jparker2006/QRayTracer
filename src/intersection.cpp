#include "include/intersection.h"
#include <QDebug>

Intersection::Intersection(float ft, int index) {
    this->ft = ft;
    this->index = index;
}

Intersection* Intersection::hit(QVector<Intersection*> intersections) { static
    float fMin = 100000000;
    int nIndex = 0;
    if (0 == intersections.length())
        return nullptr;
    for (int i=0; i<intersections.length(); i++) {
        if (intersections[i]->ft > 0 && intersections[i]->ft < fMin) {
            nIndex = i;
            fMin = intersections[i]->ft;
        }
    }
    return intersections[nIndex];
}


