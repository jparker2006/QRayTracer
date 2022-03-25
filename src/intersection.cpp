#include "include/intersection.h"

Intersection::Intersection(float ft) {
    this->ft = ft;
}

Intersection* Intersection::hit(QVector<Intersection*> intersections) { static // redo this function
    float fMin = Q_INFINITY;
    int nIndex = 0;

    if (0 == intersections.length())
        return nullptr;

    for (int i=0; i<intersections.size(); i++) {
        if (intersections[i]->ft > 0 && intersections[i]->ft < fMin) {
            fMin = intersections[i]->ft;
            nIndex = i;
        }
    }
    return intersections[nIndex];
}
