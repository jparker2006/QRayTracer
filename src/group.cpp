#include "include/group.h"
#include "include/sphere.h"
#include <QDebug>

Group::Group(Material *material): Body(material, Body::OBJ_TYPE::OBJ_GROUP) { }

QVector<Intersection *> Group::intersection(Body *body, Ray *ray) {
    QVector<Intersection *> intersections = {};
    for (int x=0; x<body->vChildren.length(); x++) {
        Ray *curr_ray = new Ray(ray->origin, ray->direction);
        Matrix *mInverse = body->vChildren[x]->transformation->inverse();
        curr_ray = curr_ray->transform(mInverse);
        delete mInverse;
        QVector<Intersection *> curr_xs = body->vChildren[x]->intersection(curr_ray);
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
    return normal_in_world_space;
}

Vector* Group::world_to_obj_space(Body *body, Vector *point) {
    if (body->parent)
        point = Group::world_to_obj_space(body->parent, point);
    return body->transformation->inverse()->vector_multiply(point);
}

Vector* Group::normal_to_world_space(Body *body, Vector *normal) {
    normal = body->transformation->inverse()->transpose()->vector_multiply(normal);
    normal->fw = 0;
    normal = normal->normalize();
    if (body->parent)
        normal = Group::normal_to_world_space(body->parent, normal);
    return normal;
}

void Group::push(Body *body) {
    body->parent = this;
    this->vChildren.push_back(body);
}
