#ifndef WORLD_H
#define WORLD_H

#include <QVector>

#include "include/light.h"
#include "include/sphere.h"
#include "include/intersection.h"
#include "include/computation.h"
#include "include/body.h"

class World {
public:
    World();
    QVector<Intersection *> intersect_world(Ray *ray);
    Light *light;
    QVector<Body *> objects = {};
    Vector *shade_hit(Computation *comp);
    Vector *color_at(Ray *ray);
    bool check_shadowed(Vector *point);
};

#endif // WORLD_H
