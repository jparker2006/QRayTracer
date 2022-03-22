// maybe need Vector<Intersection> initializer that sorts by t values
#include "include/intersection.h"

Intersection::Intersection(float ft, Object type) {
    this->ft = ft;
    this->object = type;
}

Intersection* Intersection::hit(QVector<Intersection*> intersections) { static
    float fMin = Q_INFINITY;
    int nIndex = 0;
    for (int i=0; i<intersections.size(); i++) {
        if (intersections[i]->ft > 0 && intersections[i]->ft < fMin) {
            fMin = intersections[i]->ft;
            nIndex = i;
        }
    }
    return intersections[nIndex];
}
