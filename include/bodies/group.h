#ifndef GROUP_H
#define GROUP_H

#include <QVector>

#include "include/math/vector.h"
#include "include/ray/ray.h"
#include "include/ray/intersection.h"
#include "include/math/matrix.h"
#include "include/textile/material.h"
#include "include/bodies/body.h"

class Group: public Body {
public:
    Group(Material *material);
    static QVector<Intersection *> intersection(Body *body, Ray *ray);
    static Vector *normal(Body *body, Vector *point);
    static Vector *world_to_obj_space(Body *body, Vector *point);
    static Vector *normal_to_world_space(Body *body, Vector *normal);
    void push(Body *body);
};

#endif // GROUP_H
