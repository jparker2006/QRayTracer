#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QVector>

class Intersection {
public:
    enum Object {
        OBJ_SPHERE
    };
    Intersection(float ft, Object type);
    static Intersection *hit(QVector<Intersection *> intersections);
    float ft;
    Object object;
};

#endif // INTERSECTION_H
