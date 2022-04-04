#ifndef WORLD_H
#define WORLD_H

#include <QVector>

#include "include/render/light.h"
#include "include/bodies/sphere.h"
#include "include/ray/intersection.h"
#include "include/misc/computation.h"
#include "include/bodies/body.h"

class World {
public:
    World();
    QVector<Intersection *> intersect_world(Ray *ray);
    Light *light;
    QVector<Body *> objects = {};
    Vector *shade_hit(Computation *comp, int nRemaining);
    Vector *color_at(Ray *ray, int nRemaining);
    bool check_shadowed(Vector *point);
    Vector* reflected_color(Computation *comp, int nRemaining);
    Vector *refracted_color(Computation *comp, int nRemaining);
    float schlick_approximation(Computation *comp);
    void push(Body *body);
};

#endif // WORLD_H
