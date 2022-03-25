#ifndef WORLD_H
#define WORLD_H

#include <QVector>

#include "include/light.h"
#include "include/sphere.h"
#include "include/intersection.h"
#include "include/computation.h"

class World {
public:
    World();
    QVector<Intersection *> intersect_world(Ray *ray);
    Light *light;
    QVector<Sphere *> objects = {};
    Vector *shade_hit(Computation *comp);
    Vector *color_at(Ray *ray);
};

#endif // WORLD_H
