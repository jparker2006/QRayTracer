#include "include/group.h"
#include "include/sphere.h"
#include <QDebug>

Group::Group(Material *material): Body(material, Body::OBJ_TYPE::OBJ_GROUP) { }

QVector<Intersection *> Group::intersection(Body *body, Ray *ray) {
    QVector<Intersection *> intersections = {};
    for (int x=0; x<body->vChildren.length(); x++) {
        Ray *curr_ray = new Ray(ray->origin, ray->direction);
        Ray *tRay0 = curr_ray->transform(body->vChildren[x]->mInverse);
        Ray *tRay1 = tRay0->transform(body->mInverse);
        delete curr_ray;
        delete tRay0;
        QVector<Intersection *> curr_xs = body->vChildren[x]->intersection(tRay1);
        for (int y=0; y<curr_xs.length(); y++) {
            intersections.push_back(curr_xs[y]);
        }
    }
    return intersections;
}

Vector* Group::normal(Body *body, Vector *point) {
    if (Body::OBJ_GROUP == body->type)
        return new Vector(0, 1, 0, 0);
    Vector *local_point = Group::world_to_obj_space(body, point);
    Vector *local_normal = body->normal(local_point);
    Vector *normal_in_world_space = Group::normal_to_world_space(body, local_normal);
    delete local_point;
    delete local_normal;
    return normal_in_world_space;
}

Vector* Group::world_to_obj_space(Body *body, Vector *point) {
    if (body->parent)
        point = Group::world_to_obj_space(body->parent, point);
    return body->mInverse->vector_multiply(point);
}

Vector* Group::normal_to_world_space(Body *body, Vector *normal) {
    Matrix *mtInverse = body->mInverse->transpose();
    Vector *operated = mtInverse->vector_multiply(normal);
    delete mtInverse;
    normal->fw = 0;
    Vector *normalized = operated->normalize();
    delete operated;
    if (body->parent)
        normalized = Group::normal_to_world_space(body->parent, normalized);
    return normalized;
}

void Group::push(Body *body) {
    body->parent = this;
    this->vChildren.push_back(body);
}
